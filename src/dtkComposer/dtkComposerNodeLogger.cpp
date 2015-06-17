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

#include "dtkComposerNodeLogger.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerMetaType.h"

#include <dtkLog/dtkLogger.h>

// ///////////////////////////////////////////////////////////////////
// Log categories
// ///////////////////////////////////////////////////////////////////

//DTK_LOG_CATEGORY(FR_INRIA_DTK_COMPOSER_LOGGER, "fr.inria.dtk.composer.logger")

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

class dtkComposerNodeLoggerPrivate
{
public:
    dtkComposerTransmitterReceiverVariant   receiver;
    dtkComposerTransmitterReceiver<QString> receiver_header;
    dtkComposerTransmitterReceiver<QString> receiver_level;

};

dtkComposerNodeLogger::dtkComposerNodeLogger(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeLoggerPrivate)
{
    this->appendReceiver(&(d->receiver));
    this->appendReceiver(&(d->receiver_header));
    this->appendReceiver(&(d->receiver_level));
}

dtkComposerNodeLogger::~dtkComposerNodeLogger(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeLogger::run(void)
{
    QVariantList list = d->receiver.allData();

    QStringList identifiers;
    QStringList descriptions;
    foreach (QVariant v, list) {
        identifiers << v.typeName();
        descriptions << qPrintable(dtkMetaType::description(v));
    }

    for(int i = 0; i < descriptions.count(); ++i) {

        QString output;

        if (!d->receiver_header.isEmpty())
            output += (d->receiver_header.data()) + " ";

        output += identifiers.at(i) + ": " + descriptions.at(i);

        if (!d->receiver_level.isEmpty()) {
            QString level = d->receiver_level.data();
            if (level == "trace")
                dtkTrace() <<  output;
            else if  (level == "debug")
                dtkDebug() <<  output;
            else if  (level == "info")
                dtkInfo() <<  output;
            else if  (level == "warn")
                dtkWarn() <<  output;
            else if  (level == "error")
                dtkError() <<  output;
            else if  (level == "fatal")
                dtkFatal() <<  output;
            else
                dtkInfo() <<  output;
        } else {
            dtkInfo() <<  output;
        }
    }
}

// 
// dtkComposerNodeLogger.cpp ends here
