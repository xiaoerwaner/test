#include "tcpserverwidget.h"
#include "ui_tcpserverwidget.h"

TcpServerWidget::TcpServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpServerWidget)
{
    ui->setupUi(this);

    tcpserver = nullptr;
    tcpsocket = nullptr;

    //动态分配内存空间
    tcpserver = new QTcpServer(this);

    //监听IP以及端口
    tcpserver->listen(QHostAddress::Any,8888);

    //设置窗口的名字
    setWindowTitle("服务器端");

    //建立连接套接字
    connect(tcpserver,&QTcpServer::newConnection,
            [=](){

        //从套接字获取信息
        tcpsocket = tcpserver->nextPendingConnection();

        //获取端口以及ip
        QString ip = tcpsocket->peerAddress().toString();
        qint16 port = tcpsocket->peerPort();
        QString temp = QString("[%1:%2]:成功建立连接").arg(ip).arg(port);

        ui->textEdit_read->setText(temp);


        //数据发送成功，套接字会触发对应的槽函数
        connect(tcpsocket,&QTcpSocket::readyRead,
                [=](){

            //从套接字中获取内容
            QByteArray array = tcpsocket->readAll();
            ui->textEdit_read->append(array);
        });
    });

}

TcpServerWidget::~TcpServerWidget()
{
    delete ui;
}

void TcpServerWidget::on_pushButton_send_clicked()
{
    if(nullptr == tcpserver){
        return;

    }

    //获取编辑区内容
    QString str = ui->textEdit_write->toPlainText();

    //给对方发送数据，使用套接字
    tcpsocket->write(str.toUtf8().data());
}

void TcpServerWidget::on_pushButton_2_clicked()
{
    if(nullptr == tcpserver){
        return;

    }
    //主动关闭连接
    tcpsocket->disconnectFromHost();
    tcpsocket->close();
}
