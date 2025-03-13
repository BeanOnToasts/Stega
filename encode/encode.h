#ifndef ENCODE_H
#define ENCODE_H

#include <string>
#include <bitset>
#include <opencv2/opencv.hpp>

/**
 * @class Encoder encode.h encode
 * @brief Converts a message to binary and encodes it into an image
 * @short This class handles all the methods used to convert messages to binary and encode the binary message
 * into an image in the LSB of each GBR value of each pixel
 */
class Encoder {
    //atributes
    std::string fileName;
    std::string filePath;
    std::string newFilePath;

    std::string message;
    cv::Mat message_img;

    //private methods
    static std::string ConvertToBin(const std::string& message);
    void EncodeImage(cv::Mat message_img, const std::string& binaryMessage) const;

    //public methods
public:
    Encoder(const std::string& path, const std::string& encryptedMessage);
    void CallEncode() const;
};
#endif //ENCODE_H