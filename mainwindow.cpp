#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    ui->serialComboBox->addItem(info.portName());

    ui->speedLineEdit->setValidator( new QIntValidator(0, 16, this) );
    ui->angleLineEdit->setValidator( new QIntValidator(0, 2700, this) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_serialBtn_pressed()
{
    if (serial->isOpen())
    {
        serial->close();
        ui->serialBtn->setText("Открыть порт");
    }
    else
    {

        ui->serialBtn->setText("Закрыть порт");
        serial->setBaudRate(QSerialPort::Baud57600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            if (info.portName() == ui->serialComboBox->currentText())
            {
                serial->setPort(info);
            }

        }
        serial->open(QSerialPort::ReadWrite);
    }
}

void MainWindow::on_speedBtn_pressed()
{
    QByteArray ba;
    QDataStream stream(&ba, QIODevice::WriteOnly);
    stream << (uchar)0xfa;
    stream << (uchar)0xce;
    stream << (uchar)0x02;
    stream << (uchar)0x00;
    stream << (uchar)ui->speedLineEdit->text().toInt();

    serial->write(ba);
//    qDebug() << ba.toHex();
}

void MainWindow::on_rightBtn_pressed()
{
    QByteArray ba;
    QDataStream stream(&ba, QIODevice::WriteOnly);
    stream << (uchar)0xfa;
    stream << (uchar)0xce;
    stream << (uchar)0x04;
    stream << (uchar)0x01;
    stream << ui->angleLineEdit->text().toShort();
    stream << (uchar)0x01;

    serial->write(ba);
//    qDebug() << ba.toHex();
}

void MainWindow::on_leftBtn_pressed()
{
    QByteArray ba;
    QDataStream stream(&ba, QIODevice::WriteOnly);
    stream << (uchar)0xfa;
    stream << (uchar)0xce;
    stream << (uchar)0x04;
    stream << (uchar)0x01;
    stream << ui->angleLineEdit->text().toShort();
    stream << (uchar)0x00;

    serial->write(ba);
//    qDebug() << ba.toHex();
}
