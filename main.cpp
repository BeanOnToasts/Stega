#include <opencv2/opencv.hpp>
using namespace cv;
#include <iostream>
using namespace std;

#include <QApplication>
#include <QFile>
#include <QDebug>

#include "encode/encode.h"
#include "encrypt/encrypt.h"
#include "decode/decode.h"
#include "decrypt/decrypt.h"

#include "GUI/selectOption.h"


//loads the stylesheet
void ApplyStyleSheet(QApplication &app) {
    if (QFile file("../styles.qss"); file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        app.setStyleSheet(styleSheet);
        file.close();
    } else {
        qDebug() << "Failed to load stylesheet!";
    }
}

int main(int argc, char *argv[]) {
    string fileName;
    string message;
    string encrypted_message;
    int option;

    QApplication app(argc, argv);
    ApplyStyleSheet(app);

    SelectOption window;
    window.show();

    return app.exec();
}