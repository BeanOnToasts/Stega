#include "encodeWindow.h"

/**
 * @brief constructor
 * @short  this constructor creates the layout and structure of the window
 * @param parent is the parent object of this window
 */
EncodeWindow::EncodeWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Steganography Tool");

    QVBoxLayout *layout = new QVBoxLayout(this);

    setLayout(layout);
    setMinimumSize(300, 300);
    resize(400, 300);

    messageInput = new QLineEdit(this);
    messageInput->setPlaceholderText("Enter message to encode...");
    layout->addWidget(messageInput);

    selectImageButton = new QPushButton("Select Image", this);
    layout->addWidget(selectImageButton);
    connect(selectImageButton, &QPushButton::clicked, this, &EncodeWindow::selectImage);

    selectedImageLabel = new QLabel(this);
    selectedImageLabel->setAlignment(Qt::AlignCenter);
    selectedImageLabel->setText("Select an image to encode");
    selectedImageLabel->setStyleSheet("border: 2px dashed gray; padding: 10px;");
    layout->addWidget(selectedImageLabel);

    encodeButton = new QPushButton("Encode", this);
    layout->addWidget(encodeButton);
    connect(encodeButton, &QPushButton::clicked, this, &EncodeWindow::encodeMessage);

    setLayout(layout);
}

/**
 * @brief allows user to select an image
 * @short this method allows the user to select an image through a file dialogue and filters for PNGs
 */
void EncodeWindow::selectImage() {
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
void EncodeWindow::displayImage(const QString &path) const {
    Mat img = imread(path.toStdString());

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
 * @brief runs encode function
 * @short this method ensures that both a message and an image are present, then runs the encryption and encoding of the
 * image. For use on a button press. Displays where the encoded image is located after it is created
 */
void EncodeWindow::encodeMessage() {

    //makes sure there is a message and image
    if (imagePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select an image first.");
        return;
    }

    QString message = messageInput->text();
    if (message.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a message to encode.");
        return;
    }

    //convert to std::string for encryption
    string imgPath = imagePath.toStdString();
    string msg = message.toStdString();

    //encrypt the message
    Encrypter encrypter(msg);
    string encryptedMessage = encrypter.CallEncrypter();

    //encode into the image
    Encoder encoder(imgPath, encryptedMessage);
    encoder.CallEncode();

    //tell user where image saved
    string newPath = imgPath.replace(imgPath.find(".png"),4, "") + "_encoded.png";

    //tell user it worked
    QMessageBox::information(this, "Success", "Message successfully encoded to: " + QString::fromStdString(newPath));

    //quit when finished
    QApplication::quit();
}
