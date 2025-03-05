#include "decrypt.h"

#include <string>
#include <opencv2/imgproc.hpp>

/**
 * @brief Opens a file and returns a key
 * @short This method opens a text file as an ifstream object, where the first line will be read and used as a key.
 * If no file is found with the name specified, an error is raised
 * @param file_name is name of the file
 * @return discovered key
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
string Decrypter::CallDecrypt() {
    key = OpenKey(fileName);
    message = DecryptMessage(encryptedMessage,key);
    return message;
}

/**
 * @brief Constructor
 * @param encrypted_message is the encrypted message
 * @param key_file is the key used to encrypt
 */
Decrypter::Decrypter(const string& encrypted_message, const string& key_file) : key_size(0),
    fileName(key_file), encryptedMessage(encrypted_message) {
}