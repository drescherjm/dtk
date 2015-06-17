/* @(#)dtkComposerNodeRemote.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 15:15:12
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerExport.h"

#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeLeaf.h"

#include <QDomDocument>
#include <QtNetwork>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRemote declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRemotePrivate;
class dtkDistributedCommunicator;
class dtkDistributedController;
class dtkDistributedSlave;

class DTKCOMPOSER_EXPORT dtkComposerNodeRemote : public QObject, public dtkComposerNodeComposite
{
    Q_OBJECT

public:
             dtkComposerNodeRemote(void);
    virtual ~dtkComposerNodeRemote(void);

public slots:
    void onJobStarted(QString id);

public:
    virtual void setComposition(QDomDocument document);
    virtual void setSocket(QTcpSocket  *socket);
    void setController(dtkDistributedController  *controller);
    void setCommunicator(dtkDistributedCommunicator  *communicator);
    void setSlave(dtkDistributedSlave *slave);
    void setJob(QString jobid);

public:
    virtual bool isSlave(void);

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

class DTKCOMPOSER_EXPORT dtkComposerNodeRemoteSubmit : public QObject, public dtkComposerNodeLeaf
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
    void setSlaveName(QString);

protected:
    dtkComposerNodeRemoteSubmitPrivate *d;
};

