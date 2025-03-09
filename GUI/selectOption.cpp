#include "selectOption.h"

/**
 * @brief constructor
 * @short  this constructor creates the layout and structure of the window
 * @param parent is the parent object of this window
 */
SelectOption::SelectOption(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Steganography Tool");
    setMinimumSize(300, 300);
    resize(400, 300);

    QFont titleFont("Ariel", 16, QFont::Bold);
    QFont buttonFont("Ariel", 14);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Are You Encoding Or Decoding?", this);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    encodeButton = new QPushButton("Encode", this);
    encodeButton->setFont(buttonFont);
    encodeButton->setStyleSheet(
        "QPushButton {"
        "background-color: #256100;"
        "color: white;"
        "border: 7px solid #256100;"
        "border-radius: 7px;"
        "padding: 10px;"
        "}"
        "QPushButton:hover {"
        "border-color: #66c928;"
        "}"
        );

    decodeButton = new QPushButton("Decode", this);
    decodeButton->setFont(buttonFont);
    decodeButton->setStyleSheet(
    "QPushButton {"
    "background-color: #e34400;"
    "color: white;"
    "border: 7px solid #e34400;"
    "border-radius: 7px;"
    "padding: 10px;"
    "}"
    "QPushButton:hover {"
    "border-color: #ff9061;"
    "}"
    );

    layout->addWidget(titleLabel);
    layout->addSpacing(20);
    layout->addWidget(encodeButton);
    layout->addWidget(decodeButton);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);

    connect(encodeButton, &QPushButton::clicked, this, &SelectOption::onEncodeClicked);
    connect(decodeButton, &QPushButton::clicked, this, &SelectOption::onDecodeClicked);
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
    dWindow = new decodeWindow();
    dWindow->show();
    this->close();
}