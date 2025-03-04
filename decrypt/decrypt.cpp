#include "decrypt.h"

#include <string>
#include <opencv2/imgproc.hpp>

//open file with key and return the key inside
string Decrypter::OpenKey(string &file_name) {
    if (not file_name.ends_with(".txt")) {
        file_name += ".txt";
    }
    file_name = "../"+file_name;
    string foundKey;
    ifstream file(file_name);
    if (!file) {
        cerr << "File " << file_name << " does not exist." << endl;
    }
    while (getline(file, foundKey)) {
        key_size = foundKey.size();
        return foundKey;
    }
}

//decrypt the message, same function as encryption
string Decrypter::DecryptMessage(const string& encrypted_message,const string& key) {
    string message = encrypted_message;
    for (size_t i = 0; i < encrypted_message.size(); i++) {
        message[i] = encrypted_message[i] ^ key[i % key_size];
    }
    return message;
}

string Decrypter::CallDecrypt() {
    key = OpenKey(fileName);
    message = DecryptMessage(encryptedMessage,key);
    return message;
}

Decrypter::Decrypter(const string& encrypted_message, const string& key_file) :
encryptedMessage(encrypted_message), fileName(key_file) {
}



