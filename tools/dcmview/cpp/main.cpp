#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{    
    Q_INIT_RESOURCE(dcmview);

    QApplication app(argc, argv);

    MainWindow mainWindow;

    // Show main window and move it to center
    mainWindow.show();
    mainWindow.moveToDesktopCenter();

    return app.exec();
}
