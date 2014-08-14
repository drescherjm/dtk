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

#include "dtkPluginStoreController.h"

int main(int argc, char **argv)
{
    QGuiApplication application(argc, argv);

    qmlRegisterType<dtkPluginStoreController>("dtkPluginStoreQuick", 1, 0, "PluginStoreController");

    QQmlApplicationEngine engine(QUrl("qrc:/main.qml"));

    return application.exec();
}

//
// main.cpp ends here
