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

#include "dtkComposerNodeControlWhile.h"

#include "dtkComposerNodeMetaData.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeProxy.h"

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterProxyLoop.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlWhilePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlWhilePrivate
{
public:
    dtkComposerNodeMetaData header_md;
    dtkComposerNodeProxy header;

    dtkComposerNodeMetaData footer_md;
    dtkComposerNodeProxy footer;

    dtkComposerNodeMetaData cond_block_md;
    dtkComposerNodeComposite cond_block;

    dtkComposerNodeMetaData body_block_md;
    dtkComposerNodeComposite body_block;

public:
    dtkComposerTransmitterReceiver<bool> cond;

public:
    bool first_iteration;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlWhile implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlWhile::dtkComposerNodeControlWhile(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlWhilePrivate)
{
    d->header_md.setTitle("Header");
    d->header_md.setKind("proxy");
    d->header_md.setType("proxy");

    d->header.removeReceiver(0);
    d->header.removeEmitter(0);
    d->header.setAsHeader(true);
    d->header.setNodeMetaData(&d->header_md);

    d->footer_md.setTitle("Footer");
    d->footer_md.setKind("proxy");
    d->footer_md.setType("proxy");

    d->footer.removeReceiver(0);
    d->footer.removeEmitter(0);
    d->footer.setAsFooter(true);
    d->footer.setNodeMetaData(&d->footer_md);

    d->cond_block_md.setTitle("Conditional");
    d->cond_block_md.setKind("composite");
    d->cond_block_md.setType("composite");
    d->cond_block_md.appendOutputLabel("cond");

    d->cond_block.appendEmitter(&(d->cond));
    d->cond_block.setNodeMetaData(&d->cond_block_md);

    d->body_block_md.setTitle("Body");
    d->body_block_md.setKind("composite");
    d->body_block_md.setType("composite");

    d->body_block.setNodeMetaData(&d->body_block_md);
}

dtkComposerNodeControlWhile::~dtkComposerNodeControlWhile(void)
{
    delete d;

    d = NULL;
}

int dtkComposerNodeControlWhile::blockCount(void)
{
    return 2;
}

dtkComposerNodeLeaf *dtkComposerNodeControlWhile::header(void)
{
    return &(d->header);
}

dtkComposerNodeLeaf *dtkComposerNodeControlWhile::footer(void)
{
    return &(d->footer);
}

dtkComposerNodeComposite *dtkComposerNodeControlWhile::block(int id)
{
    if (id == 0)
        return &(d->cond_block);

    if (id == 1)
        return &(d->body_block);

    return NULL;
}

void dtkComposerNodeControlWhile::setInputs(void)
{
    for (dtkComposerTransmitterProxyLoop *t : this->inputTwins()) {
        t->disableLoopMode();
    }

    d->first_iteration = true;
}

void dtkComposerNodeControlWhile::setConditions(void)
{
}

void dtkComposerNodeControlWhile::setOutputs(void)
{
    if (d->first_iteration) {
        for (dtkComposerTransmitterProxyLoop *t : this->outputTwins()) {
            t->twin()->enableLoopMode();
        }

        d->first_iteration = false;
    }

    for (dtkComposerTransmitterProxyLoop *t : this->outputTwins()) {
        t->twin()->setVariant(t->variant());
    }
}

void dtkComposerNodeControlWhile::setVariables(void)
{
}

int dtkComposerNodeControlWhile::selectBranch(void)
{
    if (!d->cond.isEmpty())
        return static_cast<int>(!(d->cond.data()));

    return static_cast<int>(true);
}

void dtkComposerNodeControlWhile::begin(void)
{
}

void dtkComposerNodeControlWhile::end(void)
{
}

//
// dtkComposerNodeControlWhile.cpp ends here
