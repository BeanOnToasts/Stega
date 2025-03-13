#ifndef ENCODEWINDOW_H
#define ENCODEWINDOW_H

#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <string>
#include <opencv2/opencv.hpp>

#include "../encode/encode.h"
#include "../encrypt/encrypt.h"

class SelectOption;

/**
 * @brief displays a window for running the encryption and encoder
 * @short this class handles the window that allows users to enter a message, choose an image, and send the
 * encrypted version of that message into an encoded version of that image
 */
class EncodeWindow final : public QWidget {
    Q_OBJECT

    SelectOption *selectOption;

    QLineEdit *messageInput;
    QPushButton *selectImageButton;
    QPushButton *encodeButton;
    QPushButton *selectKeyButton;
    QPushButton *generateKeyButton;
    QPushButton *backButton;
    QLabel *selectedImageLabel;
    QLabel *selectedKeyLabel;
    QString key;
    QString keyPath;
    QString imagePath;

    void displayImage(const QString &path) const;

    void generateKey();
    void selectKey();
    void selectImage();
    void encodeMessage();
    void backToMenu();

public:
    explicit EncodeWindow(QWidget *parent = nullptr);
};

#endif //ENCODEWINDOW_H
