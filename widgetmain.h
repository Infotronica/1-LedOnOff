#ifndef WIDGETMAIN_H
#define WIDGETMAIN_H

#include <QWidget>
#include <QDir>
#include <QFile>

namespace Ui {
class WidgetMain;
}

class WidgetMain : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetMain(QWidget *parent = nullptr);
    ~WidgetMain();

    void initializePins();
    void setPinForWrite(int pin);
    void turnOnPin(int pin);
    void turnOffPin(int pin);
    void setPinForRead(int pin);
    int readPin(int pin);

private slots:
    void on_btnOn_clicked();

    void on_btnOff_clicked();

private:
    Ui::WidgetMain *ui;
};

#endif // WIDGETMAIN_H
