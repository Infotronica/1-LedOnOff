#include "widgetmain.h"
#include "ui_widgetmain.h"

WidgetMain::WidgetMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetMain)
{
    ui->setupUi(this);

    initializePins();
}

WidgetMain::~WidgetMain()
{
    delete ui;
}
void WidgetMain::initializePins() // prepare a GPIO pin in read mode
{
#if defined Q_OS_LINUX || defined Q_OS_DARWIN
    int i;

    for (i=1; i<28; i++)
    {
        setPinForWrite(i);
        turnOffPin(i);
    }
#endif
}

void WidgetMain::setPinForWrite(int pin) // prepare a GPIO pin in write mode
{
#if defined Q_OS_LINUX || defined Q_OS_DARWIN
    QFile qFile;
    QDir qDir;
    QString pinStr;

    pinStr=QString::number(pin);
    qDir.setCurrent("/sys/class/gpio/");
    qDir.mkdir("gpio"+pinStr);

    qFile.setFileName("/sys/class/gpio/export");
    qFile.open(QIODevice::WriteOnly);
    qFile.write(pinStr.toLocal8Bit().data());
    qFile.close();

    qFile.setFileName("/sys/class/gpio/gpio"+pinStr+"/direction");
    qFile.open(QIODevice::WriteOnly);
    qFile.write("out");
    qFile.close();
#else
    Q_UNUSED(pin)
#endif
}

void WidgetMain::turnOnPin(int pin) // turn on a GPIO pin
{
#if defined Q_OS_LINUX || defined Q_OS_DARWIN
    QFile qFile;
    QString pinStr;

    pinStr=QString::number(pin);
    qFile.setFileName("/sys/class/gpio/gpio"+pinStr+"/value");
    qFile.open(QIODevice::WriteOnly);
    qFile.write("1");
    qFile.close();
#else
    Q_UNUSED(pin)
#endif
}

void WidgetMain::turnOffPin(int pin) // turn on a GPIO pin
{
#if defined Q_OS_LINUX || defined Q_OS_DARWIN
    QFile qFile;
    QString pinStr;

    pinStr=QString::number(pin);
    qFile.setFileName("/sys/class/gpio/gpio"+pinStr+"/value");
    qFile.open(QIODevice::WriteOnly);
    qFile.write("0");
    qFile.close();
#else
    Q_UNUSED(pin)
#endif
}

void WidgetMain::setPinForRead(int pin) // prepare a GPIO pin in read mode
{
#if defined Q_OS_LINUX || defined Q_OS_DARWIN
    QFile qFile;
    QDir qDir;
    QString pinStr;

    pinStr=QString::number(pin);
    qDir.setCurrent("/sys/class/gpio/");
    qDir.mkpath("gpio"+pinStr);

    qFile.setFileName("/sys/class/gpio/export");
    qFile.open(QIODevice::WriteOnly);
    qFile.write(pinStr.toLocal8Bit().data());
    qFile.close();

    qFile.setFileName("/sys/class/gpio/gpio"+pinStr+"/direction");
    qFile.open(QIODevice::WriteOnly);
    qFile.write("in");
    qFile.close();
#else
    Q_UNUSED(pin)
#endif
}

int WidgetMain::readPin(int pin) // read a GPIO pin, if there is 3.3 volts the value will be 1 otherwise it will be 0
{
    int valor=0;
#if defined Q_OS_LINUX || defined Q_OS_DARWIN
    QFile qFile;
    char c;
    QString pinStr,str;
    QByteArray qByteArray;

    pinStr=QString::number(pin);
    str="/sys/class/gpio/gpio"+pinStr+"/value";
    qFile.setFileName(str);
    qFile.open(QIODevice::ReadOnly);
    qByteArray=qFile.readAll();
    qFile.close();
    c=qByteArray.at(0);
    valor=static_cast<int>(c);
    valor-=48;
#else
    Q_UNUSED(pin)
#endif
    return valor;
}

void WidgetMain::on_btnOn_clicked()
{
    setPinForWrite(21);
    turnOnPin(21);
}

void WidgetMain::on_btnOff_clicked()
{
    setPinForWrite(21);
    turnOffPin(21);
}
