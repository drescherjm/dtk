/* dtkVrMaster.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 10 21:06:22 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar  2 11:04:40 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 32
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRMASTER_H
#define DTKVRMASTER_H

#include "dtkVrProcess.h"
#include "dtkVrTrackerVrpn.h"

class dtkVrMasterPrivate;

class dtkVrMaster : public dtkVrProcess
{
    Q_OBJECT

public:
     dtkVrMaster(dtkDistributedCommunicator *communicator);
    ~dtkVrMaster(void);

    virtual void   initialize(void);
    virtual void uninitialize(void);

    void setTracker(const QUrl& url);
    void setDevice(const QUrl& url);

protected slots:
    void onButtonPressed(int button);
    void onButtonReleased(int button);

protected:
    void process(void);

private:
    dtkVrMasterPrivate *d;
};

#endif
