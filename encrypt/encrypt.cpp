#include "encrypt.h"

/**
 * @brief Generates a random key
 * @short This method generates a random AES-256-style key using random entropy, it won't be true unless the device has
 * a TRNG, so most devices will create PRNs
 * @return The randomly generated key
 */
std::string Encrypter::GenerateKey() {
    std::random_device rd; //random entropy
    std::mt19937 gen(rd()); //random number with rd as the seed
    std::uniform_int_distribution<int> dis(0, 255); //ensure values are between 0 and 255

    std::string key_str;
    key_str.reserve(key_size*2); //reserve space for the key as hex will be twice the size

    for (int i = 0; i < key_size; i++) {
        key[i] = dis(gen); //generate key
        char hex_byte[3]; //2 hex digits and null terminator
        std::sprintf(hex_byte, "%02x", key[i]);
        //sprintf_s(hex_byte, "%02x", key[i]); //convert to hex
        key_str += hex_byte;
    }
    return key_str;
}

/**
 * @brief Writes a generated key to a text file
 * @short This method creates a file and writes the provided key to it, overwriting any existing keys in files
 * with the same name. An error is returned if the file cannot be opened (e.g. permission error)
 * @param key is the key to write
 */
void Encrypter::StoreKey(const std::string& key) const {
    std::string filePath = "../" + key_filename;
    std::ofstream file(filePath, std::ios::out | std::ios::trunc); //open file in write mode and overwrite existing file
    if (!file) {
        std::cerr << "Can't open file " << key_filename << std::endl;
    }
    file << key << std::endl;
    file.close();
}

/**
 * @brief Encrypts a message using a key
 * @short This method encrypts a message by performing an XOR operation on the message and the key, then
 * writing each bit to the encrypted message
 * @param message is the message to encrypt
 * @param key is the key to encrypt with
 * @return The encrypted message
 */
std::string Encrypter::EncryptMessage(const std::string& message, const std::string& key) {
    std::string encrypted_message = message;
    for (size_t i = 0; i < message.size(); i++) {
        encrypted_message[i] = message[i] ^ key[i % key.length()];
    }
    return encrypted_message;
}

std::string Encrypter::CallKeyGen() {
    const std::string aes_key = GenerateKey();
    StoreKey(aes_key);
    return aes_key;
}

/**
 * @brief Runs private encrypter methods
 * @short This method is used to run the methods which are encapsulated for security purposes
 * @return The encrypted message
 */
std::string Encrypter::CallEncrypter(const std::string& message, const std::string& key_str) {
    std::cout << "Encrypted and key sent to " << key_filename << std::endl;
    std::cout << EncryptMessage(message,key_str) << std::endl;
    return EncryptMessage(message, key_str);
}