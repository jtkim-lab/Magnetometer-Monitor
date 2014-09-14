#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSerialPort/QSerialPort>

#define MAXSIZE 6

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveValue()
{
    QLabel *xData = findChild<QLabel *>("label_5");
    QLabel *yData = findChild<QLabel *>("label_6");
    QLabel *zData = findChild<QLabel *>("label_7");

    QString portName = "/dev/tty.SLAB_USBtoUART";

    QSerialPort* serialPort1 = new QSerialPort(portName);

    serialPort1->setDataBits(QSerialPort::Data8);
    serialPort1->setParity(QSerialPort::NoParity);
    serialPort1->setBaudRate(QSerialPort::Baud57600);
    serialPort1->setStopBits(QSerialPort::OneStop);
    serialPort1->setFlowControl(QSerialPort::NoFlowControl);

    char receivedData[1000];//MAXSIZE*3+4];

    char storedDataX[MAXSIZE+1];
    char storedDataY[MAXSIZE+1];
    char storedDataZ[MAXSIZE+1];

    bool temp = true;

    while(temp)
    {
        if(serialPort1->open(QIODevice::ReadWrite))
        {
//            serialPort1->read(receivedData, 1);

//            while(receivedData[0] != '\n')
//            {
//                serialPort1->open(QIODevice::ReadWrite);
//                serialPort1->read(receivedData, 1);
//            }

//            serialPort1->open(QIODevice::ReadWrite);
       //     QByteArray receivedData;
            QByteArray receivedData = serialPort1->readAll();//MAXSIZE*3+4);
         //   int i = 0;

            receivedData[999] = '/0';

            xData->setText(receivedData);

//            for(i = 0; i != 22 && receivedData[i] != '\n'; i++);

  //          if(i != 22)
    //        {
   /*         storedDataX[0] = receivedData[i+1];
            storedDataX[1] = receivedData[i+2];
            storedDataX[2] = receivedData[i+3];
            storedDataX[3] = receivedData[i+4];
            storedDataX[4] = receivedData[i+5];
            storedDataX[5] = receivedData[i+6];
            storedDataX[6] = '\0';

            xData->setText(storedDataX);
            }
            else
            {
                break;
            }*/
/*            storedDataY[0] = receivedData[7];
            storedDataY[1] = receivedData[8];
            storedDataY[2] = receivedData[9];
            storedDataY[3] = receivedData[10];
            storedDataY[4] = receivedData[11];
            storedDataY[5] = receivedData[12];
            storedDataY[6] = '\0';

            yData->setText(storedDataY);

            storedDataZ[0] = receivedData[14];
            storedDataZ[1] = receivedData[15];
            storedDataZ[2] = receivedData[16];
            storedDataZ[3] = receivedData[17];
            storedDataZ[4] = receivedData[18];
            storedDataZ[5] = receivedData[19];
            storedDataZ[6] = '\0';

            zData->setText(storedDataZ);*/

            temp = false;
        }
    }
}
