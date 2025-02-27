#include "encrypt.h"

#include <random>

//generate a random AES-256 key
void Encrypter::GenerateKey() {
    random_device rd; //random entropy
    mt19937 gen(rd()); //random number with rd as the seed
    uniform_int_distribution<int> dis(0, 255); //ensure values are between 0 and 255

    for (int i = 0; i < key_size; i++) {
        key[i] = dis(gen); //generate the key
    }
    cout << key << endl;
}

void Encrypter::CallEncrypter() {
    GenerateKey();
}

Encrypter::Encrypter(const string& message) :
    message(message) {
}

