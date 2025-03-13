#include "decode.h"

/**
 * @brief Converts from binary to ASCII
 * @short Converts the given message from binary back into ASCII text by performing an OR operation on each
 * character to alter the bits
 * @param binary is the binary message
 * @return the encrypted message decoded from the binary
 */
std::string Decoder::ConvertFromBin(const std::string &binary) {
    std::string encryptedMessage;
    char tmp = 0;
    //split into bytes
    for (int i = 0; i < binary.length(); i += 8) {
        tmp = 0;
        //iterate through each bit
        for (int j = i; j < (i + 8); j++) {
            //do an OR operation to change tmp into the character
            if (binary[j] == '1') {
                tmp |= 1 << (7 - j % 8);
            }
        }
        encryptedMessage += tmp;
    }
    return encryptedMessage;
}

/**
 * @brief Decodes the message from LSB of RGB values in the image
 * @short iterates through each pixel of the image and appends each bit to the end of the discovered binary
 * message until the delimiter is discovered, then return the binary message
 * @param message_img is the image containing the message
 * @return Extracted binary message
 */
std::string Decoder::DecodeImage(cv::Mat message_img) {
    std::string binaryMessage;
    std::string currentByte;
    std::string currentBit;
    std::string error = "Loud incorrect buzzer sound";

    //define the delimiter string to stop searching when the full message is found
    const std::string delimiter = "0010010000100100";
    //iterate through rows of pixels
    for (int i = 0; i < message_img.rows; ++i) {
        //iterate through columns of pixels
        for (int j = 0; j < message_img.cols; ++j) {
            //iterate through BGR values
            for (int k = 0; k < 3; ++k) {
                //create variable for current LSB
                int bit = message_img.at<cv::Vec3b>(i, j)[k] & 1;
                //add bit to the binary message
                binaryMessage += std::to_string(bit);
                //check the right amount of bits have been discovered
                if (binaryMessage.size() >= delimiter.size() &&
                    binaryMessage.substr(binaryMessage.size() - delimiter.size()) == delimiter) {
                    //return binary message when delimiter is found
                    return binaryMessage.substr(0, binaryMessage.size() - delimiter.size());
                }
            }
        }
    }
    //if delimiter is not found, return the error message
    return error;
}

/**
 * @brief Constructor
 * @short Initialises the file path to the encoded image and returns an error if the file is not found
 * @param path is the name of the file
 */
Decoder::Decoder(const std::string &path) : fileName(path) {
    message_img = cv::imread(fileName);

    if (message_img.empty()) {
        std::cerr << "Could not open or find " << fileName << std::endl;
    } else {
        std::cout << "Opened file " << fileName << std::endl;
    }
}

/**
 * @brief Runs private decoder methods
 * @short This method is used to run the methods which are encapsulated for security purposes
 * @return The discovered message
 */
std::string Decoder::CallDecode() const {
    const std::string binary = DecodeImage(message_img);
    return ConvertFromBin(binary);
}
