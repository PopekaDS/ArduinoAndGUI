/*
* Допустимые символы:
* !#$%&'()*+,-./:;<=>^_|"[]?@
* 0-9
* A-Z
* a-z
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include <QByteArray>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("Введите текст");
    ui->lineEdit->setFocus();
    ui->txtOutput->setReadOnly(true);

    // Разрешенные сиволы для ввода: 0-9, A-Z, a-z и !#$%&'()*+,-./:;<=>^_|"[]?@
    QRegularExpression re("^[a-zA-Z0-9!#$%& '()*+,-.//:;<=>^_|\"\\[\\]\\?\\@]*$");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(re, this);
    ui->lineEdit->setValidator(validator);

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        ui->cmbPort->addItem(serialPortInfo.portName());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
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
    // Отправляем первый байт
    if(login_ba_size <= 16) {
        // Отправляем 0
        q_b.setNum(0);
        serialPort.write(q_b);
    } else {
        // Отправляем 1
        q_b.setNum(1);
        serialPort.write(q_b);
    }

    // Отправляем строку
    serialPort.write(login_ba);
    serialPort.waitForBytesWritten();

    QByteArray data;
    while (serialPort.waitForReadyRead(10) || data.isEmpty()) {
        data.append(serialPort.readAll());
    }

    data[0] = '>';
    ui->txtOutput->append(QString(data));

    serialPort.close();
    ui->lineEdit->clear();
}

void MainWindow::on_lineEdit_returnPressed()
{
    emit on_pushButton_clicked();
}
