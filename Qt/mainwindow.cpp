#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    // создали экземпляр для общения по последовательному порту
    QSerialPort serialPort;

    // указали имя к какому порту будем подключаться
    serialPort.setPortName(this->ui->cmbPort->currentText());
    // указали скорость
    serialPort.setBaudRate(QSerialPort::Baud9600);

    // пробуем подключится
    if (!serialPort.open(QIODevice::ReadWrite)) {
        // если подключится не получится, то покажем сообщение с ошибкой
        QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
        return;
    }

    // отправляем строку с b нашей арудинкой
    serialPort.write("b"); // очень важно, что именно двойные кавычки
    serialPort.waitForBytesWritten(); // ждем пока дойдет

    /*
    // и не знаю с чем тут связано, но, чтобы сообщение дошло
    // надо обязательно прочитать не пришло ли нам чего в ответ
    //
    // функция waitForReadyRead(10) проверят не появилось
    // в ближайшие 10 миллисекунд чего-нибудь в ответ
    while (serialPort.waitForReadyRead(10)) {
        // и если появилось мы просто это читаем в пустоту
        serialPort.readAll();

        // сам while необходим для того что ответ приходит порциями
        // и мы хотим считать все что отправилось
    }
    */
    QByteArray data;  // специальный тип QT для хранения последовательности байтов
    while (serialPort.waitForReadyRead(10)) {
        // вместо холостого чтения накапливаем результат в переменную data
        data.append(serialPort.readAll());
    }

    // добавляем строку с содержимым data в поле txtOutput
    ui->txtOutput->append(data);

    // ну и закрываем порт
    serialPort.close();
}


void MainWindow::on_pushButton_2_clicked()
{
    QSerialPort serialPort;

    serialPort.setPortName(this->ui->cmbPort->currentText());
    serialPort.setBaudRate(QSerialPort::Baud9600);

    if (!serialPort.open(QIODevice::ReadWrite)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось подключится к порту");
        return;
    }

    serialPort.write("r"); // меняем тут b на r
    serialPort.waitForBytesWritten();

    QByteArray data;
    while (serialPort.waitForReadyRead(10)) {
        data.append(serialPort.readAll());
    }

    ui->txtOutput->append(data);

    serialPort.close();
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

    serialPort.write("New text"); // меняем тут b на r
    serialPort.waitForBytesWritten();

    QByteArray data;
    while (serialPort.waitForReadyRead(10)) {
        data.append(serialPort.readAll());
    }

    ui->txtOutput->append(data);

    serialPort.close();
}

