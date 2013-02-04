/* dtkDistributedCommunicatorPlugin.h --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb  4 12:49:51 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb  4 12:50:23 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore/QObject>

class dtkDistributedCommunicatorPlugin : public QObject
{
    Q_OBJECT

public:
             dtkDistributedCommunicatorPlugin(void) {}
    virtual ~dtkDistributedCommunicatorPlugin(void) {}
};

Q_DECLARE_INTERFACE(dtkDistributedCommunicatorPlugin, "fr.inria.dtkDistributedCommunicatorPlugin")
