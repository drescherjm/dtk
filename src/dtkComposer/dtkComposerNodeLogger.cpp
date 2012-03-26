/* dtkComposerNodeLog.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2008-2011 -Nicolas Niclausse , Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: lun. mars 26 13:49:39 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 43
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
    dtkComposerTransmitterVariant *receiver;

};

dtkComposerNodeLogger::dtkComposerNodeLogger(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeLoggerPrivate)
{
    d->receiver = new dtkComposerTransmitterVariant(this);
    this->appendReceiver(d->receiver);
}

dtkComposerNodeLogger::~dtkComposerNodeLogger(void)
{
    delete d->receiver;
    delete d;

    d = NULL;
}

void dtkComposerNodeLogger::run(void)
{
    dtkInfo() << "run logger";
    foreach(QVariant q,  d->receiver->allData())
        if (q.canConvert(QVariant::String))
            dtkInfo() << q.toString();
        else
            dtkInfo() << q;
}

