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

#include "dtkComposerNodeControlMap.h"

#include "dtkComposerNodeMetaData.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeProxy.h"

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterProxy.h"
#include "dtkComposerTransmitterProxyLoop.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlMapPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlMapPrivate
{
public:
    dtkComposerNodeMetaData header_md;
    dtkComposerNodeProxy header;

    dtkComposerNodeMetaData footer_md;
    dtkComposerNodeProxy footer;

    dtkComposerNodeMetaData body_block_md;
    dtkComposerNodeComposite body_block;

public:
    dtkComposerTransmitterReceiverVariant header_rcv;
    dtkComposerTransmitterEmitterVariant footer_emit;

    dtkComposerTransmitterEmitterVariant     block_container;
    dtkComposerTransmitterEmitter<qlonglong> block_size;
    dtkComposerTransmitterEmitter<qlonglong> block_index;
    dtkComposerTransmitterEmitterVariant     block_item;
    dtkComposerTransmitterEmitterVariant     block_newitem;

public:
    qlonglong counter;
    qlonglong size;

    // dtkAbstractContainerWrapper *container;
    // dtkAbstractContainerWrapper *out_container;
    dtkMetaContainerSequential *container;
    dtkMetaContainerSequential *out_container;

public:
    bool first_iteration;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlMap implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlMap::dtkComposerNodeControlMap(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlMapPrivate)
{
    dtkComposerTransmitter::TypeList type_list;
    type_list << qMetaTypeId<dtkMetaContainerSequentialHandler *>();
    d->header_rcv.setTypeList(type_list);

    d->header_md.setTitle("Header");
    d->header_md.setKind("proxy");
    d->header_md.setType("proxy");
    d->header_md.appendInputLabel("container");

    d->header.removeEmitter(0);
    d->header.removeReceiver(0);
    d->header.appendReceiver(&(d->header_rcv));
    d->header.setAsHeader(true);
    d->header.setNodeMetaData(&d->header_md);

    d->footer_md.setTitle("Footer");
    d->footer_md.setKind("proxy");
    d->footer_md.setType("proxy");
    d->footer_md.appendOutputLabel("container");

    d->footer.removeReceiver(0);
    d->footer.removeEmitter(0);
    d->footer.appendEmitter(&(d->footer_emit));
    d->footer.setAsFooter(true);
    d->footer.setNodeMetaData(&d->footer_md);

    d->body_block_md.setTitle("Body");
    d->body_block_md.setKind("composite");
    d->body_block_md.setType("composite");
    d->body_block_md.appendInputLabel("container");
    d->body_block_md.appendInputLabel("size");
    d->body_block_md.appendInputLabel("index");
    d->body_block_md.appendInputLabel("item");
    d->body_block_md.appendOutputLabel("newItem");

    d->body_block.appendReceiver(&(d->block_container));
    d->body_block.appendReceiver(&(d->block_size));
    d->body_block.appendReceiver(&(d->block_index));
    d->body_block.appendReceiver(&(d->block_item));
    d->body_block.appendEmitter(&(d->block_newitem));
    d->body_block.setNodeMetaData(&d->body_block_md);

    d->block_container.appendPrevious(&d->header_rcv);
    d->header_rcv.appendNext(&d->block_container);

    d->footer.emitters().first()->appendNext(&(d->footer_emit));

    d->counter = 0;
    d->size = -1;
}

dtkComposerNodeControlMap::~dtkComposerNodeControlMap(void)
{
    delete d;

    d = NULL;
}

int dtkComposerNodeControlMap::blockCount(void)
{
    return 1;
}

dtkComposerNodeLeaf *dtkComposerNodeControlMap::header(void)
{
    return &(d->header);
}

dtkComposerNodeLeaf *dtkComposerNodeControlMap::footer(void)
{
    return &(d->footer);
}

dtkComposerNodeComposite *dtkComposerNodeControlMap::block(int id)
{
    if(id == 0)
        return &(d->body_block);

    return NULL;
}

void dtkComposerNodeControlMap::setInputs(void)
{
    for(dtkComposerTransmitterProxyLoop *t : this->inputTwins()) {
        t->disableLoopMode();
    }
    d->first_iteration = true;
}


void dtkComposerNodeControlMap::setOutputs(void)
{
    if (d->first_iteration) {
	for(dtkComposerTransmitterProxyLoop *t : this->outputTwins()) {
	    t->twin()->enableLoopMode();
	}
	d->first_iteration = false;
    }
    for(dtkComposerTransmitterProxyLoop *t : this->outputTwins()) {
        t->twin()->setVariant(t->variant());
    }
}

void dtkComposerNodeControlMap::setVariables(void)
{

    //d->out_container->append(d->block_newitem.variant());

    d->block_index.setData((d->counter)++);
    //d->block_item.setData(d->container->at(d->counter));
}

int dtkComposerNodeControlMap::selectBranch(void)
{
    return static_cast<int>(!((d->counter) < d->size));
}

void dtkComposerNodeControlMap::begin(void)
{
    if (d->header_rcv.isEmpty())
        return;

    QVariant var_container = d->header_rcv.variant();
    d->block_container.setData(var_container);

    // d->container = d->header_rcv.container();

    // if (d->out_container)
    //     delete d->out_container;
    // d->out_container = d->container->voidClone();    
    // d->footer_emit.setData(d->out_container);

    d->counter = 0;
    // d->size = d->container->count();
    d->block_size.setData(d->size);
}

void dtkComposerNodeControlMap::end(void)
{

}

// 
// dtkComposerNodeControlMap.cpp ends here
