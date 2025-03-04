#include "encode.h"

/*
 * Converts a message to binary and adds the delimiter to the end for encoding. Uses the bitset function
 */
string Encoder::ConvertToBin(const string& message) {
    string binary;
    //convert each character to a binary value
    for (char c : message + "$$") {
        binary += bitset<8>(c).to_string();
    }
    return binary;
}

/*
 * iterates through each pixel of the image and the binary message and alters the least significant bit
 * of each colour value (BGR) to be the same as the current bit in the binary message
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

//constructor, initialises file paths to image
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

/*
 * used for running the encoder as the methods are encapsulated for security purposes
 */
void Encoder::CallEncode() const {
        string binaryMessage = ConvertToBin(message);
        EncodeImage(message_img, binaryMessage);
    }
