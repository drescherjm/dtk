/* dtkComposerNodeControlIf.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: mar. mai 15 17:05:32 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr  5 08:34:03 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 360
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
#include "dtkComposerTransmitterProxyLoop.h"
#include "dtkComposerTransmitterReceiver.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlCasePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlCasePrivate
{
public:
    dtkComposerNodeProxy header;
    dtkComposerNodeProxy footer;

    QList<dtkComposerNodeComposite *> blocks;

    QList<dtkComposerTransmitterProxyLoop *> blocks_input;

public:
    dtkComposerTransmitterReceiverVariant cond;

public:
    int block_id;
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
    if (id < d->blocks.count() && id >= 0)
        return d->blocks.at(id);

    return NULL;
}

void dtkComposerNodeControlCase::addBlock(void)
{
    dtkComposerNodeComposite *c = new dtkComposerNodeComposite;
    QString id = QString::number(d->blocks.count());
    c->setTitleHint("Case#"+id);
    d->blocks << c;

    dtkComposerTransmitterProxyLoop *v = new dtkComposerTransmitterProxyLoop;
    d->blocks_input << v;
    c->appendReceiver(v);
    c->setInputLabelHint("case#"+id,0);
}

void dtkComposerNodeControlCase::addBlock(dtkComposerNodeComposite *c)
{
    d->blocks << c;
    d->blocks_input << dynamic_cast<dtkComposerTransmitterProxyLoop *>(c->receivers().at(0));
}

void dtkComposerNodeControlCase::removeBlock(int id)
{
    if (id == 0) // can't remove default block
        return;

    d->blocks.removeAt(id);
    d->blocks_input.removeAt(id-1);

    for (int i=1; i< d->blocks.count(); ++i)
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
    d->block_id = 0;

    if (d->cond.isEmpty())
        return d->block_id;

    QVariant var = d->cond.variant();

    if (!var.canConvert<QString>())
        return d->block_id;

    QString s_cond = var.toString();
    int count = d->blocks.count() - 1;    
    for (int i = 0; i < count; ++i) {
	if (s_cond == d->blocks_input.at(i)->variant().toString()) {
	    d->block_id = i + 1;
	    break;
	}
    }

    return d->block_id;
}

void dtkComposerNodeControlCase::begin(void)
{

}

void dtkComposerNodeControlCase::end(void)
{
    int count = d->blocks.count();
    bool active;
    for (int i = 0; i < count; ++i) {
        active = (i == d->block_id);
        foreach(dtkComposerTransmitter *t, d->blocks.at(i)->emitters()) {
            t->setActive(active);
        }
    }
}
