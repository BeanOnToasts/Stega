#include "decodeWindow.h"

decodeWindow::decodeWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Decode", this);

    layout->addWidget(label);
    setLayout(layout);

    setMinimumSize(300, 300);
    resize(400, 300);
}
