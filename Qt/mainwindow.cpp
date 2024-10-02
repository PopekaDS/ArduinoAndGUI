#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <QByteArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("Введите текст");

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        ui->cmbPort->addItem(serialPortInfo.portName());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    QSerialPort serialPort;

    serialPort.setPortName(this->ui->cmbPort->currentText());
    serialPort.setBaudRate(QSerialPort::Baud9600);

    if (!serialPort.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
        return;
    }

    QString qs = ui->lineEdit->text();
    QByteArray login_ba = qs.toUtf8();

    int login_ba_size = qs.size();
    QByteArray q_b;
    if(login_ba_size <= 16) {
        // Отправляем 0
        q_b.setNum(0);
        serialPort.write(q_b);
    } else {
        // Отправляем 1
        // Следом отправляем размер строки
        q_b.setNum(1);
        serialPort.write(q_b);
        q_b.setNum(login_ba_size);
        serialPort.write(q_b);
    }

    // Отправляем строку
    serialPort.write(login_ba);
    serialPort.waitForBytesWritten();

    QByteArray data;
    while (serialPort.waitForReadyRead(10)) {
        data.append(serialPort.readAll());
    }

    ui->txtOutput->append(data);

    serialPort.close();
    ui->lineEdit->clear();
}

