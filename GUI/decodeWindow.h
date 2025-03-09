#ifndef DECODEWINDOW_H
#define DECODEWINDOW_H

#include <string>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

#include "../decode/decode.h"
#include "../decrypt/decrypt.h"

class DecodeWindow final : public QWidget {
    Q_OBJECT

    QPushButton *selectImageButton;
    QPushButton *selectKeyButton;
    QPushButton *decodeButton;
    QLabel *selectedImageLabel;
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
