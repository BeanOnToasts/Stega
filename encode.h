#ifndef ENCODE_H
#define ENCODE_H
#include <iostream>
#include <bitset>
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;


class Encoder {
    string fileName;
    string filePath;
    string newFilePath;

    string message;
    Mat message_img;

private:
    string ConvertToBin(const string& message);
    void EncodeImage(Mat message_img, const string& binaryMessage);
public:
    //use constructor to create the constants that will be used throughout the class
    Encoder(const string& path, const string& encryptedMessage, const string& keyVal) :
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
    void CallEncode();
};
#endif //ENCODE_H