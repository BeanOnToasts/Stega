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

    //sorry Ian I liked cout more than printf
    cout << "Enter the name of the file to be encoded" << endl;
    getline(cin, fileName);
    cout << "Enter the message you want to encode" << endl;
    getline(cin, message);
    //key will be generated automatically eventually
    cout << "Enter the key you want to encode with" << endl;
    getline(cin, key);

    string newFile = "hacker_encoded";

    Encoder encoder(fileName, message, key);
    Decoder decoder(newFile, key);

    encoder.CallEncode();
    decoder.CallDecode();

    return 0;
}