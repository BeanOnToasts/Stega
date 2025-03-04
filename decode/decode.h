#ifndef DECODE_H
#define DECODE_H

using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;

class Decoder {
    //attributes
    string fileName;
    string filePath;
    string newFilePath;

    Mat message_img;

    //private methods
    static string ConvertFromBin(const string& binary);
    static string DecodeImage(Mat message_img);

    //public methods
public:
    Decoder(const string& path, const string& keyVal);
    string CallDecode() const;
};
#endif //DECODE_H
