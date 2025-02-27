#ifndef ENCODE_H
#define ENCODE_H

#include <bitset>
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;

class Encoder {
    //atributes
    string fileName;
    string filePath;
    string newFilePath;

    string message;
    Mat message_img;

    //private methods
    string ConvertToBin(const string& message);
    void EncodeImage(Mat message_img, const string& binaryMessage);

    //public methods
public:
    Encoder(const string& path, const string& encryptedMessage, const string& keyVal);
    void CallEncode();
};
#endif //ENCODE_H