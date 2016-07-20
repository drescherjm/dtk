/* dtkComposerNodeControlIf.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sat Feb 25 00:02:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. janv. 13 08:49:53 2015 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 99
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeControlIf.h"

#include "dtkComposerNodeMetaData.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeProxy.h"

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterReceiver.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlIfPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlIfPrivate
{
public:
    dtkComposerNodeMetaData header_md;
    dtkComposerNodeProxy header;

    dtkComposerNodeMetaData footer_md;
    dtkComposerNodeProxy footer;

    dtkComposerNodeMetaData then_block_md;
    dtkComposerNodeComposite then_block;

    dtkComposerNodeMetaData else_block_md;
    dtkComposerNodeComposite else_block;

public:
    dtkComposerTransmitterReceiver<bool> cond;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlIf implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlIf::dtkComposerNodeControlIf(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlIfPrivate)
{
    d->header_md.setTitle("Header");
    d->header_md.setKind("proxy");
    d->header_md.setType("proxy");
    d->header_md.appendInputLabel("cond");

    d->header.removeEmitter(0);
    d->header.setAsHeader(true);
    d->header.setNodeMetaData(&d->header_md);

    d->cond.appendPrevious(d->header.receivers().first());
    d->header.receivers().first()->appendNext(&(d->cond));

    d->footer_md.setTitle("Footer");
    d->footer_md.setKind("proxy");
    d->footer_md.setType("proxy");
    d->footer_md.appendOutputLabel("cond");

    d->footer.removeReceiver(0);
    d->footer.setAsFooter(true);
    d->footer.setNodeMetaData(&d->footer_md);

    d->cond.appendNext(d->footer.emitters().first());
    d->footer.emitters().first()->appendPrevious(&(d->cond));

    d->then_block_md.setTitle("Then");
    d->then_block_md.setKind("composite");
    d->then_block_md.setType("composite");

    d->then_block.setNodeMetaData(&d->then_block_md);

    d->else_block_md.setTitle("Else");
    d->else_block_md.setKind("composite");
    d->else_block_md.setType("composite");

    d->else_block.setNodeMetaData(&d->else_block_md);
}

dtkComposerNodeControlIf::~dtkComposerNodeControlIf(void)
{
    delete d;

    d = NULL;
}

int dtkComposerNodeControlIf::blockCount(void)
{
    return 2;
}

dtkComposerNodeLeaf *dtkComposerNodeControlIf::header(void)
{
    return &(d->header);
}

dtkComposerNodeLeaf *dtkComposerNodeControlIf::footer(void)
{
    return &(d->footer);
}

dtkComposerNodeComposite *dtkComposerNodeControlIf::block(int id)
{
    if (id == 0)
        return &(d->then_block);

    if (id == 1)
        return &(d->else_block);

    return NULL;
}

void dtkComposerNodeControlIf::setInputs(void)
{

}

void dtkComposerNodeControlIf::setConditions(void)
{

}

void dtkComposerNodeControlIf::setOutputs(void)
{
}

void dtkComposerNodeControlIf::setVariables(void)
{

}

int dtkComposerNodeControlIf::selectBranch(void)
{
    if (!d->cond.isEmpty())
        return static_cast<int>(!(d->cond.data()));

    return static_cast<int>(false);
}

void dtkComposerNodeControlIf::begin(void)
{

}

void dtkComposerNodeControlIf::end(void)
{
    bool value = d->cond.data();

    foreach (dtkComposerTransmitter *t, d->then_block.emitters())
        t->setActive(value);

    foreach (dtkComposerTransmitter *t, d->else_block.emitters())
        t->setActive(!value);
}
