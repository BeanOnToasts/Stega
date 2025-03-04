#include "decrypt.h"

#include <string>
#include <opencv2/imgproc.hpp>

/*
 * opens the specified file and returns the key found inside
 */
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
    getline(file, foundKey);
    key_size = foundKey.size();
    return foundKey;
}

/*
 * Decrypts the message by performing an XOR operation on the encrypted message using the key
 */
string Decrypter::DecryptMessage(const string &encrypted_message, const string &key) const {
    string message = encrypted_message;
    for (size_t i = 0; i < encrypted_message.size(); i++) {
        message[i] = encrypted_message[i] ^ key[i % key_size];
    }
    return message;
}

/*
 * used for running the decrypter as the methods are encapsulated for security purposes
 */
string Decrypter::CallDecrypt() {
    key = OpenKey(fileName);
    message = DecryptMessage(encryptedMessage,key);
    return message;
}

//constructor
Decrypter::Decrypter(const string& encrypted_message, const string& key_file) : key_size(0),
    fileName(key_file), encryptedMessage(encrypted_message) {
}



