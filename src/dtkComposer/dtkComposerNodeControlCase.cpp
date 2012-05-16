/* dtkComposerNodeControlIf.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: mar. mai 15 17:05:32 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mer. mai 16 16:59:07 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 229
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
#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlCasePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlCasePrivate
{
public:
    dtkComposerNodeProxy header;
    dtkComposerNodeProxy footer;

    QList<dtkComposerNodeComposite *> blocks;

    QList<dtkComposerTransmitterVariant *> blocks_input;

public:
    dtkComposerTransmitterVariant cond;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlCase implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlCase::dtkComposerNodeControlCase(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlCasePrivate)
{

    d->header.removeEmitter(0);
    d->header.setInputLabelHint("switch", 0);
    d->header.setAsHeader(true);

    d->cond.appendPrevious(d->header.receivers().first());
    d->header.receivers().first()->appendNext(&(d->cond));

    d->footer.removeReceiver(0);
    d->footer.setOutputLabelHint("switch", 0);
    d->footer.setAsFooter(true);

    d->cond.appendNext(d->footer.emitters().first());
    d->footer.emitters().first()->appendPrevious(&(d->cond));

    dtkComposerNodeComposite *def = new dtkComposerNodeComposite;
    def->setTitleHint("Case#default");
    d->blocks << def;

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
    if(id < d->blocks.count() && id >= 0)
        return d->blocks[id];

    return NULL;
}


void dtkComposerNodeControlCase::addBlock(void)
{
    dtkComposerNodeComposite *c = new dtkComposerNodeComposite;
    QString id = QString::number(d->blocks.count());
    c->setTitleHint("Case#"+id);
    d->blocks << c;

    dtkComposerTransmitterVariant *v = new dtkComposerTransmitterVariant;
    d->blocks_input << v;
    c->appendReceiver(v);
    c->setInputLabelHint("case",0);
}


void dtkComposerNodeControlCase::removeBlock(int id)
{
    if (id = 0) // can't remove default block
        return;

    for (int i=0; i< d->blocks.count(); i++)
        if (id == i) {
            dtkComposerNodeComposite *b = d->blocks.takeAt(id);
            dtkComposerTransmitterVariant *t = d->blocks_input.takeAt(id-1);
            delete t;
            delete b;
        }

    for (int i=0; i< d->blocks.count(); i++)
            d->blocks.at(i)->setTitleHint("Case#"+QString::number(i));
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
    int value = 0;

    for (int i = 1; i < d->blocks.count(); i++)
        foreach(dtkComposerTransmitter *t, d->blocks[i]->emitters()) {
            dtkComposerTransmitterVariant *v =  dynamic_cast<dtkComposerTransmitterVariant *>(d->blocks_input[i-1]);
            if (d->cond.data() ==  v->data() ) {
                t->setActive(true);
                value = i;
            } else
                t->setActive(false);
        }

    foreach(dtkComposerTransmitter *t, d->blocks[0]->emitters())
        if (value == 0)
            t->setActive(true);
        else
            t->setActive(false);

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
