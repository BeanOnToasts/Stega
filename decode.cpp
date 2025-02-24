#include "decode.h"
string Decoder::ConvertFromBin(const string& binary) {
  string encryptedMessage;
  char tmp = 0;
  //split into bytes
  for (int i = 0; i < binary.length(); i += 8) {
    tmp = 0;
    //iterate through each bit
    for (int j = i; j < (i+8); j++) {
      //do an OR operation to change tmp into the character
      if (binary[j] == '1') {
        tmp |= 1 << (7-j%8);
      }
    }
    encryptedMessage += tmp;
  }
  return encryptedMessage;
}

string Decoder::DecodeImage(Mat message_img) {
  string binaryMessage;
  string currentByte;
  string currentBit;

  bool delimiterFound = false;
  const string delimiterCheck = "0010010000100100";
    for (int i=0; i < message_img.rows; ++i) {
      for (int j=0; j < message_img.cols; ++j) {
        for (int k=0; k < 3; ++k) {
          int bit = message_img.at<Vec3b>(i, j)[k] & 1;
          binaryMessage += to_string(bit);
          if (binaryMessage.size() >= delimiterCheck.size() &&
              binaryMessage.substr(binaryMessage.size() - delimiterCheck.size()) == delimiterCheck) {
              return binaryMessage.substr(0, binaryMessage.size() - delimiterCheck.size()); ;
        }
      }
    }
  }
}

//use constructor to create the constants that will be used throughout the class
Decoder::Decoder(const string& path, const string& keyVal) :
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

void Decoder::CallDecode() {
  string binary = DecodeImage(message_img);
  string encryptedMessage = ConvertFromBin(binary);
  cout << encryptedMessage << endl;
}