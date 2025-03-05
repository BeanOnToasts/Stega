#include "encode.h"

/**
 * @brief Converts from ASCII to binary
 * @short This method converts a message to binary and adds the delimiter to the end for encoding using
 * the bitset function
 * @param message is the ASCII message
 * @return The binary message
 */
string Encoder::ConvertToBin(const string& message) {
    string binary;
    //convert each character to a binary value
    for (char c : message + "$$") {
        binary += bitset<8>(c).to_string();
    }
    return binary;
}

/**
 * @brief Encodes a message into an image
 * @short This method iterates through each pixel of the image and the binary message and alters the least
 * significant bit of each colour value (BGR) to be the same as the current bit in the binary message
 * @param message_img is the image to encode
 * @param binaryMessage is the message to be encoded
 */
void Encoder::EncodeImage(Mat message_img, const string& binaryMessage) const {
    //size_t is for indexing specifically which is cool I think
    size_t bitIndex = 0;
    //check image is large enough to store the message
    //iterate through rows of pixels
    for (int i=0; i < message_img.rows; ++i) {
    //iterate through columns of pixels
        for (int j=0; j < message_img.cols; ++j) {
        //iterate through BGR values
            for (int k=0; k < 3; ++k) {
            //check whether all the message is complete
                if (bitIndex < binaryMessage.size()) {
                //check that LSB isn't already the correct value
                    if ((message_img.at<Vec3b>(i, j)[k] & 1) != binaryMessage[bitIndex] - '0') {
                    //change the LSB if required
                        message_img.at<Vec3b>(i, j)[k] ^= 1;
                    }
                    bitIndex++;
                }
                //breaks when all bits have been encoded
                else {
                    break;
                }
            }
        }
    }
    imwrite(newFilePath, message_img);
    cout << "Message encoded into " << newFilePath << endl;
}

/**
 * @brief Constructor
 * @short This constructor initialises the file paths of the image to encode and the image to write to, and
 * throws an error if the file is not found
 * @param path is the name of the file
 * @param encryptedMessage is the message to be encoded
 */
Encoder::Encoder(const string& path, const string& encryptedMessage) :
fileName(path),
message(encryptedMessage) {

        //define the image paths and create image object
        fileName = "../" + fileName;

        if (not fileName.ends_with(".png")) {
            filePath = fileName + ".png";
            newFilePath = fileName + "_encoded.png";
        }
        else {
            filePath = fileName;
            fileName.replace(fileName.find(".png"),3, "");
            newFilePath = fileName + "_encoded.png";
        }

        message_img = imread(filePath);

        if (message_img.empty()) {
            cerr << "Could not open or find " << filePath << ", make sure the image is a png." << endl;
        }
        else {
            printf("Opened file %s, writing the message to %s\n", filePath.c_str(), newFilePath.c_str());
        }
    }

/**
 * @brief Runs private encoder methods
 * @short This method is used to run the methods which are encapsulated for security purposes
 */
void Encoder::CallEncode() const {
        string binaryMessage = ConvertToBin(message);
        EncodeImage(message_img, binaryMessage);
    }
