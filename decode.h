#ifndef DECODE_H
#define DECODE_H
#include <iostream>
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;

class Decoder {
private:
    string fileName;
    string filePath;
    string newFilePath;

    Mat message_img;

    string ConvertFromBin(const string& binary);

    string DecodeImage(Mat message_img);

public:
    //use constructor to create the constants that will be used throughout the class
    Decoder(const string& path, const string& keyVal) :
    fileName(path) {
        //define the image paths and create image object
        filePath = "../" + fileName + ".png";
        newFilePath = "../" + fileName + "_encoded.png";
        message_img = imread(filePath);

        if (message_img.empty()) {
            cout << "Could not open or find " << filePath << ", make sure the image is a png." << endl;
        }
        else {
            cout << "Opened file " << filePath << endl;
        }
    }
    void CallDecode();
};
#endif //DECODE_H
