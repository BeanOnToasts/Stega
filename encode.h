#ifndef ENCODE_H
#define ENCODE_H

class Encoder {
    private:
    string filePath;
    public:
    Encoder(const string& path) : filePath(path) {
        Mat message_img = imread(filePath);
        if (message_img.empty()) {
            cout << "Could not open or find the image, make sure the image is a png." << endl;
        }
        else {
            cout << "Opened file " << filePath << endl;
        }
    }

};
#endif //ENCODE_H
