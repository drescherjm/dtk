/* dtkVrProcess.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 10 21:08:39 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr 29 12:31:42 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 75
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRPROCESS_H
#define DTKVRPROCESS_H

#include <QtCore>

class dtkDistributedCommunicator;
class dtkVrDevice;
class dtkVrProcessPrivate;

class dtkVrProcess : public QObject
{
    Q_OBJECT

public:
             dtkVrProcess(dtkDistributedCommunicator *communicator);
    virtual ~dtkVrProcess(void);

    virtual void   initialize(void) = 0;
    virtual void uninitialize(void) = 0;

    void show(bool fullscreen = false);

    void start(void);
    void stop(void);

    int rank(void) const;
    int size(void) const;

    bool running(void);

protected:
    virtual void process(void) = 0;

    void broadcast(void);
    void synchronize(void);

private:
    dtkVrProcessPrivate *d;
};

#endif
