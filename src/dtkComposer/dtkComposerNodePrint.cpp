/* dtkComposerNodeLog.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2008-2011 -Nicolas Niclausse , Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */
#include "dtkComposerMetaType.h"

#include "dtkComposerNodePrint.h"
#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <iostream>

class dtkComposerNodePrintPrivate
{
public:
    dtkComposerTransmitterReceiverVariant receiver_stdout;
    dtkComposerTransmitterReceiverVariant receiver_stderr;

};

dtkComposerNodePrint::dtkComposerNodePrint(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodePrintPrivate)
{
    this->appendReceiver(&(d->receiver_stdout));
    this->appendReceiver(&(d->receiver_stderr));
}

dtkComposerNodePrint::~dtkComposerNodePrint(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodePrint::run(void)
{
    foreach (QVariant v, d->receiver_stdout.allData()) {
        std::cout << qPrintable(dtkMetaType::description(v)) << std::endl;
    }

    foreach (QVariant v, d->receiver_stderr.allData()) {
        std::cerr << qPrintable(dtkMetaType::description(v)) <<  std::endl ;
    }
}

