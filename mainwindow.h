#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include <QtCore/QtGlobal>

#include "qcustomplot.h"

#define MAXSIZE 6
#define DATANUM 1000
#define GRAPHYRANGE 500

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_connect_clicked();
    void on_disconnect_clicked();
    void readData();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QCustomPlot *graph;
    QVector<double> magTVec;
    QVector<double> magXVec;
    QVector<double> magYVec;
    QVector<double> magZVec;
    QMutex mutex;

    char storedDataX[MAXSIZE+1];
    char storedDataY[MAXSIZE+1];
    char storedDataZ[MAXSIZE+1];

    void initGraph();
    void shiftData(QVector<double> vecX, QVector<double> vecY, QVector<double> vecZ);
};

#endif // MAINWINDOW_H
