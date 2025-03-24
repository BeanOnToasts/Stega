#include "encodeWindow.h"
#include "selectOption.h"

/**
 * @brief constructor
 * @short  this constructor creates the layout and structure of the window
 * @param parent is the parent object of this window
 */
EncodeWindow::EncodeWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Steganography Tool");

    QVBoxLayout *layout = new QVBoxLayout(this);

    setMinimumSize(320, 200);
    setMaximumSize(1600, 1000);
    resize(1200, 750);

    messageInput = new QLineEdit(this);
    messageInput->setPlaceholderText("Enter message to encode...");
    messageInput->setProperty("class", "displayText");
    layout->addWidget(messageInput);

    generateKeyButton = new QPushButton("Generate a Key", this);
    generateKeyButton->setProperty("class", "selectButton");
    layout->addWidget(generateKeyButton);
    connect(generateKeyButton, &QPushButton::clicked, this, &EncodeWindow::generateKey);

    selectKeyButton = new QPushButton("Select a Key", this);
    selectKeyButton->setProperty("class", "selectButton");
    layout->addWidget(selectKeyButton);
    connect(selectKeyButton, &QPushButton::clicked, this, &EncodeWindow::selectKey);

    selectedKeyLabel = new QLabel(this);
    selectedKeyLabel->setMaximumHeight(30);
    selectedKeyLabel->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    selectedKeyLabel->setText("Please select an encryption key...");
    selectedKeyLabel->setProperty("class", "displayText");
    layout->addWidget(selectedKeyLabel);

    selectImageButton = new QPushButton("Select Image", this);
    selectImageButton->setProperty("class", "selectButton");
    layout->addWidget(selectImageButton);
    connect(selectImageButton, &QPushButton::clicked, this, &EncodeWindow::selectImage);

    selectedImageLabel = new QLabel(this);
    selectedImageLabel->setAlignment(Qt::AlignCenter);
    selectedImageLabel->setText("Select an image to encode or leave blank to use default image");
    selectedImageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    selectedImageLabel->setStyleSheet("border: 2px dashed gray; padding: 10px;");
    layout->addWidget(selectedImageLabel);

    encodeButton = new QPushButton("Encode", this);
    encodeButton->setProperty("class", "encodeButton");
    layout->addWidget(encodeButton);
    connect(encodeButton, &QPushButton::clicked, this, &EncodeWindow::encodeMessage);

    backButton = new QPushButton("Back to Menu", this);
    backButton->setProperty("class", "negativeButton");
    layout->addWidget(backButton);
    connect(backButton, &QPushButton::clicked, this, &EncodeWindow::backToMenu);

    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
}

/**
 * @brief generates a key
 * @short allows the user to generate a key using the generate key method in the encrypt class, for use on a
 * button
 */
void EncodeWindow::generateKey() {
    Encrypter encrypter;
    key = QString::fromStdString(encrypter.CallKeyGen());
    selectedKeyLabel->setText("Key: " + key);
    generateKeyButton->hide();
    layout()->removeWidget(generateKeyButton);
    delete generateKeyButton;
    generateKeyButton = nullptr; //delete the button once used
    QMessageBox::information(this, "Key", "Key Sent to aes_key.txt");
}

/**
 * @brief generates a key
 * @short allows the user to select a key, for use on a button
 */
void EncodeWindow::selectKey() {
    keyPath = QFileDialog::getOpenFileName(this, "Select Key File", "../", "Text Files (*.txt)");
    QFile file(keyPath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        key = in.readLine(); // Read the first line
        file.close();

        selectedKeyLabel->setText("Key: " + key);
    }
}

/**
 * @brief allows user to select an image
 * @short this method allows the user to select an image through a file dialogue and filters for PNGs
 */
void EncodeWindow::selectImage() {
    imagePath = QFileDialog::getOpenFileName(this, "Select Image", "../", "PNG Images (*.png)");
    if (!imagePath.isEmpty()) {
        displayImage(imagePath);

        //ensures the message will fit in the image
        const QImage selectedImage(imagePath);
        const int height = selectedImage.height();
        const int width = selectedImage.width();
        const int maxMsgChars = 3*8*height*width;

        messageInput->setMaxLength(maxMsgChars);
    }
}

/**
 * @brief displays the selected image
 * @short this method is used to display the image by converting the Mat into a Qimg which can be displayed
 * by a label in Qt
 * @param path is the file path of the image
 */
void EncodeWindow::displayImage(const QString &path) const {
    cv::Mat img = cv::imread(path.toStdString());

    if (img.empty()) {
        qDebug() << "Failed to load image: " << path;
        return;
    }

    //makes the image a Qimage
    cvtColor(img, img, cv::COLOR_BGR2RGB); //converts BGR to RGB
    const QImage qimg(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);

    //display the image
    QSize labelSize = selectedImageLabel->size();
    QPixmap pixmap = QPixmap::fromImage(qimg).scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    selectedImageLabel->setPixmap(pixmap);
}

/**
 * @brief runs encode function
 * @short this method ensures that both a message and an image are present, then runs the encryption and encoding
 * of the image. For use on a button press. Displays where the encoded image is located after it is created
 */
void EncodeWindow::encodeMessage() {
    //makes sure there is a message and image
    if (imagePath.isEmpty()) {
        QMessageBox::warning(this, "Image", "No image selected, using default.");
        imagePath = "../default.png";
    }

    QString message = messageInput->text();
    if (message.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a message to encode.");
        return;
    }

    //convert to std::string for encryption
    std::string imgPath = imagePath.toStdString();
    std::string msg = message.toStdString();

    //encrypt the message
    Encrypter encrypter;
    std::string encryptedMessage = encrypter.CallEncrypter(msg, key.toStdString());

    //encode into the image
    Encoder encoder(imgPath, encryptedMessage);
    encoder.CallEncode();

    //tell user where image saved
    std::string newPath = imgPath.replace(imgPath.find(".png"), 4, "") + "_encoded.png";

    //tell user it worked
    QMessageBox::information(this, "Success", "Message successfully encoded to: " + QString::fromStdString(newPath));

    //return to select option screen when finished
    selectOption = new SelectOption();
    selectOption->show();
    this->close();
}

/**
 * @brief goes back to selection screen
 */
void EncodeWindow::backToMenu() {
    //return to select option screen when finished
    selectOption = new SelectOption();
    selectOption->show();
    this->close();
}