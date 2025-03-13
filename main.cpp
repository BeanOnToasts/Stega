#include "GUI/selectOption.h"
#include <QApplication>

//loads the stylesheet
void ApplyStyleSheet(QApplication &app) {
    if (QFile file("../styles.qss"); file.open(QFile::ReadOnly)) {
        const QString styleSheet = QLatin1String(file.readAll());
        app.setStyleSheet(styleSheet);
        file.close();
    } else {
        qDebug() << "Failed to load stylesheet!";
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ApplyStyleSheet(app);

    SelectOption window;
    window.show();

    return app.exec();
}
