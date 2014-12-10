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


#include <dtkDistributed/dtkDistributed.h>
#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedController.h>
#include <dtkDistributed/dtkDistributedPolicy.h>
#include <dtkDistributed/dtkDistributedSettings.h>

#include <QtQml>
#include <QtQml/QQmlApplicationEngine>
#include <QtQuick>
#include <QGuiApplication>

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    qmlRegisterType<dtkDistributedController>("dtkDistributed", 1, 0, "DistributedController");
    qmlRegisterType<dtkDistributedPolicy>("dtkDistributed", 1, 0, "DistributedPolicy");

    dtkDistributedSettings settings;
    settings.beginGroup("communicator");
    dtkDistributed::communicator::pluginManager().initialize(settings.value("plugins").toString());
    settings.endGroup();

    QQmlApplicationEngine engine(QUrl::fromLocalFile("dash.qml"));
    return app.exec();

}

