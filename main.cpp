#include "demo_udp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    demo_udp w;
    w.show();

    return a.exec();
}
