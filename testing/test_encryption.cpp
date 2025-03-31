#include <gtest/gtest.h>
#include <stdexcept>
#include <filesystem>

#include "../encrypt/encrypt.h"

std::string test_key_path = "../aes_key.txt";

//Test: Key generation
TEST(EncryptTest, GeneratedKey) {
    Encrypter encrypter;
    ASSERT_NO_THROW({
        encrypter.CallKeyGen();
    }) << "Key generation should run.";
    ASSERT_TRUE(std::filesystem::exists(test_key_path)) << "Key file should exist";
    ASSERT_TRUE(std::filesystem::remove(test_key_path)) << "Key file should be deleted after test";
}

//Test: Key sent to key file
TEST(EncryptTest, StoredKey) {
    Encrypter encrypter;
    encrypter.CallKeyGen();

    ASSERT_TRUE(std::filesystem::exists(test_key_path)) << "Key file should exist";
    ASSERT_TRUE(std::filesystem::remove(test_key_path)) << "Key file should be deleted after test";
}

//Test: Message Encrypted
TEST(EncryptTest, EncryptedMessage) {
    Encrypter encrypter;
    std::string encryptedMessage = encrypter.CallEncrypter("Hello World","TestKey");
    ASSERT_FALSE(encryptedMessage.empty()) << "Encrypted message should not be empty";
}