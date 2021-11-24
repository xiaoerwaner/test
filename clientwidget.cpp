#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    //动态分配存储空间，指定父对象
   tcpsocket = new QTcpSocket(this);

   //建立tcpsocket 套接字，建立连接就会触发此信号
   connect(tcpsocket,&QTcpSocket::connected,
           [=](){

       ui->textEdit_read->setText("成功和服务器建立连接");

   });

   //获取对方发送的数据


   connect(tcpsocket,&QTcpSocket::readyRead,
           [=](){
       //获取对方发送的内容
       QByteArray array =tcpsocket->readAll();
       //追加到编辑区中
       ui->textEdit_write->append(array);

   });


}

ClientWidget::~ClientWidget()
{
    delete ui;
}

//connect连接
void ClientWidget::on_pushButton_connect_clicked()
{
    //获取服务器IP和端口
    QString  ip = ui->lineEdit_ip->text();
    qint16 port = ui->lineEdit_port->text().toInt();

    //主动和服务器建立连接
    tcpsocket->connectToHost(QHostAddress(ip),port);
}



void ClientWidget::on_pushButton_send_clicked()
{
    //获取编辑区的内容
    QString str = ui->textEdit_read->toPlainText();

    //发送数据
    tcpsocket->write(str.toUtf8().data());


}


void ClientWidget::on_pushButton_close_clicked()
{
    //主动与服务器端关闭连接
    tcpsocket->disconnectFromHost();
    tcpsocket->close();
}
