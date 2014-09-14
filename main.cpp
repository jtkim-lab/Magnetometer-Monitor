#include "mainwindow.h"
#include <QApplication>
#include <QtSerialPort/QSerialPort>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QSerialPort serialPort1;

    serialPort1.setPortName("/dev/tty.SLAB_USBtoUART");
    serialPort1.setDataBits(JTSerialPort::Data8);
    serialPort1.setReadBufferSize(dataSize);
    serialPort1.setParity(JTSerialPort::NoParity);
    serialPort1.setBaudRate(JTSerialPort::Baud57600);
    serialPort1.setStopBits(JTSerialPort::OneStop);
    serialPort1.setFlowControl(JTSerialPort::NoFlowControl);
    serialPort1.open(QIODevice::ReadOnly);



    return a.exec();
}
