#ifndef DECRYPT_H
#define DECRYPT_H

#include <iostream>
#include <fstream>
using namespace std;

class Decrypter {
    //attributes
    string key;
    int key_size;
    string fileName;

    string encryptedMessage;
    string message;

    //private methods
    string OpenKey(string& file_name);

    string DecryptMessage(const string &encrypted_message, const string &key) const;

    //public methods
public:
    string CallDecrypt();
    Decrypter(const string& encrypted_message, const string& key_file);
};
#endif //DECRYPT_H
