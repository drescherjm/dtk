/* dtkDistributedCommunicatorPlugin.h --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb  4 12:49:51 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb 11 18:24:48 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 13
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

public:
    virtual void   initialize(void) = 0;
    virtual void uninitialize(void) = 0;
};

Q_DECLARE_INTERFACE(dtkDistributedCommunicatorPlugin, "fr.inria.dtkDistributedCommunicatorPlugin")
