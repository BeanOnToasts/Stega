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

string ConvertToBin(const string& message);
void EncodeImage(Mat message_img, const string& binaryMessage);
public:
    Encoder(const string& path, const string& encryptedMessage, const string& keyVal);
    void CallEncode();
};
#endif //ENCODE_H