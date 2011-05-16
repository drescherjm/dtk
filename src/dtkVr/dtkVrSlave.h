/* dtkVrSlave.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 10 21:06:57 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon May  9 14:45:37 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 68
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRSLAVE_H
#define DTKVRSLAVE_H

#include "dtkVrProcess.h"

#include <QtGui>

class dtkAbstractView;
class dtkVec3;
class dtkVrSlavePrivate;
class dtkQuat;

class dtkVrSlave : public dtkVrProcess
{
    Q_OBJECT

public:
             dtkVrSlave(dtkDistributedCommunicator *communicator);
    virtual ~dtkVrSlave(void);

    void   initialize(void);
    void uninitialize(void);

    void show(void);
    void showFullScreen(void);

    void resize(int w, int h);
    void move(int x, int y);

    void setView(dtkAbstractView *view);
    void setStereo(bool on);

protected:
    void process(void);

private:
    dtkVrSlavePrivate *d;
};

#endif
