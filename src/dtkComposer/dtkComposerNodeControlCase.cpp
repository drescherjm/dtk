/* dtkComposerNodeControlIf.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: mar. mai 15 17:05:32 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. mai 15 17:33:13 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 72
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeControlCase.h"

#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeProxy.h"

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlCasePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlCasePrivate
{
public:
    dtkComposerNodeProxy header;
    dtkComposerNodeProxy footer;

    QList<dtkComposerNodeComposite *> blocks;

public:
    dtkComposerTransmitterVariant cond;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlCase implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlCase::dtkComposerNodeControlCase(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlCasePrivate)
{
    QList<QVariant::Type> variants;
    variants << QVariant::Bool;
    d->cond.setTypes(variants);

    d->header.removeEmitter(0);
    d->header.setInputLabelHint("cond", 0);
    d->header.setAsHeader(true);

    d->cond.appendPrevious(d->header.receivers().first());
    d->header.receivers().first()->appendNext(&(d->cond));

    d->footer.removeReceiver(0);
    d->footer.setOutputLabelHint("cond", 0);
    d->footer.setAsFooter(true);

    d->cond.appendNext(d->footer.emitters().first());
    d->footer.emitters().first()->appendPrevious(&(d->cond));

    dtkComposerNodeComposite *case1 = new dtkComposerNodeComposite;
    case1->setTitleHint("Case#1");
    d->blocks << case1;
    dtkComposerNodeComposite *case2 = new dtkComposerNodeComposite;
    case2->setTitleHint("Case#2");
    d->blocks << case2;

}

dtkComposerNodeControlCase::~dtkComposerNodeControlCase(void)
{

    //FIXME: delete blocks
    delete d;

    d = NULL;
}

int dtkComposerNodeControlCase::blockCount(void)
{
    return d->blocks.count();
}

dtkComposerNodeLeaf *dtkComposerNodeControlCase::header(void)
{
    return &(d->header);
}

dtkComposerNodeLeaf *dtkComposerNodeControlCase::footer(void)
{
    return &(d->footer);
}

dtkComposerNodeComposite *dtkComposerNodeControlCase::block(int id)
{
    if(id < d->blocks.count() && id >= 0) {
        qDebug() << "return id " << id << d->blocks.count();
        return d->blocks[id];
    }
    return NULL;
}

void dtkComposerNodeControlCase::setInputs(void)
{

}

void dtkComposerNodeControlCase::setConditions(void)
{

}

void dtkComposerNodeControlCase::setOutputs(void)
{

}

void dtkComposerNodeControlCase::setVariables(void)
{

}

int dtkComposerNodeControlCase::selectBranch(void)
{
    int value = d->cond.data().toInt();

    for (int i=0; i++ ;i < d->blocks.count())
        foreach(dtkComposerTransmitter *t, d->blocks[i]->emitters())
            if (i == value)
                t->setActive(value);
            else
                t->setActive(!value);

    return value;
}

void dtkComposerNodeControlCase::begin(void)
{

}

void dtkComposerNodeControlCase::end(void)
{

}

QString dtkComposerNodeControlCase::type(void)
{
    return "case";
}

QString dtkComposerNodeControlCase::titleHint(void)
{
    return "Case";
}
