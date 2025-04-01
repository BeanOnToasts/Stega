#include <gtest/gtest.h>
#include <stdexcept>
#include <filesystem>
#include <opencv2/opencv.hpp>

#include "../encode/encode.h"

static const std::string test_image_path = "../../assets/test_image.png";
static const std::string encoded_test_image_path = "../../assets/test_image_encoded.png";

//Test: Load valid image
TEST(EncoderTest, ValidImage) {
    ASSERT_NO_THROW({
        Encoder encoder(test_image_path, "Hello World");
    });
}

//Test: New image is created
TEST(EncoderTest, ImageCreation) {
    Encoder encoder(test_image_path, "Hello World");
    encoder.CallEncode();
    ASSERT_TRUE(std::filesystem::exists(encoded_test_image_path)) << "Encoded image should exist";

    ASSERT_TRUE(std::filesystem::remove(encoded_test_image_path)) << "Encoded image should be deleted after test";
}

//Test: Image is encoded
TEST(EncoderTest, ImageEncode) {
    Encoder encoder(test_image_path, "Hello World");
    encoder.CallEncode();
    cv::Mat test_image = cv::imread(test_image_path);
    cv::Mat encoded_test_image = cv::imread(encoded_test_image_path);

    cv::Mat diff;
    absdiff(test_image, encoded_test_image, diff); //calculate absolute difference
    double difference = norm(diff, cv::NORM_L1); //sum of absolute differences

    ASSERT_GT(difference, 0) << "Encoded image should be different from the original image.";

    //clean-up
    ASSERT_TRUE(std::filesystem::exists(encoded_test_image_path)) << "Encoded image should exist";
    ASSERT_TRUE(std::filesystem::remove(encoded_test_image_path)) << "Encoded image should be deleted after test";
}