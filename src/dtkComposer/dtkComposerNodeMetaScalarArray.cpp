/* dtkComposerNodeMetaScalarArray.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Jul 13 16:06:48 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Oct 17 11:36:54 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeMetaScalarArray.h"

#include <dtkComposer/dtkComposerTransmitterEmitter.h>

#include <dtkContainer/dtkAbstractContainerWrapper.h>
#include <dtkContainer/dtkContainerVector.h>

#include <dtkLog/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaScalarArrayPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaScalarArrayPrivate
{
public:
    dtkComposerTransmitterEmitterVector<dtkContainerVector<qreal> > emitter_arrays;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaScalarArray implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMetaScalarArray::dtkComposerNodeMetaScalarArray(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMetaScalarArrayPrivate)
{
    this->appendEmitter(&d->emitter_arrays);
}

dtkComposerNodeMetaScalarArray::~dtkComposerNodeMetaScalarArray(void)
{
    delete d;
    
    d = NULL;
}

QString dtkComposerNodeMetaScalarArray::outputLabelHint(int port)
{    
    switch(port) {
    case 0:
        return "arrays";
        break;
    default:
        break;
    }

    return "port";
}

void dtkComposerNodeMetaScalarArray::run(void)
{
    dtkContainerVector<dtkContainerVector<qreal> > arrays;
    d->emitter_arrays.setData(&arrays);
}
