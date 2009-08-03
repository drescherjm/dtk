#include <QtGui/QApplication>
#include "tstMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    tstMainWindow window; window.show();

    return application.exec();
}
