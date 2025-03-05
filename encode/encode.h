#ifndef ENCODE_H
#define ENCODE_H

#include <iostream>
#include <bitset>
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;

/**
 * @class Encoder encode.h encode
 * @brief Converts a message to binary and encodes it into an image
 * @short This class handles all the methods used to convert messages to binary and encode the binary message
 * into an image in the LSB of each GBR value of each pixel
 */
class Encoder {
    //atributes
    string fileName;
    string filePath;
    string newFilePath;

    string message;
    Mat message_img;

    //private methods
    static string ConvertToBin(const string& message);
    void EncodeImage(Mat message_img, const string& binaryMessage) const;

    //public methods
public:
    Encoder(const string& path, const string& encryptedMessage);
    void CallEncode() const;
};
#endif //ENCODE_H