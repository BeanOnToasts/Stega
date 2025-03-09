#include "decodeWindow.h"

DecodeWindow::DecodeWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Steganography Tool");

    QVBoxLayout *layout = new QVBoxLayout(this);

    setMinimumSize(300, 300);
    resize(400, 300);

    selectKeyButton = new QPushButton("Select Key File", this);
    layout->addWidget(selectKeyButton);
    connect(selectKeyButton, &QPushButton::clicked, this, &DecodeWindow::selectKey);

    selectImageButton = new QPushButton("Select Image", this);
    layout->addWidget(selectImageButton);
    connect(selectImageButton, &QPushButton::clicked, this, &DecodeWindow::selectImage);

    selectedImageLabel = new QLabel(this);
    selectedImageLabel->setAlignment(Qt::AlignCenter);
    selectedImageLabel->setText("Select an image to encode");
    selectedImageLabel->setStyleSheet("border: 2px dashed gray; padding: 10px;");
    layout->addWidget(selectedImageLabel);

    decodeButton = new QPushButton("Decode", this);
    layout->addWidget(decodeButton);
    connect(decodeButton, &QPushButton::clicked, this, &DecodeWindow::decodeMessage);

    setLayout(layout);
}

/**
 * @brief allows user to select a key
 * @short this method allows the user to select a key through a file dialogue and filters for .txt
 */
void DecodeWindow::selectKey() {
    keyPath = QFileDialog::getOpenFileName(this, "Select Key File", "../", "Text Files (*.txt)");
    if (!keyPath.isEmpty()) {
        qDebug() << "Key file selected: " << keyPath;
    } else {
        qDebug() << "No key file selected.";
    }
}

/**
 * @brief allows user to select an image
 * @short this method allows the user to select an image through a file dialogue and filters for PNGs
 */
void DecodeWindow::selectImage() {
    imagePath = QFileDialog::getOpenFileName(this, "Select Image", "../", "PNG Images (*.png)");
    if (!imagePath.isEmpty()) {
        displayImage(imagePath);
    }
}

/**
 * @brief displays the selected image
 * @short this method is used to display the image by converting the Mat into a Qimg which can be displayed
 * by a label in Qt
 * @param path is the file path of the image
 */
void DecodeWindow::displayImage(const QString &path) const {
    cv::Mat img = imread(path.toStdString());

    if (img.empty()) {
        qDebug() << "Failed to load image: " << path;
        return;
    }

    //makes the image a Qimage
    cvtColor(img, img, cv::COLOR_BGR2RGB); //converts BGR to RGB
    const QImage qimg(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);

    //display the image
    selectedImageLabel->setPixmap(QPixmap::fromImage(qimg).scaled(380, 280, Qt::KeepAspectRatio));
}

/**
 * @brief runs decode function
 * @short this method ensures that both a key and an image are present, then runs the decryption and decoding
 * of the image. For use on a button press.
 */
void DecodeWindow::decodeMessage() {

    //makes sure there is a message and image
    if (imagePath.isEmpty()) {
        qDebug() << "No image selected for decoding.";
        return;
    }

    if (keyPath.isEmpty()) {
        qDebug() << "No key file selected.";
        return;
    }

    //decode image
    Decoder decoder(imagePath.toStdString());
    string encryptedMessage = decoder.CallDecode();

    //if no message was found
    if (encryptedMessage == "Loud incorrect buzzer sound") {
        qDebug() << "No secret message found in the image.";
        return;
    }

    //decrypt message
    Decrypter decrypter(encryptedMessage, keyPath.toStdString());
    string decryptedMessage = decrypter.CallDecrypt();

    //display decrypted message
    QMessageBox::information(this, "Decoded Message", QString::fromStdString(decryptedMessage));
}

