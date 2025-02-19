#ifndef ENCODE_H
#define ENCODE_H
#include <bitset>
using namespace std;

class Encoder {

    private:
    string filePath;
    string message;
    Mat message_img;
    string binaryMessage;

    //these are private for security reasons i think
    string ConvertToBin() {
        string binary;
        //delimiter to mark the end of the message
        string delimiter = "00000000";
        //convert each character to a binary value
        for (char c : message) {
            binary += bitset<8>(c).to_string();
        }
        binary += delimiter;
        return binary;
    };

    Mat EncodeImage() {
        //size_t is for indexing specifically which is cool i think
        size_t currentBit = 0;
        //check image is large enough to store the message
        //iterate through rows and columns of pixels
        for (int i=0; i < message_img.rows; ++i) {
            for (int j=0; j < message_img.cols; ++j) {
                //iterate through RGB values
                for (int k=0; k < 3; ++k) {
                    //check whether all the message is complete
                    if (currentBit < binaryMessage.size()) {
                        //check that LSB isn't already the correct value
                        if ((message_img.at<Vec3b>(i, j)[k] & 1) != (binaryMessage[currentBit] - '0')) {
                            //change the LSB if required
                            message_img.at<Vec3b>(i, j)[k] ^= 1;
                        }
                        currentBit++;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }

    public:
    //use constructor to create the constants that will be used throughout the class
    Encoder(const string& path, const string& encryptedMessage, const string& keyVal) :
    filePath(path),
    message(encryptedMessage) {

        Mat message_img = imread(filePath);
        binaryMessage = ConvertToBin();
        if (message_img.empty()) {
            cout << "Could not open or find the image, make sure the image is a png." << endl;
        }
        else {
            cout << "Opened file " << filePath << endl;
            cout << "Message: " << message << endl;
        }
    }
};
#endif //ENCODE_H
