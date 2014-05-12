/* main.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2014 - Nicolas Niclausse, Inria.
 * Created: 2014/04/30 09:54:08
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


// #include <QGuiApplication>
#include <QtQuick>
#include <dtkDistributed/dtkDistributedController.h>
#include <QtQml>
#include <QtQml/QQmlApplicationEngine>
#include <QtGui/QGuiApplication>

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    qmlRegisterType<dtkDistributedController>("dtkDistributed", 1, 0, "DistributedController");

    QQmlApplicationEngine engine(QUrl::fromLocalFile("dash.qml"));
    return app.exec();

}
