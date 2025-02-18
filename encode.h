#ifndef ENCODE_H
#define ENCODE_H
#include <bitset>
using namespace std;

class Encoder {

    private:
    string filePath;
    string message;
    string key;

    public:
    //use constructor to create the constants that will be used throughout the class
    Encoder(const string& path, const string& encryptedMessage, const string& keyVal) :
    filePath(path),
    message(encryptedMessage),
    key(keyVal) {

        Mat message_img = imread(filePath);
        if (message_img.empty()) {
            cout << "Could not open or find the image, make sure the image is a png." << endl;
        }
        else {
            cout << "Opened file " << filePath << endl;
            cout << "Message: " << message << endl;
            cout << "Key: " << key << endl;
        }
    }
    string convertToBin() {
        string binary;
        for (char c : message) {
            binary += bitset<8>(c).to_string();
        }
        return binary;
    };
};
#endif //ENCODE_H
