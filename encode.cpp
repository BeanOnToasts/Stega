#include "encode.h"

//these are private for security reasons i think
string Encoder::ConvertToBin(const string& message) {
    string binary;
    //convert each character to a binary value
    for (char c : message + "$$") {
        binary += bitset<8>(c).to_string();
    }
    return binary;
};

    void Encoder::EncodeImage(Mat message_img, const string& binaryMessage) {
        //size_t is for indexing specifically which is cool I think
        size_t bitIndex = 0;
        //check image is large enough to store the message
        //iterate through rows of pixels
        for (int i=0; i < message_img.rows; ++i) {
            //iterate through columns of pixels
            for (int j=0; j < message_img.cols; ++j) {
                //iterate through RGB values
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

//use constructor to create the constants that will be used throughout the class
Encoder::Encoder(const string& path, const string& encryptedMessage, const string& keyVal) :
fileName(path),
message(encryptedMessage) {

        //define the image paths and create image object
        filePath = "../" + fileName + ".png";
        newFilePath = "../" + fileName + "_encoded.png";
        message_img = imread(filePath);


        if (message_img.empty()) {
            cout << "Could not open or find " << filePath << ", make sure the image is a png." << endl;
        }
        else {
            printf("Opened file %s, writing the message '%s' to %s\n",filePath.c_str(), message.c_str(), newFilePath.c_str());
        }
    }

    //public function to run the encoder
    void Encoder::CallEncode() {
        string binaryMessage = ConvertToBin(message);
        EncodeImage(message_img, binaryMessage);
    }