/* dtkDistributedCommunicatorPluginFactory.h --- 
 * 
 * Author: Julien Wintz
 * Created: Fri Feb  8 16:17:21 2013 (+0100)
 * Version: 
 * Last-Updated: 2013 Thu Feb 28 14:43:48 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 49
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkCore/dtkCorePluginFactory.h>

#include "dtkDistributedCommunicator.h"

class dtkDistributedCommunicatorPluginFactory : public dtkCorePluginFactory<dtkDistributedCommunicator> {};

#if 0

#include <QtCore>

class dtkDistributedCommunicator;
class dtkDistributedCommunicatorPluginFactoryPrivate;

class dtkDistributedCommunicatorPluginFactory : public QObject
{
    Q_OBJECT

public:
    typedef dtkDistributedCommunicator *(*creator) (void);

public:
     dtkDistributedCommunicatorPluginFactory(void);
    ~dtkDistributedCommunicatorPluginFactory(void);

public slots:
    dtkDistributedCommunicator *create(const QString& key);

public:
    QStringList keys(void);

public:
    void record(QString key, creator func);

private:
    dtkDistributedCommunicatorPluginFactoryPrivate *d;
};

#endif
