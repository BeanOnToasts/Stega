#include <gtest/gtest.h>
#include <stdexcept>
#include <filesystem>
#include <fstream>

#include "../decrypt/decrypt.h"
#include "../encrypt/encrypt.h"

static const std::string test_key_path = "../aes_key.txt";

//Test: Open valid key file
TEST(DecryptTest, ValidKey) {
    Encrypter encrypter;
    encrypter.CallKeyGen();
    ASSERT_TRUE(std::filesystem::exists(test_key_path)) << "Key file should exist";
    ASSERT_NO_THROW(Decrypter decrypter("Encrypted Message", test_key_path)) << "Decryption failed";
    ASSERT_TRUE(std::filesystem::remove(test_key_path)) << "Key file should be deleted after test";
}

//Test: Message is decrypted
TEST(DecryptTest, DecrytpedMessage) {
    Encrypter encrypter;

    encrypter.CallKeyGen();
    ASSERT_TRUE(std::filesystem::exists(test_key_path)) << "Key file should exist";

    std::ifstream file(test_key_path);
    std::string test_key;
    std::getline(file, test_key);
    file.close();

    std::string test_message = "Hello World";

    std::string encryptedMessage = encrypter.CallEncrypter(test_message, test_key);

    Decrypter decrypter(encryptedMessage, test_key_path);
    std::string decryptedMessage = decrypter.CallDecrypt();

    ASSERT_TRUE(test_message == decryptedMessage) << "Original message should be the same as the decrypted message";

    ASSERT_TRUE(std::filesystem::remove(test_key_path)) << "Key file should be deleted after test";
}