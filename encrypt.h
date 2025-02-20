#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <opencv2/opencv.hpp>
using namespace cv;

class Encrypter {
    private:
    std::string key;
    public:
    Encrypter();
    
    ~Encrypter();
};

#endif //ENCRYPTION_H
