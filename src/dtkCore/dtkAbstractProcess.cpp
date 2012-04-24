/* dtkAbstractProcess.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 16:01:09 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 11:41:18 2012 (+0200)
 *           By: tkloczko
 *     Update #: 99
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkAbstractProcess.h"
#include "dtkAbstractProcess_p.h"

dtkAbstractProcess::dtkAbstractProcess(dtkAbstractProcess *parent) : dtkAbstractObject(*new dtkAbstractProcessPrivate, parent)
{

}

dtkAbstractProcess::dtkAbstractProcess(const dtkAbstractProcess& other) : dtkAbstractObject(*new dtkAbstractProcessPrivate(*other.d_func()), other)
{

}

dtkAbstractProcess::~dtkAbstractProcess(void)
{

}

dtkAbstractProcess& dtkAbstractProcess::operator=(const dtkAbstractProcess& other)
{
    dtkAbstractObject::operator=(other);

    return *this;
}

QDebug operator<<(QDebug debug, const dtkAbstractProcess& process)
{
    debug.nospace() << process.identifier();

    return debug.space();
}

QDebug operator<<(QDebug debug, dtkAbstractProcess *process)
{
    debug.nospace() << process->identifier();

    return debug.space();
}

int dtkAbstractProcess::run(void)
{
    int retval = this->update();

    if (retval == 0)
        emit success();
    else
        emit failure();

    return retval;
}

void dtkAbstractProcess::cancel (void)
{
    onCanceled ();
    emit canceled();
}

int dtkAbstractProcess::update(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return DTK_FAILURE;
}

void dtkAbstractProcess::onCanceled (void)
{
    DTK_DEFAULT_IMPLEMENTATION;  
}

bool dtkAbstractProcess::read(const QString& file)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(file);

    return false;
}

bool dtkAbstractProcess::read(const QStringList& files)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(files);

    return false;
}

bool dtkAbstractProcess::write(const QString& file)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(file);

    return false;
}

bool dtkAbstractProcess::write(const QStringList& files)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(files);

    return false;
}

void dtkAbstractProcess::setParameter(int data)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
}

void dtkAbstractProcess::setParameter(int data, int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(channel);
}

void dtkAbstractProcess::setParameter(int data, int channel, int frame)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(channel);
    DTK_UNUSED(frame);
}

void dtkAbstractProcess::setParameter(int* data)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
}

void dtkAbstractProcess::setParameter(int* data, int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(channel);
}

void dtkAbstractProcess::setParameter(int* data, int channel, int frame)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(channel);
    DTK_UNUSED(frame);
}

void dtkAbstractProcess::setParameter(double  data)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
}

void dtkAbstractProcess::setParameter(double  data, int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(channel);
}

void dtkAbstractProcess::setParameter(double  data, int channel, int frame)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(channel);
    DTK_UNUSED(frame);
}

void dtkAbstractProcess::setParameter(double *data, int count)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(count);
}

void dtkAbstractProcess::setParameter(double *data, int count, int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(count);
    DTK_UNUSED(channel);
}

void dtkAbstractProcess::setParameter(double *data, int count, int channel, int frame)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(count);
    DTK_UNUSED(channel);
    DTK_UNUSED(frame);
}

void dtkAbstractProcess::setParameter(dtkAbstractObject*  data)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
}

void dtkAbstractProcess::setParameter(dtkAbstractObject*  data, int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(channel);
}

void dtkAbstractProcess::setParameter(dtkAbstractObject*  data, int channel, int frame)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(channel);
    DTK_UNUSED(frame);
}

void dtkAbstractProcess::setInput(dtkAbstractData *data)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
}

void dtkAbstractProcess::setInput(dtkAbstractData *data, int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(channel);
}

void dtkAbstractProcess::setInput(dtkAbstractData *data, int channel, int frame)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(channel);
    DTK_UNUSED(frame);
}

void dtkAbstractProcess::setData(void *data)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
}

void dtkAbstractProcess::setData(void *data, int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(channel);
}

void dtkAbstractProcess::setData(void *data, int channel, int frame)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(channel);
    DTK_UNUSED(frame);
}

dtkAbstractData *dtkAbstractProcess::output(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return NULL;
}

dtkAbstractData *dtkAbstractProcess::output(int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(channel);

    return NULL;
}

dtkAbstractData *dtkAbstractProcess::output(int channel, int frame)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(channel);
    DTK_UNUSED(frame);

    return NULL;
}

void *dtkAbstractProcess::data(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return NULL;
}

void *dtkAbstractProcess::data(int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(channel);

    return NULL;
}

void *dtkAbstractProcess::data(int channel, int frame)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(channel);
    DTK_UNUSED(frame);

    return NULL;
}
