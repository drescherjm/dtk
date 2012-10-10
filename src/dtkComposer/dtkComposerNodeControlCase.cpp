/* dtkComposerNodeControlIf.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: mar. mai 15 17:05:32 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Sep 19 15:25:47 2012 (+0200)
 *           By: tkloczko
 *     Update #: 298
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
    c->setInputLabelHint("case#"+id,0);
}

void dtkComposerNodeControlCase::addBlock(dtkComposerNodeComposite *c)
{
    d->blocks << c;
    d->blocks_input << dynamic_cast<dtkComposerTransmitterVariant*>(c->receivers().at(0));
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
    int value = 0;
    bool is_case = false;

    for (int i = 1; i < d->blocks.count(); ++i) {
        dtkComposerTransmitterVariant *v =  d->blocks_input[i-1] ;
        if (value > 0) //already found the good block, no need to check again.
            is_case = false;
        else {

            QString *s_cond = d->cond.data<QString>();
            QString *s_v    = v->data<QString>();

            if (s_cond && s_v) {
                is_case = (*s_cond == *s_v);

            } else {

                dtkAbstractObject *o_cond = d->cond.object();
                dtkAbstractObject *o_v    = v->object();

                if (o_cond && o_v)
                    is_case = (*o_cond == *o_v);
                else
                    is_case = false;
            }
        }

        if (is_case) {

            value = i;
            foreach(dtkComposerTransmitter *t, d->blocks[i]->emitters()) {
                t->setActive(true);
            }

        } else {

            foreach(dtkComposerTransmitter *t, d->blocks[i]->emitters())
                t->setActive(false);
        }
    }

    if (value == 0) {
        foreach(dtkComposerTransmitter *t, d->blocks[0]->emitters())
            t->setActive(true);
    } else {
        foreach(dtkComposerTransmitter *t, d->blocks[0]->emitters())
            t->setActive(false);
    }

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
