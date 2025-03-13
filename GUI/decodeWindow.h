#ifndef DECODEWINDOW_H
#define DECODEWINDOW_H

#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <string>
#include <opencv2/opencv.hpp>

#include "../decode/decode.h"
#include "../decrypt/decrypt.h"

class SelectOption;

class DecodeWindow final : public QWidget {
    Q_OBJECT

    SelectOption *selectOption;

    QPushButton *selectImageButton;
    QPushButton *selectKeyButton;
    QPushButton *decodeButton;
    QPushButton *backButton;
    QLabel *decryptedMessageLabel;
    QLabel *selectedImageLabel;
    QLabel *selectedKeyLabel;
    QString imagePath;
    QString keyPath;
    void displayImage(const QString &path) const;

    void selectImage();
    void selectKey();
    void decodeMessage() const;
    void backToMenu();

public:
    explicit DecodeWindow(QWidget *parent = nullptr);
};

#endif // DECODEWINDOW_H
