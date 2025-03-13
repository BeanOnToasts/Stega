#ifndef DECODE_H
#define DECODE_H

#include <string>
#include <opencv2/opencv.hpp>

/**
 * @class Decoder decode.h decode
 * @brief Extracts message from an encoded image
 * @short This class handles all the methods used to extract messages out of encoded images and convert the
 * extracted binary back into readable ASCII
 */
class Decoder {
    //attributes
    std::string fileName;
    std::string filePath;
    std::string newFilePath;

    cv::Mat message_img;

    //private methods
    static std::string ConvertFromBin(const std::string &binary);

    static std::string DecodeImage(cv::Mat message_img);

    //public methods
public:
    Decoder(const std::string &path);

    std::string CallDecode() const;
};
#endif //DECODE_H
