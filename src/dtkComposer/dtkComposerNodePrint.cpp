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
    QStringList identifiers;
    QStringList descriptions;
    QString str;

    foreach (QVariant v, d->receiver_stdout.allData()) {
        identifiers << v.typeName();
        QDataStream ds;
        ds << v;
        ds >> str;
        descriptions << str;
        str.clear();
        std::cout << str.toUtf8().constData() <<  std::endl ;
    }

    foreach (QVariant v, d->receiver_stderr.allData()) {
        identifiers << v.typeName();
        QDataStream ds;
        ds << v;
        ds >> str;
        descriptions << str;
        str.clear();
        std::cerr << str.toUtf8().constData() <<  std::endl ;
    }

    // foreach (QString s, d->receiver_stdout.allDataDescription()) {
    //     std::cout << s.toUtf8().constData() <<  std::endl ;
    // }
    // foreach (QString s, d->receiver_stderr.allDataDescription()) {
    //     std::cerr << s.toUtf8().constData() <<  std::endl ;
    // }

}
