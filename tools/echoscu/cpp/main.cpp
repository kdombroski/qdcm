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

    echoScu.setHost("localhost");
    echoScu.setPort(104);
    echoScu.setCallingAE("SCU");
    echoScu.setCalledAE("SCP");

    QTimer timer;
    QObject::connect(&echoScu, SIGNAL(over()), &app, SLOT(quit()));

    timer.singleShot(100, &echoScu, SLOT(perform()));

    app.exec();
}
