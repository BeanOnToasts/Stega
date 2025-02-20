#ifndef DECODE_H
#define DECODE_H

class Decoder {
private:
    string fileName;
    string filePath;
    string newFilePath;

    string binary;
    string message;
    Mat message_img;

    string ConvertFromBin() {
        string encryptedMessage;
        char tmp = 0;
        //split into bytes
        for (int i = 0; i < binary.length(); i += 8) {
            tmp = 0;
            //iterate through each bit
            for (int j = i; j < (i+8); j++) {
                //do an OR operation to change tmp into the character
                if (binary[j] == '1') {
                    tmp |= 1 << 7-j%8;
                }
            }
            encryptedMessage += tmp;
        }
        return encryptedMessage;
    }

    void DecodeImage() {
        size_t currentBit = 0;
        for (int i=0; i < message_img.rows; ++i) {
            for (int j=0; j < message_img.cols; ++j) {
                for (int k=0; k < 3; ++k) {

                }
            }
        }
    }

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
};
#endif //DECODE_H
