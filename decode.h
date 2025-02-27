#ifndef DECODE_H
#define DECODE_H
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;

class Decoder {
string fileName;
string filePath;
string newFilePath;

Mat message_img;

static string ConvertFromBin(const string& binary);

static string DecodeImage(Mat message_img);
public:
    Decoder(const string& path, const string& keyVal);
    void CallDecode();
};
#endif //DECODE_H
