#include <opencv2/opencv.hpp>
using namespace cv;
#include <iostream>
using namespace std;

#include "encode/encode.h"
#include "encrypt/encrypt.h"
#include "decode/decode.h"
#include "decrypt/decrypt.h"

int main() {
    string fileName;
    string message;
    string encrypted_message;
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
        encrypted_message = encrypter.CallEncrypter();

        Encoder encoder(fileName, encrypted_message);
        encoder.CallEncode();
    }
    else if (option == 2) {
        string keyFileName;
        cout << "Enter the name of the file to be decoded" << endl;
        cin.ignore();
        getline(cin, fileName);
        cout << "Enter the name of the file containing the decryption key" << endl;
        getline(cin, keyFileName);
        Decoder decoder(fileName, message);
        encrypted_message = decoder.CallDecode();
        Decrypter decrypter(encrypted_message,keyFileName);
        message = decrypter.CallDecrypt();
        cout << message << endl;
    }
    else {
        cout << "no" << endl;
    }

    return 0;
}