#ifndef ENCODEWINDOW_H
#define ENCODEWINDOW_H

#include <string>

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

#include <opencv2/opencv.hpp>

#include "../encode/encode.h"
#include "../encrypt/encrypt.h"
#include "selectOption.h"

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
    QLabel *selectedImageLabel;
    QLabel *selectedKeyLabel;
    QString key;
    QString keyPath;
    QString imagePath;

    void displayImage(const QString &path) const;

public:
    explicit EncodeWindow(QWidget *parent = nullptr);

private slots:
    void generateKey();

    void selectKey();

    void selectImage();

    void encodeMessage();
};

#endif //ENCODEWINDOW_H
