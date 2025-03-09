#include "decrypt.h"

#include <string>
#include <opencv2/imgproc.hpp>

/**
 * @brief Decrypts the message using the key
 * @short This method decrypts an encrypted message by performing an XOR operation on the encrypted message
 * and the key, then writing each bit to the decrypted message
 * @param encrypted_message is the encrypted message
 * @param key is the key used to encrypt
 * @return decrypted message
 */
string Decrypter::DecryptMessage(const string &encrypted_message, const string &key) const {
    string message = encrypted_message;
    for (size_t i = 0; i < encrypted_message.size(); i++) {
        message[i] = encrypted_message[i] ^ key[i % key_size];
    }
    return message;
}

/**
 * @brief Runs private decrypter methods
 * @short This method is used to run the methods which are encapsulated for security purposes
 * @return The decrypted message
 */
string Decrypter::CallDecrypt() const {
    return DecryptMessage(encryptedMessage, key);
}

/**
 * @brief Constructor
 * @param encrypted_message is the encrypted message
 * @param key_file is the key used to encrypt
 */
Decrypter::Decrypter(const string& encrypted_message, const string& key_file) : key_size(0),
    fileName(key_file), encryptedMessage(encrypted_message) {
    //open key file and read key
    ifstream file(key_file);
    if (!file) {
        cerr << "Error: Could not open key file: " << key_file << endl;
        return;
    }

    getline(file, key);
    key_size = key.size();
}