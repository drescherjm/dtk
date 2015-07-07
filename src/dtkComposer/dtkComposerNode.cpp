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

#include "dtkComposerNode.h"
#include "dtkComposerTransmitter.h"
#include "dtkComposerNodeMetaData.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePrivate
{
public:
    dtkComposerNodeMetaData *meta_data;

public:
    QList<dtkComposerTransmitter *> emitters;
    QList<dtkComposerTransmitter *> receivers;

public:
    QString title_hint;

public:
    QHash<int, QString>  input_label_hint;
    QHash<int, QString> output_label_hint;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNode implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNode::dtkComposerNode(void) : d(new dtkComposerNodePrivate)
{
    d->title_hint = "Node";
    d->meta_data = 0;
}

dtkComposerNode::~dtkComposerNode(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNode::setNodeMetaData(dtkComposerNodeMetaData *meta_data)
{
    d->meta_data = meta_data;
}

dtkComposerNodeMetaData *dtkComposerNode::nodeMetaData(void) const
{
    return d->meta_data;
}

void dtkComposerNode::appendEmitter(dtkComposerTransmitter *emitter)
{
    if (!d->emitters.contains(emitter)) {
        d->emitters << emitter;
        emitter->setParentNode(this);
    }
}

void dtkComposerNode::removeEmitter(dtkComposerTransmitter *emitter)
{
    d->emitters.removeOne(emitter);
}

dtkComposerTransmitter *dtkComposerNode::removeEmitter(int index)
{
    return d->emitters.takeAt(index);
}

void dtkComposerNode::appendReceiver(dtkComposerTransmitter *receiver)
{
    if(!d->receivers.contains(receiver)) {
        d->receivers << receiver;
        receiver->setParentNode(this);
    }
}

void dtkComposerNode::removeReceiver(dtkComposerTransmitter *receiver)
{
    d->receivers.removeOne(receiver);
}

dtkComposerTransmitter *dtkComposerNode::removeReceiver(int index)
{
    return d->receivers.takeAt(index);
}

QList<dtkComposerTransmitter *> dtkComposerNode::emitters(void)
{
    return d->emitters;
}

QList<dtkComposerTransmitter *> dtkComposerNode::receivers(void)
{
    return d->receivers;
}

QString dtkComposerNode::type(void)
{
    if (d->meta_data)
        return d->meta_data->type();

    return QString();
}

QString dtkComposerNode::titleHint(void)
{
    if (d->meta_data)
        return d->meta_data->title();

    return d->title_hint;
}

QString dtkComposerNode::inputLabelHint(int port)
{
    if (d->meta_data)
        return d->meta_data->inputLabels().value(port, "port");

    return "port";
}

QString dtkComposerNode::outputLabelHint(int port)
{
    if (d->meta_data)
        return d->meta_data->outputLabels().value(port, "port");

    return "port";
}

dtkComposerViewWidget *dtkComposerNode::widget(void)
{
    return NULL;
}

QWidget *dtkComposerNode::editor(void)
{
    return NULL;
}

void dtkComposerNode::setTitleHint(const QString& hint)
{
    d->title_hint = hint;
}

void dtkComposerNode::setInputLabelHint(const QString& hint, int port)
{
    d->input_label_hint[port] = hint;
}

void dtkComposerNode::setOutputLabelHint(const QString& hint, int port)
{
    d->output_label_hint[port] = hint;
}

//
// dtkComposerNode.cpp ends here
