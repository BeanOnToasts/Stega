#ifndef DECRYPT_H
#define DECRYPT_H

#include <iostream>
#include <fstream>

/**
 * @class Decrypter decrypt.h decrypt
 * @brief Decrypts message using a key
 * @short This class handles all aspects of the decryption of the message, including: retrieving the key from
 * the key text file; and decrypting the given encrypted message
 */
class Decrypter {
    //attributes
    std::string key;
    int key_size;
    std::string fileName;

    std::string encryptedMessage;
    std::string message;

    //private methods
    std::string OpenKey(std::string &file_name);

    std::string DecryptMessage(const std::string &encrypted_message, const std::string &key) const;

    //public methods
public:
    std::string CallDecrypt() const;

    Decrypter(const std::string &encrypted_message, const std::string &key_file);
};
#endif //DECRYPT_H
