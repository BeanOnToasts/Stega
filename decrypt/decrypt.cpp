#include "decrypt.h"

/**
 * @brief Decrypts the message using the key
 * @short This method decrypts an encrypted message by performing an XOR operation on the encrypted message
 * and the key, then writing each bit to the decrypted message
 * @param encrypted_message is the encrypted message
 * @param key is the key used to encrypt
 * @return decrypted message
 */
std::string Decrypter::DecryptMessage(const std::string &encrypted_message, const std::string &key) const {
    std::string message = encrypted_message;
    for (size_t i = 0; i < encrypted_message.size(); i++) {
        message[i] = encrypted_message[i] ^ key[i % key.length()];
    }
    return message;
}

/**
 * @brief Runs private decrypter methods
 * @short This method is used to run the methods which are encapsulated for security purposes
 * @return The decrypted message
 */
std::string Decrypter::CallDecrypt() const {
    return DecryptMessage(encryptedMessage, key);
}

/**
 * @brief Constructor
 * @param encrypted_message is the encrypted message
 * @param key_file is the key used to encrypt
 */
Decrypter::Decrypter(const std::string &encrypted_message, const std::string &key_file) : key_size(0),
    fileName(key_file), encryptedMessage(encrypted_message) {
    //open key file and read key
    std::ifstream file(key_file);
    if (!file) {
        std::cerr << "Error: Could not open key file: " << key_file << std::endl;
        return;
    }

    getline(file, key);
    key_size = key.size();
}
