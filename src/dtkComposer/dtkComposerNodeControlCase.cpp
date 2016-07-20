/* dtkComposerNodeControlIf.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: mar. mai 15 17:05:32 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. janv. 13 08:34:13 2015 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 432
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeControlCase.h"

#include "dtkComposerNodeMetaData.h"
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
    dtkComposerNodeMetaData header_md;
    dtkComposerNodeProxy header;

    dtkComposerNodeMetaData footer_md;
    dtkComposerNodeProxy footer;

    QList<dtkComposerNodeMetaData *> blocks_md;
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
    d->header_md.setTitle("Header");
    d->header_md.setKind("proxy");
    d->header_md.setType("proxy");
    d->header_md.appendInputLabel("swicth");

    d->header.removeEmitter(0);
    d->header.setAsHeader(true);
    d->header.setNodeMetaData(&d->header_md);

    d->cond.appendPrevious(d->header.receivers().first());
    d->header.receivers().first()->appendNext(&(d->cond));

    d->footer_md.setTitle("Footer");
    d->footer_md.setKind("proxy");
    d->footer_md.setType("proxy");
    d->footer_md.appendOutputLabel("switch");

    d->footer.removeReceiver(0);
    d->footer.setAsFooter(true);
    d->footer.setNodeMetaData(&d->footer_md);

    d->cond.appendNext(d->footer.emitters().first());
    d->footer.emitters().first()->appendPrevious(&(d->cond));

    dtkComposerNodeMetaData *def_md = new dtkComposerNodeMetaData;
    def_md->setTitle("Case#default");
    def_md->setKind("composite");
    def_md->setType("composite");
    d->blocks_md << def_md;

    dtkComposerNodeComposite *def = new dtkComposerNodeComposite;
    def->setNodeMetaData(def_md);
    d->blocks << def;
}

dtkComposerNodeControlCase::~dtkComposerNodeControlCase(void)
{
    qDebug() << Q_FUNC_INFO << d->blocks;

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
    dtkComposerNodeMetaData *c_md = new dtkComposerNodeMetaData;
    QString id = QString::number(d->blocks.count());
    c_md->setTitle("case#" + id);
    c_md->setKind("composite");
    c_md->setType("composite");
    c_md->appendInputLabel("case#" + id);
    d->blocks_md << c_md;

    dtkComposerNodeComposite *c = new dtkComposerNodeComposite;
    c->setNodeMetaData(c_md);
    d->blocks << c;

    dtkComposerTransmitterProxyLoop *v = new dtkComposerTransmitterProxyLoop;
    d->blocks_input << v;
    c->appendReceiver(v);
}

void dtkComposerNodeControlCase::addBlock(dtkComposerNodeComposite *c)
{
    d->blocks_md << c->nodeMetaData();
    d->blocks << c;
    d->blocks_input << dynamic_cast<dtkComposerTransmitterProxyLoop *>(c->receivers().at(0));
}

void dtkComposerNodeControlCase::removeBlock(int id)
{
    if (id == 0) // can't remove default block
        return;

    delete d->blocks_md.takeAt(id);

    d->blocks.removeAt(id);
    delete d->blocks_input.takeAt(id - 1);

    for (int i = 1; i < d->blocks.count(); ++i) {
        d->blocks_md.at(i)->setTitle("Case#" + QString::number(i));
        d->blocks_md.at(i)->setInputLabel(0, "case#" + QString::number(i));
        qDebug() << Q_FUNC_INFO << i << d->blocks_md.at(i)->title() << d->blocks_md.at(i)->inputLabels();
    }


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

        foreach (dtkComposerTransmitter *t, d->blocks.at(i)->emitters()) {
            t->setActive(active);
        }
    }
}
