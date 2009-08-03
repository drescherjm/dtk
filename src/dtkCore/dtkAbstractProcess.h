/* dtkAbstractProcess.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 16:00:26 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Thu May 28 15:08:27 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 107
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTPROCESS_H
#define DTKABSTRACTPROCESS_H

#include <dtkCore/dtkAbstractObject.h>

class dtkAbstractData;

class DTKCORE_EXPORT dtkAbstractProcess : public dtkAbstractObject
{
    Q_OBJECT

public:
             dtkAbstractProcess(      dtkAbstractProcess *parent = 0);
             dtkAbstractProcess(const dtkAbstractProcess& process);
    virtual ~dtkAbstractProcess(void);

    virtual QString description(void) const { return ""; }

    friend QDebug operator<<(QDebug debug, const dtkAbstractProcess& process);
    friend QDebug operator<<(QDebug debug,       dtkAbstractProcess *process);

public slots:

    void run(void);

    virtual void update(void);

    virtual void setParameter(double  data);
    virtual void setParameter(double  data, int channel);
    virtual void setParameter(double  data, int channel, int frame);

    virtual void setParameter(double *data, int count);
    virtual void setParameter(double *data, int count, int channel);
    virtual void setParameter(double *data, int count, int channel, int frame);

    virtual void setParameter(dtkAbstractObject*  data);
    virtual void setParameter(dtkAbstractObject*  data, int channel);
    virtual void setParameter(dtkAbstractObject*  data, int channel, int frame);

    virtual void setInput(dtkAbstractData *data);
    virtual void setInput(dtkAbstractData *data, int channel);
    virtual void setInput(dtkAbstractData *data, int channel, int frame);

    virtual void setData(void* data);
    virtual void setData(void* data, int channel);
    virtual void setData(void* data, int channel, int frame);

    virtual dtkAbstractData *output(void);
    virtual dtkAbstractData *output(int channel);
    virtual dtkAbstractData *output(int channel, int frame);

    virtual void *data (void);
    virtual void *data (int channel);
    virtual void *data (int channel, int frame);
};

QDebug operator<<(QDebug debug, const dtkAbstractProcess& process);
QDebug operator<<(QDebug debug,       dtkAbstractProcess *process);

#endif
