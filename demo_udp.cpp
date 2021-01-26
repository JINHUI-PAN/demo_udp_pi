#include "demo_udp.h"
#include "ui_demo_udp.h"
#include <wiringPi.h>
#include <stdio.h>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QTime>
#include <QDateTime>

demo_udp::demo_udp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::demo_udp)
{
    ui->setupUi(this);
    mSocket = new QUdpSocket();
    mSocket->bind(QHostAddress::AnyIPv4,6655);
   // mSocket->bind(QHostAddress("192.168.0.46"),6655);
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(read_data()));
    //  qDebug()<<" data kkk";
   //   wiringPiSetup();
   //   pinMode(15,INPUT);

}

demo_udp::~demo_udp()
{
    delete ui;
}

void demo_udp::on_pushButton_clicked()
{
    //json
     QJsonObject jsonobject;
    // QTime cu_time = QTime::currentTime();
     QDateTime cu_time = QDateTime::currentDateTime();
     QString  data_new;
     int msec ;
     int data = 0;
     jsonobject.insert("senderId","QT_Client");
     jsonobject.insert("receiverId","Unity_Client");  //Unity_Client  //UE4_Client
     jsonobject.insert("action",5);
     jsonobject.insert("msg",data);
     jsonobject.insert("ip","192.168.0.204");
     jsonobject.insert("port",6655);

   //  jsonobject.insert("name","xiaoxiao");
   // jsonobject.insert("age","18");
     for(int i = 0 ; i < 20 ; i++)
     {
         data = data+2;
       //  jsonobject.insert("msg",data);
       //  data_new = cu_time.toString("yyyy.MM.dd.hh.mm:ss.zzz ddd");
       //  jsonobject.insert("time",data_new);
     QJsonDocument jsondocument;
     jsondocument.setObject(jsonobject);
     QByteArray dataArray  = jsondocument.toJson();
    //danbo
    //qint64 len = mSocket->writeDatagram(ui->textEdit->toPlainText().toUtf8(),QHostAddress("192.168.0.102"),6677);
    qint64 len = mSocket->writeDatagram(dataArray/*ui->textEdit->toPlainText().toUtf8()*/,QHostAddress(address1),port1);
    //delayMicroseconds(5000);

   //  msec = cu_time.msec();
    // qDebug()<<"time msec"  <<msec;

    //guangbo
   // qint64 len = mSocket->writeDatagram(dataArray/*ui->textEdit->toPlainText().toUtf8()*/,QHostAddress::Broadcast,6677);
     }
     data_new = cu_time.toString("yyyy.MM.dd.hh.mm:ss.zzz ddd");
     qDebug()<<"time msec1"  <<data_new;
}

void demo_udp::read_data()
{
    //json
    QJsonParseError json_err;
    QJsonDocument json_doc;


    QByteArray array;
    QHostAddress address;
    quint16  port ;
    array.resize(mSocket->bytesAvailable()) ;  //have data
    mSocket->readDatagram(array.data(),array.size(),&address,&port);

    json_doc = QJsonDocument::fromJson(array,&json_err);
    if(json_err.error != QJsonParseError::NoError)
    {
        qDebug()<<" data error";
       // return  false;
    }else {

        if(json_doc.isObject())
        {
              QJsonObject obj  = json_doc.object();
              if(obj.contains("action"))
              {

                  QJsonValue   act_value =obj.take("action");
                 int act  = act_value.toInt();

              if(act == 6 && ip_fale)
                 {
                  ip_fale = false;

              if(obj.contains("ip"))
              {
                  QJsonValue name_value = obj.take("ip");
                address1= name_value.toString();
                  qDebug()<< "%s" << address1;
              }
              if(obj.contains("udp_port"))
              {
                  QJsonValue port_value = obj.take("udp_port");
                 port1 = port_value.toInt();
                 qDebug()<< "%p" << port1;
              }
              }else if(act == 5 )
              {
                  QString  data_new;
                  int msec ;
                 // obj.contains()
                  QDateTime cu_time = QDateTime::currentDateTime();
                  data_new = cu_time.toString("yyyy.MM.dd.hh.mm:ss.zzz ddd");
                  qDebug()<<"time msec"  <<data_new;


              }
        }

        }



}


    ui->listWidget->addItem(array);
}

void demo_udp::IoDate()
{


    digitalRead(15);
}

