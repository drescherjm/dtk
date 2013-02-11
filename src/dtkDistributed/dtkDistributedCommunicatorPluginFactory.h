/* dtkDistributedCommunicatorPluginFactory.h --- 
 * 
 * Author: Julien Wintz
 * Created: Fri Feb  8 16:17:21 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb 11 18:37:37 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 36
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>

class dtkDistributedCommunicator;
class dtkDistributedCommunicatorPluginFactoryPrivate;

class dtkDistributedCommunicatorPluginFactory : public QObject
{
    Q_OBJECT

public:
    typedef dtkDistributedCommunicator (*creator) (void);

public:
     dtkDistributedCommunicatorPluginFactory(void);
    ~dtkDistributedCommunicatorPluginFactory(void);

public slots:
    dtkDistributedCommunicator create(const QString& key);

public:
    QStringList keys(void);

public:
    void record(QString key, creator func);

private:
    dtkDistributedCommunicatorPluginFactoryPrivate *d;
};
