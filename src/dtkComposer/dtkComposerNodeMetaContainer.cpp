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
            int type = d->receiver_value.data().type();
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
                var_container = dtkMetaType::variantFromValue(new dtkArray<QVariant>(size, d->receiver_value.data()));
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
    dtkComposerTransmitter::TypeList type_list;
    type_list << qMetaTypeId<dtkMetaContainerSequentialHandler *>();
    d->receiver_container.setTypeList(type_list);

    this->appendReceiver(&d->receiver_container);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_container);
}

dtkComposerNodeMetaContainerAppend::~dtkComposerNodeMetaContainerAppend(void)
{

}

void dtkComposerNodeMetaContainerAppend::run(void)
{
    if(!d->receiver_container.isEmpty()) {
        QVariant var_container = d->receiver_container.data();

        if(!d->receiver_value.isEmpty()) {
            dtkMetaContainerSequential m_c = var_container.value<dtkMetaContainerSequential>();
            m_c.append(d->receiver_value.data());

        } else {
            dtkWarn() << "No input value to append to the container. The container is not modified.";
        }

        d->emitter_container.setData(var_container);

    } else {
        dtkWarn() << "No input container for append operation. Nothing is emitted.";
        d->emitter_container.clearData();
    }
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
    dtkComposerTransmitter::TypeList type_list;
    type_list << qMetaTypeId<dtkMetaContainerSequentialHandler *>();
    d->receiver_container.setTypeList(type_list);

    this->appendReceiver(&d->receiver_container);

    this->appendEmitter(&d->emitter_size);
}

dtkComposerNodeMetaContainerSize::~dtkComposerNodeMetaContainerSize(void)
{

}

void dtkComposerNodeMetaContainerSize::run(void)
{
    if (!d->receiver_container.isEmpty()) {
        QVariant var_container = d->receiver_container.data();
        dtkMetaContainerSequential m_c = var_container.value<dtkMetaContainerSequential>();
        d->emitter_size.setData(m_c.size());

    } else {
        dtkWarn() << "No input container for size operation. Nothing is emitted.";
        d->emitter_size.clearData();
    }
}

////////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerAtPrivate interface
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
    dtkComposerTransmitter::TypeList type_list;
    type_list << qMetaTypeId<dtkMetaContainerSequentialHandler *>();
    d->receiver_container.setTypeList(type_list);

    this->appendReceiver(&d->receiver_container);
    this->appendReceiver(&d->receiver_index);

    this->appendEmitter(&d->emitter_value);
}

dtkComposerNodeMetaContainerAt::~dtkComposerNodeMetaContainerAt(void)
{

}

void dtkComposerNodeMetaContainerAt::run(void)
{
    if(!d->receiver_container.isEmpty()) {
        QVariant var_container = d->receiver_container.data();
        dtkMetaContainerSequential m_c = var_container.value<dtkMetaContainerSequential>();
        if(!d->receiver_index.isEmpty()) {
            d->emitter_value.setData(m_c.at(d->receiver_index.data()));

        } else {
            dtkWarn() << "No input index for the at operation. First item of the container is returned.";
            d->emitter_value.setData(m_c.at(0));
        }

    } else {
        dtkWarn() << "No input container for at operation. Nothing is emitted.";
        d->emitter_value.clearData();
    }
}


////////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerSetAtPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaContainerSetAtPrivate
{
public:
    dtkComposerTransmitterReceiverVariant receiver_container;
    dtkComposerTransmitterReceiver<qlonglong> receiver_index;
    dtkComposerTransmitterReceiverVariant receiver_value;

public:
    dtkComposerTransmitterEmitterVariant emitter_container;
};



// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerSetAt implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMetaContainerSetAt::dtkComposerNodeMetaContainerSetAt(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMetaContainerSetAtPrivate)
{
    dtkComposerTransmitter::TypeList type_list;
    type_list << qMetaTypeId<dtkMetaContainerSequentialHandler *>();
    d->receiver_container.setTypeList(type_list);

    this->appendReceiver(&d->receiver_container);
    this->appendReceiver(&d->receiver_index);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_container);
}

dtkComposerNodeMetaContainerSetAt::~dtkComposerNodeMetaContainerSetAt(void)
{

}

void dtkComposerNodeMetaContainerSetAt::run(void)
{
    if(!d->receiver_container.isEmpty() && !d->receiver_value.isEmpty() && !d->receiver_index.isEmpty()) {
        QVariant var_container = d->receiver_container.data();
        dtkMetaContainerSequential m_c = var_container.value<dtkMetaContainerSequential>();

        m_c.setAt(d->receiver_index.data(), d->receiver_value.data());
        d->emitter_container.setData(var_container);


    } else {
        dtkWarn() << "All input ports must be connected for set at operation. Nothing is emitted.";
        d->emitter_container.clearData();
    }
}



////////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerRemoveAtPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaContainerRemoveAtPrivate
{
public:
    dtkComposerTransmitterReceiverVariant receiver_container;
    dtkComposerTransmitterReceiver<qlonglong> receiver_index;

public:
    dtkComposerTransmitterEmitterVariant emitter_container;
};



// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerRemoveAt implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMetaContainerRemoveAt::dtkComposerNodeMetaContainerRemoveAt(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMetaContainerRemoveAtPrivate)
{
    dtkComposerTransmitter::TypeList type_list;
    type_list << qMetaTypeId<dtkMetaContainerSequentialHandler *>();
    d->receiver_container.setTypeList(type_list);

    this->appendReceiver(&d->receiver_container);
    this->appendReceiver(&d->receiver_index);

    this->appendEmitter(&d->emitter_container);
}

dtkComposerNodeMetaContainerRemoveAt::~dtkComposerNodeMetaContainerRemoveAt(void)
{

}

void dtkComposerNodeMetaContainerRemoveAt::run(void)
{
    if(!d->receiver_container.isEmpty() && !d->receiver_index.isEmpty()) {
        QVariant var_container = d->receiver_container.data();
        dtkMetaContainerSequential m_c = var_container.value<dtkMetaContainerSequential>();

        m_c.removeAt(d->receiver_index.data());
        d->emitter_container.setData(var_container);

    } else {
        dtkWarn() << "All input ports must be connected for remove at operation. Nothing is emitted.";
        d->emitter_container.clearData();
    }
}



////////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerTakeAtPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaContainerTakeAtPrivate
{
public:
    dtkComposerTransmitterReceiverVariant receiver_container;
    dtkComposerTransmitterReceiver<qlonglong> receiver_index;

public:
    dtkComposerTransmitterEmitterVariant emitter_container;
    dtkComposerTransmitterEmitterVariant emitter_value;
};



// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerTakeAt implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMetaContainerTakeAt::dtkComposerNodeMetaContainerTakeAt(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMetaContainerTakeAtPrivate)
{
    dtkComposerTransmitter::TypeList type_list;
    type_list << qMetaTypeId<dtkMetaContainerSequentialHandler *>();
    d->receiver_container.setTypeList(type_list);

    this->appendReceiver(&d->receiver_container);
    this->appendReceiver(&d->receiver_index);

    this->appendEmitter(&d->emitter_container);
    this->appendEmitter(&d->emitter_value);
}

dtkComposerNodeMetaContainerTakeAt::~dtkComposerNodeMetaContainerTakeAt(void)
{

}

void dtkComposerNodeMetaContainerTakeAt::run(void)
{
    if(!d->receiver_container.isEmpty() && !d->receiver_index.isEmpty()) {
        QVariant var_container = d->receiver_container.data();
        dtkMetaContainerSequential m_c = var_container.value<dtkMetaContainerSequential>();

        QVariant v = m_c.at(d->receiver_index.data());
        m_c.removeAt(d->receiver_index.data());
        d->emitter_container.setData(var_container);
        d->emitter_value.setData(v);

    } else {
        dtkWarn() << "All input ports must be connected for take at operation. Nothing is emitted.";
        d->emitter_container.clearData();
        d->emitter_value.clearData();
    }
}



////////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerInsertPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaContainerInsertPrivate
{
public:
    dtkComposerTransmitterReceiverVariant receiver_container;
    dtkComposerTransmitterReceiver<qlonglong> receiver_index;
    dtkComposerTransmitterReceiverVariant receiver_value;

public:
    dtkComposerTransmitterEmitterVariant emitter_container;
};



// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerInsert implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMetaContainerInsert::dtkComposerNodeMetaContainerInsert(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMetaContainerInsertPrivate)
{
    dtkComposerTransmitter::TypeList type_list;
    type_list << qMetaTypeId<dtkMetaContainerSequentialHandler *>();
    d->receiver_container.setTypeList(type_list);

    this->appendReceiver(&d->receiver_container);
    this->appendReceiver(&d->receiver_index);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_container);
}

dtkComposerNodeMetaContainerInsert::~dtkComposerNodeMetaContainerInsert(void)
{

}

void dtkComposerNodeMetaContainerInsert::run(void)
{
    if(!d->receiver_container.isEmpty() && !d->receiver_index.isEmpty() && !d->receiver_value.isEmpty()) {
        QVariant var_container = d->receiver_container.data();
        dtkMetaContainerSequential m_c = var_container.value<dtkMetaContainerSequential>();

        m_c.insert(d->receiver_index.data(),d->receiver_value.data());
        d->emitter_container.setData(var_container);

    } else {
        dtkWarn() << "All input ports must be connected for insert operation. Nothing is emitted.";
        d->emitter_container.clearData();
    }
}


////////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerResizePrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaContainerResizePrivate
{
public:
    dtkComposerTransmitterReceiverVariant receiver_container;
    dtkComposerTransmitterReceiver<qlonglong> receiver_size;

public:
    dtkComposerTransmitterEmitterVariant emitter_container;
};



// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerResize implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMetaContainerResize::dtkComposerNodeMetaContainerResize(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMetaContainerResizePrivate)
{
    dtkComposerTransmitter::TypeList type_list;
    type_list << qMetaTypeId<dtkMetaContainerSequentialHandler *>();
    d->receiver_container.setTypeList(type_list);

    this->appendReceiver(&d->receiver_container);
    this->appendReceiver(&d->receiver_size);

    this->appendEmitter(&d->emitter_container);
}

dtkComposerNodeMetaContainerResize::~dtkComposerNodeMetaContainerResize(void)
{

}

void dtkComposerNodeMetaContainerResize::run(void)
{
    if(!d->receiver_container.isEmpty() && !d->receiver_size.isEmpty()) {
        QVariant var_container = d->receiver_container.data();
        dtkMetaContainerSequential m_c = var_container.value<dtkMetaContainerSequential>();

        m_c.resize(d->receiver_size.data());
        d->emitter_container.setData(var_container);

    } else {
        dtkWarn() << "All input ports must be connected for resize operation. Nothing is emitted.";
        d->emitter_container.clearData();
    }
}


////////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerPrependPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaContainerPrependPrivate
{
public:
    dtkComposerTransmitterReceiverVariant receiver_container;
    dtkComposerTransmitterReceiverVariant receiver_value;

public:
    dtkComposerTransmitterEmitterVariant emitter_container;
};



// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaContainerPrepend implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeMetaContainerPrepend::dtkComposerNodeMetaContainerPrepend(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeMetaContainerPrependPrivate)
{
    dtkComposerTransmitter::TypeList type_list;
    type_list << qMetaTypeId<dtkMetaContainerSequentialHandler *>();
    d->receiver_container.setTypeList(type_list);

    this->appendReceiver(&d->receiver_container);
    this->appendReceiver(&d->receiver_value);

    this->appendEmitter(&d->emitter_container);
}

dtkComposerNodeMetaContainerPrepend::~dtkComposerNodeMetaContainerPrepend(void)
{

}

void dtkComposerNodeMetaContainerPrepend::run(void)
{
    if(!d->receiver_container.isEmpty()  && !d->receiver_value.isEmpty()) {
        QVariant var_container = d->receiver_container.data();
        dtkMetaContainerSequential m_c = var_container.value<dtkMetaContainerSequential>();

        m_c.prepend(d->receiver_value.data());
        d->emitter_container.setData(var_container);

    } else {
        dtkWarn() << "All input ports must be connected for prepend operation. Nothing is emitted.";
        d->emitter_container.clearData();
    }
}

// 
// dtkComposerNodeMetaContainer.cpp ends here
