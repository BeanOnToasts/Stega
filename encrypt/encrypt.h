#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <random>
#include <iostream>
#include <fstream>
using namespace std;

/**
 * @class Encrypter encrypt.h encrypt
 * @brief Encrypts a message using a key
 * @short This class handles all the methods used to generate and store a random key, and to use the key to
 * encrypt a message
 */
class Encrypter {
    //attributes
    static constexpr int key_size = 32;
    unsigned char key[key_size]; //unsigned char so it can't be negative as I only need 0-255
    string key_filename = "aes_key.txt"; //the key will be saved to this file

    string message;

    //private methods
    string GenerateKey();
    void StoreKey(const string& key) const;

    static string EncryptMessage(const string& message, const string& key);

    //public methods
public:
    // Encrypter(const string& message, const string& keyFile);
    string CallEncrypter(const string& message, const string& key);

    string CallKeyGen();
};

#endif //ENCRYPTION_H
