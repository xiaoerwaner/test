#ifndef TCPSERVERWIDGET_H
#define TCPSERVERWIDGET_H

#include <QWidget>

#include<QTcpServer>//监听套接字
#include<QTcpSocket>//通信套接字

namespace Ui {
class TcpServerWidget;
}

class TcpServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TcpServerWidget(QWidget *parent = nullptr);
    ~TcpServerWidget();

private slots:
    void on_pushButton_send_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TcpServerWidget *ui;


    QTcpServer *tcpserver;
    QTcpSocket *tcpsocket;
};

#endif // TCPSERVERWIDGET_H
