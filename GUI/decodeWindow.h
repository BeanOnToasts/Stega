#ifndef DECODEWINDOW_H
#define DECODEWINDOW_H

#include <string>

#include <opencv2/opencv.hpp>

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QFileDialog>

#include "../decode/decode.h"
#include "../decrypt/decrypt.h"

class DecodeWindow final : public QWidget {
    Q_OBJECT

    QPushButton *selectImageButton;
    QPushButton *selectKeyButton;
    QPushButton *decodeButton;
    QLabel *decryptedMessageLabel;
    QLabel *selectedImageLabel;
    QLabel *selectedKeyLabel;
    QString imagePath;
    QString keyPath;
    void displayImage(const QString &path) const;

public:
    explicit DecodeWindow(QWidget *parent = nullptr);

private slots:
    void selectImage();
    void selectKey();
    void decodeMessage();
};

#endif // DECODEWINDOW_H
