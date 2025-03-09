#ifndef SELECTOPTION_H
#define SELECTOPTION_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include "decodeWindow.h"
#include "encodeWindow.h"

/**
 * @brief allows user to select between encode or decode
 */
class SelectOption final : public QWidget {
    Q_OBJECT

    QPushButton *encodeButton;
    QPushButton *decodeButton;
    EncodeWindow *eWindow;
    DecodeWindow *dWindow;

    public:
    explicit SelectOption(QWidget *parent = nullptr);

    signals:
    void encodeSelected();
    void decodeSelected();

    private slots:
    void onEncodeClicked();
    void onDecodeClicked();
};


#endif //SELECTOPTION_H
