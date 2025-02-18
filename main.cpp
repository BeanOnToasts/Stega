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
    cout << "Enter the name of the file to be encoded" << endl;
    cin >> fileName;
    string filePath = "../" + fileName + ".png";
    Encoder encoder(filePath);

    return 0;
}