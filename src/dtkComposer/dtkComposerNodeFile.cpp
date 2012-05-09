/* dtkComposerNodeFile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 11:45:03 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed May  9 09:55:18 2012 (+0200)
 *           By: tkloczko
 *     Update #: 53
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeFile.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFilePrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeFilePrivate
{
public:
    dtkComposerTransmitterReceiver<QString> receiver;

public:    
    dtkComposerTransmitterEmitter<QString> emitter_name;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFile implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeFile::dtkComposerNodeFile(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeFilePrivate)
{
    this->appendReceiver(&(d->receiver));

    this->appendEmitter(&(d->emitter_name));
}

dtkComposerNodeFile::~dtkComposerNodeFile(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposerNodeFile::run(void)
{
    qDebug() << "Not yet implemented";
}

QString dtkComposerNodeFile::type(void)
{
    return "file";
}

QString dtkComposerNodeFile::titleHint(void)
{
    return "File";
}

QString dtkComposerNodeFile::inputLabelHint(int port)
{
    if(port == 0)
        return "name";

    return dtkComposerNode::inputLabelHint(port);
}

QString dtkComposerNodeFile::outputLabelHint(int port)
{
    if(port == 0)
        return "name";

    if(port == 1)
        return "file";

    return dtkComposerNode::outputLabelHint(port);
}
