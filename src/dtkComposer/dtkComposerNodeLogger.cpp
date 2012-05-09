/* dtkComposerNodeLog.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2008-2011 -Nicolas Niclausse , Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed May  9 09:58:42 2012 (+0200)
 *           By: tkloczko
 *     Update #: 45
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeLogger.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkLog/dtkLog.h>

class dtkComposerNodeLoggerPrivate
{
public:
    dtkComposerTransmitterVariant receiver;

};

dtkComposerNodeLogger::dtkComposerNodeLogger(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeLoggerPrivate)
{
    this->appendReceiver(&(d->receiver));
}

dtkComposerNodeLogger::~dtkComposerNodeLogger(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeLogger::run(void)
{
    foreach(QVariant q,  d->receiver.allData())
        if (q.canConvert(QVariant::String))
            dtkInfo() << q.toString();
        else
            dtkInfo() << q;
}

