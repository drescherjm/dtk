#include <QtGui/QApplication>

#include "tstMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    application.setApplicationName("dtkTextEditor");
    application.setOrganizationName("inria");

    tstMainWindow window; window.show();

    return application.exec();
}
