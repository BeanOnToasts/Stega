#ifndef DECODE_H
#define DECODE_H

using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;

/**
 * @class Decoder decode.h decode
 * @brief Extracts message from an encoded image
 * @short This class handles all the methods used to extract messages out of encoded images and convert the
 * extracted binary back into readable ASCII
 */
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
    Decoder(const string& path);
    string CallDecode() const;
};
#endif //DECODE_H
