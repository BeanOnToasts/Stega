#include "encrypt.h"

//generate a random AES-256 key
string Encrypter::GenerateKey() {
    random_device rd; //random entropy
    mt19937 gen(rd()); //random number with rd as the seed
    uniform_int_distribution<int> dis(0, 255); //ensure values are between 0 and 255

    string key_str;
    key_str.reserve(key_size*2); //reserve space for the key as hex will be twice the size

    for (int i = 0; i < key_size; i++) {
        key[i] = dis(gen); //generate key
        char hex_byte[3]; //2 hex digits and null terminator
        sprintf(hex_byte, "%02x", key[i]); //convert to hex
        key_str += hex_byte;
    }
    return key_str;
}

//store the key in a text file
void Encrypter::StoreKey(const string& key) {
    string filePath = "../" + key_filename;
    ofstream file(filePath, ios::out | ios::trunc); //open file in write mode and overwrite existing file
    if (!file) {
        cerr << "Can't open file " << key_filename << endl;
    }
    file << key << endl;
    file.close();
}

//encrypt message using the key
string Encrypter::EncryptMessage(const string& message, const string& key) {
    string encrypted_message = message;
    for (size_t i = 0; i < message.size(); i++) {
        encrypted_message[i] = message[i] + key[i % key_size];
    }
    cout << "Encrypted message: " << encrypted_message << endl;
    return encrypted_message;
}

void Encrypter::CallEncrypter() {
    aes_key = GenerateKey();
    StoreKey(aes_key);
    EncryptMessage(message, aes_key);
    cout << "Encrypted and key sent to " << key_filename << endl;
}

Encrypter::Encrypter(const string& message) :
    message(message) {
}

