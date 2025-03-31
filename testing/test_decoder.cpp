#include <gtest/gtest.h>
#include <stdexcept>
#include <filesystem>
#include <opencv2/opencv.hpp>

#include "../encode/encode.h"
#include "../decode/decode.h"

static const std::string test_message = "Hello World";
static const std::string test_image_path = "../../assets/test_image.png";
static const std::string encoded_test_image_path = "../../assets/test_image_encoded.png";

//Test: Load valid image
TEST(DecoderTest, ValidImage) {
    Encoder encoder(test_image_path, test_message);
    encoder.CallEncode();
    ASSERT_NO_THROW({
        Decoder decoder(encoded_test_image_path);
    });

    //clean-up
    ASSERT_TRUE(std::filesystem::exists(encoded_test_image_path)) << "Encoded image should exist";
    ASSERT_TRUE(std::filesystem::remove(encoded_test_image_path)) << "Encoded image should be deleted after test";
}

//Test: Message successfully decoded
TEST(DecoderTest, ImageDecode) {
    Encoder encoder(test_image_path, test_message);
    encoder.CallEncode();
    Decoder decoder(encoded_test_image_path);
    std::string decodedMessage = decoder.CallDecode();
    ASSERT_TRUE(test_message == decodedMessage);

    //clean-up
    ASSERT_TRUE(std::filesystem::exists(encoded_test_image_path)) << "Encoded image should exist";
    ASSERT_TRUE(std::filesystem::remove(encoded_test_image_path)) << "Encoded image should be deleted after test";
}