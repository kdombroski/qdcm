#include <QCoreApplication>
#include <QTimer>
#include "CEchoSCU.h"

void printUsage()
{
    qDebug() << "USAGE:\n"
                "echoscu "
                "--host=<host> "
                "--port=<port> "
                "--ae=<application entity> "
                "[--thisae=<caller AE>]";
}

int main(int argc, char *argv[])
{    
    QCoreApplication app(argc, argv);

    CEchoSCU echoScu;
    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &echoScu, SLOT(perform()));

    app.exec();
}
