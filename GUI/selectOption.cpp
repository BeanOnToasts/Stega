#include "selectOption.h"

/**
 * @brief constructor
 * @short  this constructor creates the layout and structure of the window
 * @param parent is the parent object of this window
 */
SelectOption::SelectOption(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Steganography Tool");

    setMinimumSize(320, 200);
    setMaximumSize(1600, 1000);
    resize(1200, 750);

    const QFont titleFont("Ariel", 16, QFont::Bold);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Are You Encoding Or Decoding?", this);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    encodeButton = new QPushButton("Encode", this);
    encodeButton->setProperty("class", "encodeButton");

    decodeButton = new QPushButton("Decode", this);
    decodeButton->setProperty("class", "decodeButton");

    layout->addWidget(titleLabel);
    layout->addWidget(encodeButton);
    layout->addWidget(decodeButton);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);

    connect(encodeButton, &QPushButton::clicked, this, &SelectOption::onEncodeClicked);
    connect(decodeButton, &QPushButton::clicked, this, &SelectOption::onDecodeClicked);

    quitButton = new QPushButton("Quit Application", this);
    quitButton->setProperty("class", "negativeButton");
    layout->addWidget(quitButton);
    connect(quitButton, &QPushButton::clicked, this, &SelectOption::onQuitClicked);
}

/**
 * @brief opens encode window
 */
void SelectOption::onEncodeClicked() {
    eWindow = new EncodeWindow();
    eWindow->show();
    this->close();
}

/**
 * @brief opens decode window
 */
void SelectOption::onDecodeClicked() {
    dWindow = new DecodeWindow();
    dWindow->show();
    this->close();
}

/**
 * @brief quits application
 */
void SelectOption::onQuitClicked() {
    QApplication::quit();
}