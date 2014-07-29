// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include <QtGui>
#include <QtQml>

int main(int argc, char **argv)
{
    QGuiApplication application(argc, argv);

    QQmlApplicationEngine engine(QUrl("qrc:/main.qml"));

    return application.exec();
}

//
// main.cpp ends here
