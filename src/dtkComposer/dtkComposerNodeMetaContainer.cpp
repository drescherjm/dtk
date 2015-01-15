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

#include "dtkComposerNodeMetaContainer.h"

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMeta/dtkMetaContainerSequential.h>

#include <dtkCore/dtkArray>
#include <dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaContainerPrivate
{
public:
    dtkComposerTransmitterReceiver<qlonglong> receiver_size;
    dtkComposerTransmitterReceiverVariant receiver_value;

public:
    dtkComposerTransmitterEmitterVariant emitter_container;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainer implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMetaContainer::dtkComposerNodeMetaContainer(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMetaContainerPrivate)
{
    this->appendReceiver(&d->receiver_size);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_container);
}

dtkComposerNodeMetaContainer::~dtkComposerNodeMetaContainer(void)
{

}

void dtkComposerNodeMetaContainer::run(void)
{
    QVariant var_container;

    if (!d->receiver_size.isEmpty()) {
        qlonglong size = d->receiver_size.data();
        if (!d->receiver_value.isEmpty()) {
            int type = d->receiver_value.variant().type();
            switch(type) {
            case QMetaType::Int:
                var_container = dtkMetaType::variantFromValue(new dtkArray<int>(size, d->receiver_value.data<int>()));
                break;
            case QMetaType::Short:
                var_container = dtkMetaType::variantFromValue(new dtkArray<short>(size, d->receiver_value.data<short>()));
                break;
            case QMetaType::Long:
            case QMetaType::LongLong:
                var_container = dtkMetaType::variantFromValue(new dtkArray<qlonglong>(size, d->receiver_value.data<qlonglong>()));
                break;
            case QMetaType::UInt:
                var_container = dtkMetaType::variantFromValue(new dtkArray<uint>(size, d->receiver_value.data<uint>()));
                break;
            case QMetaType::UShort:
                var_container = dtkMetaType::variantFromValue(new dtkArray<ushort>(size, d->receiver_value.data<ushort>()));
                break;
            case QMetaType::ULong:
            case QMetaType::ULongLong:
                var_container = dtkMetaType::variantFromValue(new dtkArray<qulonglong>(size, d->receiver_value.data<qulonglong>()));
                break;
            case QMetaType::Float:
            case QMetaType::Double:
                var_container = dtkMetaType::variantFromValue(new dtkArray<double>(size, d->receiver_value.data<double>()));
                break;
            default:
                var_container = dtkMetaType::variantFromValue(new dtkArray<QVariant>(size, d->receiver_value.variant()));
                break;
            }
        } else {
            var_container = dtkMetaType::variantFromValue(new dtkArray<QVariant>(size));
        }
    } else {
        var_container = dtkMetaType::variantFromValue(new dtkArray<QVariant>(0));
    }
    
    d->emitter_container.setData(var_container);

    qDebug() << d->emitter_container.variant();
}


////////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerAppendPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaContainerAppendPrivate
{
public:
    dtkComposerTransmitterReceiverVariant receiver_container;
    dtkComposerTransmitterReceiverVariant receiver_value;

public:
    dtkComposerTransmitterEmitterVariant emitter_container;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainer implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMetaContainerAppend::dtkComposerNodeMetaContainerAppend(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMetaContainerAppendPrivate)
{
    this->appendReceiver(&d->receiver_container);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_container);
}

dtkComposerNodeMetaContainerAppend::~dtkComposerNodeMetaContainerAppend(void)
{

}

void dtkComposerNodeMetaContainerAppend::run(void)
{
    QVariant var_container;

    if (!d->receiver_container.isEmpty() && !d->receiver_value.isEmpty()) {
        var_container = d->receiver_container.variant();
        if (dtkMetaType::canConvert<dtkMetaContainerSequential>(var_container.userType())) {
            dtkMetaContainerSequential m_c = var_container.value<dtkMetaContainerSequential>();
            m_c.append(d->receiver_value.variant());
        } else {
            dtkError()<< "input container is not a dtkMetaContainerSequential";
        }

    }
    d->emitter_container.setData(var_container);
}


////////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerSizePrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaContainerSizePrivate
{
public:
    dtkComposerTransmitterReceiverVariant receiver_container;

public:
    dtkComposerTransmitterEmitter<qlonglong> emitter_size;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerSize implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMetaContainerSize::dtkComposerNodeMetaContainerSize(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMetaContainerSizePrivate)
{
    this->appendReceiver(&d->receiver_container);

    this->appendEmitter(&d->emitter_size);
}

dtkComposerNodeMetaContainerSize::~dtkComposerNodeMetaContainerSize(void)
{

}

void dtkComposerNodeMetaContainerSize::run(void)
{
    QVariant var_container;
    qlonglong size ;

    if (!d->receiver_container.isEmpty()) {
        var_container = d->receiver_container.variant();
        if (dtkMetaType::canConvert<dtkMetaContainerSequential>(var_container.userType())) {
            dtkMetaContainerSequential m_c = var_container.value<dtkMetaContainerSequential>();
            size = m_c.size();
        } else {
            dtkError()<< "input container is not a dtkMetaContainerSequential";
        }

    }
    d->emitter_size.setData(size);
}


////////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerSizePrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaContainerAtPrivate
{
public:
    dtkComposerTransmitterReceiverVariant receiver_container;
    dtkComposerTransmitterReceiver<qlonglong> receiver_index;

public:
    dtkComposerTransmitterEmitterVariant emitter_value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerAt implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMetaContainerAt::dtkComposerNodeMetaContainerAt(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMetaContainerAtPrivate)
{
    this->appendReceiver(&d->receiver_container);
    this->appendReceiver(&d->receiver_index);

    this->appendEmitter(&d->emitter_value);
}

dtkComposerNodeMetaContainerAt::~dtkComposerNodeMetaContainerAt(void)
{

}

void dtkComposerNodeMetaContainerAt::run(void)
{
    QVariant var_container;
    QVariant v;

    if (!d->receiver_container.isEmpty() && !d->receiver_index.isEmpty()) {
        var_container = d->receiver_container.variant();
        if (dtkMetaType::canConvert<dtkMetaContainerSequential>(var_container.userType())) {
            dtkMetaContainerSequential m_c = var_container.value<dtkMetaContainerSequential>();
            v = m_c.at(d->receiver_index.data());
        } else {
            dtkError()<< "input container is not a dtkMetaContainerSequential";
        }

        d->emitter_value.setData(v);
    }
}


// 
// dtkComposerNodeMetaContainer.cpp ends here
