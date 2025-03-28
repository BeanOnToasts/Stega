#include "decodeWindow.h"
#include "selectOption.h"

DecodeWindow::DecodeWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Steganography Tool");

    QVBoxLayout *layout = new QVBoxLayout(this);

    setMinimumSize(320, 200);
    setMaximumSize(1600, 1000);
    resize(1200, 750);

    selectKeyButton = new QPushButton("Select Key File", this);
    selectKeyButton->setProperty("class", "selectButton");
    layout->addWidget(selectKeyButton);
    connect(selectKeyButton, &QPushButton::clicked, this, &DecodeWindow::selectKey);

    selectedKeyLabel = new QLabel(this);
    selectedKeyLabel->setMaximumHeight(30);
    selectedKeyLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    selectedKeyLabel->setText("Please select a decryption key...");
    selectedKeyLabel->setProperty("class", "displayText");
    layout->addWidget(selectedKeyLabel);

    selectImageButton = new QPushButton("Select Image", this);
    selectImageButton->setProperty("class", "selectButton");
    layout->addWidget(selectImageButton);
    connect(selectImageButton, &QPushButton::clicked, this, &DecodeWindow::selectImage);

    selectedImageLabel = new QLabel(this);
    selectedImageLabel->setAlignment(Qt::AlignCenter);
    selectedImageLabel->setText("Select an image to encode");
    selectedImageLabel->setProperty("class", "displayImage");
    layout->addWidget(selectedImageLabel);

    decodeButton = new QPushButton("Decode", this);
    decodeButton->setProperty("class", "decodeButton");
    layout->addWidget(decodeButton);
    connect(decodeButton, &QPushButton::clicked, this, &DecodeWindow::decodeMessage);

    decryptedMessageLabel = new QLabel(this);
    decryptedMessageLabel->setWordWrap(true);
    decryptedMessageLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    decryptedMessageLabel->setText("Decrypted message will appear here...");
    decryptedMessageLabel->setProperty("class", "displayText");
    layout->addWidget(decryptedMessageLabel);

    backButton = new QPushButton("Back to Menu", this);
    backButton->setProperty("class", "negativeButton");
    layout->addWidget(backButton);
    connect(backButton, &QPushButton::clicked, this, &DecodeWindow::backToMenu);

    setLayout(layout);
}

/**
 * @brief allows user to select a key
 * @short this method allows the user to select a key through a file dialogue and filters for .txt
 */
void DecodeWindow::selectKey() {
    keyPath = QFileDialog::getOpenFileName(this, "Select Key File", "../", "Text Files (*.txt)");
    QFile file(keyPath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString key = in.readLine(); // Read the first line
        file.close();

        selectedKeyLabel->setText("Key: " + key);
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
    cv::Mat img = cv::imread(path.toStdString());

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
void DecodeWindow::decodeMessage() const {

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
    std::string encryptedMessage = decoder.CallDecode();

    //if no message was found
    if (encryptedMessage == "Loud incorrect buzzer sound") {
        qDebug() << "No secret message found in the image.";
        decryptedMessageLabel->setText("No secret message found.");
        return;
    }

    //decrypt message
    Decrypter decrypter(encryptedMessage, keyPath.toStdString());
    std::string decryptedMessage = decrypter.CallDecrypt();

    //display decrypted message
    decryptedMessageLabel->setText(QString::fromStdString(decryptedMessage));
}

/**
 * @brief goes back to selection screen
 */
void DecodeWindow::backToMenu() {
    //return to select option screen when finished
    selectOption = new SelectOption();
    selectOption->setProperty("class", "windows");
    selectOption->show();
    this->close();
}