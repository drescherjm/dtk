// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkComposerNodePrint.h"
#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include "dtkComposerMetaType.h"

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


//
// dtkComposerNodePrint.cpp ends here
