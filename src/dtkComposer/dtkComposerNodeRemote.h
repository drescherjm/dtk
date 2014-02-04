/* @(#)dtkComposerNodeRemote.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 15:15:12
 * Version: $Id$
 * Last-Updated: mer. oct. 31 15:55:55 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 36
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEREMOTE_H
#define DTKCOMPOSERNODEREMOTE_H


#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeLeaf.h"

#include <QDomDocument>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRemote declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRemotePrivate;
class dtkDistributedCommunicator;
class dtkDistributedController;
class dtkDistributedSlave;

class  dtkComposerNodeRemote : public QObject, public dtkComposerNodeComposite
{
    Q_OBJECT

public:
             dtkComposerNodeRemote(void);
    virtual ~dtkComposerNodeRemote(void);

public:
    QString type(void);

public:
    QString titleHint(void);

public slots:
    void onJobStarted(QString id);

public:
    void setComposition(QDomDocument document);
    void setController(dtkDistributedController  *controller);
    void setCommunicator(dtkDistributedCommunicator  *communicator);
    void setSlave(dtkDistributedSlave *slave);
    void setJob(QString jobid);

public:
    bool isSlave(void);

public:
    virtual void begin(void);
    virtual void end(void);

private:
    dtkComposerNodeRemotePrivate *d;
};





// /////////////////////////////////////////////////////////////////
// Distributed submit
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRemoteSubmitPrivate;

class  dtkComposerNodeRemoteSubmit : public QObject, public dtkComposerNodeLeaf
{
    Q_OBJECT

public:
     dtkComposerNodeRemoteSubmit(void);
    ~dtkComposerNodeRemoteSubmit(void);

public:
    void run(void);

public slots:
    void onJobQueued(const QString& job_id);

public:
    inline QString type(void) {
        return "remoteSubmit";
    }

    inline QString titleHint(void) {
        return "Remote Submit";
    }


public:
    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "cluster";
        else if (port == 1)
            return "nodes";
        else if (port == 2)
            return "cores";
        else if (port == 3)
            return "walltime";
        else if (port == 4)
            return "queuename";
        else
            return "value";
    }

public:
    inline QString outputLabelHint(int) {
        return "jobid";
    }

public:
    void setSlaveName(QString);

protected:
    dtkComposerNodeRemoteSubmitPrivate *d;
};


#endif /* DTKCOMPOSERNODEREMOTE_H */
