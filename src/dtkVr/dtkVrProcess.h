/* dtkVrProcess.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 10 21:08:39 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon May  9 14:47:37 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 78
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

protected:
    void broadcast(void);
    void synchronize(void);

private:
    dtkVrProcessPrivate *d;
};

#endif
