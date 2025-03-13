#ifndef SELECTOPTION_H
#define SELECTOPTION_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>

#include "decodeWindow.h"
#include "encodeWindow.h"

/**
 * @brief allows user to select between encode or decode
 */
class SelectOption final : public QWidget {
    Q_OBJECT

    QPushButton *encodeButton;
    QPushButton *decodeButton;
    QPushButton *quitButton;
    EncodeWindow *eWindow;
    DecodeWindow *dWindow;

    void onEncodeClicked();
    void onDecodeClicked();

    static void onQuitClicked();

    public:
    explicit SelectOption(QWidget *parent = nullptr);
};


#endif //SELECTOPTION_H
