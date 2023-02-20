#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_speedBtn_pressed();
    void on_leftBtn_pressed();
    void on_rightBtn_pressed();
    void on_upBtn_pressed();
    void on_downBtn_pressed();
    void on_serialBtn_pressed();


private:
    Ui::MainWindow *ui;
    QSerialPort *serial;

};
#endif // MAINWINDOW_H
