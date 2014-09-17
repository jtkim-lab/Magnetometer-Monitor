#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);
    graph = ui->widget;

    initGraph();

    ui->connectButton->setEnabled(true);
    ui->disconnectButton->setEnabled(false);

    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(on_connect_clicked()));
    connect(ui->disconnectButton, SIGNAL(clicked()), this, SLOT(on_disconnect_clicked()));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connect_clicked()
{
    serial->setPortName(QString("/dev/tty.SLAB_USBtoUART"));
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setBaudRate(QSerialPort::Baud57600);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setReadBufferSize(60);

    if (serial->open(QIODevice::ReadOnly))
    {
        ui->connectButton->setEnabled(false);
        ui->disconnectButton->setEnabled(true);
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Fail to Connect"));
    }
}

void MainWindow::on_disconnect_clicked()
{
    serial->close();

    ui->connectButton->setEnabled(true);
    ui->disconnectButton->setEnabled(false);
}

void MainWindow::readData()
{
    QByteArray data = serial->read(60);

    int size = data.size() - 30;

    QLabel *xData = findChild<QLabel *>("label_5");
    QLabel *yData = findChild<QLabel *>("label_6");
    QLabel *zData = findChild<QLabel *>("label_7");

    int i = 0;
    bool b = false;

    if(size == -7)
    {
        if(data[0] == '-' || data[0] == '0')
        {
            magXVec.pop_back();
            magYVec.pop_back();
            magZVec.pop_back();

            storedDataX[0] = data[i+0];
            storedDataX[1] = data[i+1];
            storedDataX[2] = data[i+2];
            storedDataX[3] = data[i+3];
            storedDataX[4] = data[i+4];
            storedDataX[5] = data[i+5];
            storedDataX[6] = '\0';

            xData->setText(storedDataX);
            magXVec.push_front(atof(storedDataX));

    storedDataY[0] = data[i+7];
    storedDataY[1] = data[i+8];
    storedDataY[2] = data[i+9];
    storedDataY[3] = data[i+10];
    storedDataY[4] = data[i+11];
    storedDataY[5] = data[i+12];
    storedDataY[6] = '\0';

    yData->setText(storedDataY);
    magYVec.push_front(atof(storedDataY));

    storedDataZ[0] = data[i+14];
    storedDataZ[1] = data[i+15];
    storedDataZ[2] = data[i+16];
    storedDataZ[3] = data[i+17];
    storedDataZ[4] = data[i+18];
    storedDataZ[5] = data[i+19];
    storedDataZ[6] = '\0';

    zData->setText(storedDataZ);
    magZVec.push_front(atof(storedDataZ));

    graph->graph(0)->setData(magTVec, magXVec);
    graph->graph(1)->setData(magTVec, magYVec);
    graph->graph(2)->setData(magTVec, magZVec);
    graph->replot();
        }
    }

    while(!b && size >= i && data.size() == serial->readBufferSize())
    {
        if(data[i] == '\r')
        {
            i++;

            if(data[i] == '\n')
            {
                i++;
                b = true;
            }
            else
                i++;
        }
        else
            i++;
    }

    mutex.lock();

    if(b && size >= i && data.size() == serial->readBufferSize())
    {
        if(data[i+0] == '-' || data[i+0] == '0')
        {
            magXVec.pop_back();
            magYVec.pop_back();
            magZVec.pop_back();

            storedDataX[0] = data[i+0];
            storedDataX[1] = data[i+1];
            storedDataX[2] = data[i+2];
            storedDataX[3] = data[i+3];
            storedDataX[4] = data[i+4];
            storedDataX[5] = data[i+5];
            storedDataX[6] = '\0';

            xData->setText(storedDataX);
            magXVec.push_front(atof(storedDataX));

    storedDataY[0] = data[i+7];
    storedDataY[1] = data[i+8];
    storedDataY[2] = data[i+9];
    storedDataY[3] = data[i+10];
    storedDataY[4] = data[i+11];
    storedDataY[5] = data[i+12];
    storedDataY[6] = '\0';

    yData->setText(storedDataY);
    magYVec.push_front(atof(storedDataY));

    storedDataZ[0] = data[i+14];
    storedDataZ[1] = data[i+15];
    storedDataZ[2] = data[i+16];
    storedDataZ[3] = data[i+17];
    storedDataZ[4] = data[i+18];
    storedDataZ[5] = data[i+19];
    storedDataZ[6] = '\0';

    zData->setText(storedDataZ);
    magZVec.push_front(atof(storedDataZ));

    graph->graph(0)->setData(magTVec, magXVec);
    graph->graph(1)->setData(magTVec, magYVec);
    graph->graph(2)->setData(magTVec, magZVec);
    graph->replot();
    }
    }

    mutex.unlock();
    //serial->clear();
    //sleep(1);
}

void MainWindow::initGraph()
{
    graph->addGraph();
    graph->addGraph();
    graph->addGraph();

    graph->graph(0)->setPen(QPen(QColor(255,0,0,255)));
    graph->graph(1)->setPen(QPen(QColor(0,255,0,255)));
    graph->graph(2)->setPen(QPen(QColor(0,0,255,255)));

    graph->xAxis->setLabel("time");
    graph->yAxis->setLabel("value");

    graph->xAxis->setRange(0, 10);
    graph->yAxis->setRange(-GRAPHYRANGE, GRAPHYRANGE);


    magTVec.resize(DATANUM);
    magXVec.resize(DATANUM);
    magYVec.resize(DATANUM);
    magZVec.resize(DATANUM);

    for(int i = 0; i < DATANUM; i++)
    {
        magTVec[i] = (double) i / (double) DATANUM * 10.0;

        magXVec.pop_back();
        magYVec.pop_back();
        magZVec.pop_back();

        magXVec.push_front(100.0);
        magYVec.push_front(0.0);
        magZVec.push_front(-100.0);
    }

    graph->graph(0)->setData(magTVec, magXVec);
    graph->graph(1)->setData(magTVec, magYVec);
    graph->graph(2)->setData(magTVec, magZVec);

    graph->replot();
}

void MainWindow::shiftData(QVector<double> vecX, QVector<double> vecY, QVector<double> vecZ)
{
    for(int i = DATANUM-1; i > 0; i--)
    {
        vecX[i] = vecX[i-1];
        vecY[i] = vecY[i-1];
        vecZ[i] = vecZ[i-1];
    }
}
