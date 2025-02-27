#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <iostream>
using namespace std;

class Encrypter {
    //attributes
    string key;
    const int key_size = 32;
    string message;

    //private methods
    void GenerateKey();
    // void StoreKey();
    // string EncryptMessage(const string& message);

    //public methods
public:
    Encrypter(const string& message);
    void CallEncrypter();
};

#endif //ENCRYPTION_H
