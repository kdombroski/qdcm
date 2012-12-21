#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{    
    Q_INIT_RESOURCE(dcmview);

    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
