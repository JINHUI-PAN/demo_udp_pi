#ifndef DEMO_UDP_H
#define DEMO_UDP_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QNetworkAddressEntry>
#include <wiringPi.h>
namespace Ui {
class demo_udp;
}

class demo_udp : public QMainWindow
{
    Q_OBJECT

public:
    explicit demo_udp(QWidget *parent = nullptr);
    ~demo_udp();
    bool ip_fale = true;

private slots:
    void on_pushButton_clicked();
    void read_data();
    void IoDate();

private:
    Ui::demo_udp *ui;
    QUdpSocket *mSocket;
    QString address1 = "192.168.0.46";
    quint16  port1  = 5566;
};

#endif // DEMO_UDP_H
