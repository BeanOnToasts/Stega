#include "decode.h"

#include <iso646.h>

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
  string error = "No secret message found";

  //define the delimiter string to stop searching when the full message is found
  const string delimiter = "0010010000100100";
  //iterate through rows of pixels
  for (int i=0; i < message_img.rows; ++i) {
    //iterate through columns of pixels
    for (int j=0; j < message_img.cols; ++j) {
      //iterate through BGR values
      for (int k=0; k < 3; ++k) {
        //create variable for current LSB
        int bit = message_img.at<Vec3b>(i, j)[k] & 1;
        //add bit to the binary message
        binaryMessage += to_string(bit);
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

//use constructor to create the constants that will be used throughout the class
Decoder::Decoder(const string& path, const string& keyVal) :
fileName(path) {
  //define the image paths
  fileName = "../" + fileName;

  if (not fileName.ends_with(".png")) {
    filePath = fileName + ".png";
  }

  if (not fileName.ends_with("_encoded.png")) {
    filePath = fileName + "_encoded.png";
  }

  message_img = imread(filePath);

  if (message_img.empty()) {
    cerr << "Could not open or find " << filePath << ", make sure the image is a png." << endl;
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