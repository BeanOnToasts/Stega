#ifndef DECODE_H
#define DECODE_H

class Decoder {
    private:
    string filePath;
    public:
    Decoder(const string& path) : filePath(path) {
        Mat message_img = imread(filePath);
        if (message_img.empty()) {
            cout << "Could not open or find the image, make sure the image is a png." << endl;
        }
        else {
            cout << "Opened file " << filePath << endl;
        }
    }
};
#endif //DECODE_H
