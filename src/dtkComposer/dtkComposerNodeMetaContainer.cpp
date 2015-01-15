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

// 
// dtkComposerNodeMetaContainer.cpp ends here
