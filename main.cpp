#include <opencv2/opencv.hpp>
using namespace cv;
#include <iostream>
using namespace std;

#include "encode.h"
#include "encrypt.h"
#include "decode.h"
#include "decrypt.h"

int main() {
    string fileName;
    string message;
    string key;
    int option;

    //sorry Ian I liked cout more than printf
    cout << "Would you like to encode [1] or decode [2] a message?" << endl;
    cin >> option;

    if (option == 1) {
        cout << "Enter the name of the file to be encoded" << endl;
        cin.ignore();
        getline(cin, fileName);
        cout << "Enter the message you want to encode" << endl;
        getline(cin, message);

        Encrypter encrypter(message);
        encrypter.CallEncrypter();

        Encoder encoder(fileName, message);
        encoder.CallEncode();
    }
    else if (option == 2) {
        cout << "Enter the name of the file to be decoded" << endl;
        cin.ignore();
        getline(cin, fileName);
        Decoder decoder(fileName, key);
        decoder.CallDecode();
    }
    else {
        cout << "no" << endl;
    }

    return 0;
}