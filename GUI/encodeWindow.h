#ifndef ENCODEWINDOW_H
#define ENCODEWINDOW_H

#include <string>
using namespace std;

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>

#include <opencv2/opencv.hpp>
using namespace cv;

#include "../encode/encode.h"
#include "../encrypt/encrypt.h"

/**
 * @brief displays a window for running the encryption and encoder
 * @short this class handles the window that allows users to enter a message, choose an image, and send the
 * encrypted version of that message into an encoded version of that image
 */
class EncodeWindow final : public QWidget {
    Q_OBJECT

    QLineEdit *messageInput;
    QPushButton *selectImageButton;
    QPushButton *encodeButton;
    QLabel *selectedImageLabel;
    QString imagePath;
    void displayImage(const QString &path) const;

public:
    explicit EncodeWindow(QWidget *parent = nullptr);

private slots:
    void selectImage();
    void encodeMessage();

};

#endif //ENCODEWINDOW_H
