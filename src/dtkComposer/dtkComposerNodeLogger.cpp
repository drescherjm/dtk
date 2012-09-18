/* dtkComposerNodeLog.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2008-2011 -Nicolas Niclausse , Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Sep 18 16:44:03 2012 (+0200)
 *           By: tkloczko
 *     Update #: 54
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */
#include "dtkComposerMetatype.h"

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
    QStringList list = d->receiver.allDataDescription();

    for(int i = 0; i < list.count(); ++i)
        dtkDebug() << list.at(i);
}

