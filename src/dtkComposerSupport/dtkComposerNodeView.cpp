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

#include "dtkComposerMetatype.h"

//#include "dtkComposerNodeVector3D.h"
//#include "dtkComposerNodeQuaternion.h"
#include "dtkComposerNodeView.h"

#include <dtkComposer/dtkComposerTransmitterEmitter.h>
#include <dtkComposer/dtkComposerTransmitterReceiver.h>

#include <dtkLog/dtkLog>

#include <dtkCoreSupport/dtkAbstractData>
#include <dtkCoreSupport/dtkAbstractView>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeViewPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeViewPrivate
{
public:
    dtkComposerTransmitterReceiverSupport<QString> receiver_type;
    dtkComposerTransmitterReceiverSupport<bool> receiver_fullscreen;
    dtkComposerTransmitterReceiverSupport<dtkVector3DReal> receiver_head_position;
    dtkComposerTransmitterReceiverSupport<dtkQuaternionReal> receiver_head_orientation;
    dtkComposerTransmitterReceiverSupport<dtkVector3DReal> receiver_screen_upper_left;
    dtkComposerTransmitterReceiverSupport<dtkVector3DReal> receiver_screen_lower_left;
    dtkComposerTransmitterReceiverSupport<dtkVector3DReal> receiver_screen_lower_right;
    dtkComposerTransmitterReceiverSupport<dtkAbstractData> receiver_data;

public:
    dtkAbstractView *view;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeView implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeView::dtkComposerNodeView(void) : QObject(), dtkComposerNodeLeafViewSupport(), d(new dtkComposerNodeViewPrivate)
{
    d->view = NULL;

    this->appendReceiver(&(d->receiver_type));
    this->appendReceiver(&(d->receiver_fullscreen));
    this->appendReceiver(&(d->receiver_head_position));
    this->appendReceiver(&(d->receiver_head_orientation));
    this->appendReceiver(&(d->receiver_screen_upper_left));
    this->appendReceiver(&(d->receiver_screen_lower_left));
    this->appendReceiver(&(d->receiver_screen_lower_right));
    this->appendReceiver(&(d->receiver_data));

}

dtkComposerNodeView::~dtkComposerNodeView(void)
{
    if (d->view)
        delete d->view;
    d->view = NULL;

    delete d;

    d = NULL;
}

QString dtkComposerNodeView::type(void)
{
    return "view";
}

QString dtkComposerNodeView::titleHint(void)
{
    return "View";
}

QString dtkComposerNodeView::inputLabelHint(int port)
{
    if(port == 0)
        return "type";

    if(port == 1)
        return "fullscreen";

    if(port == 2)
        return "head position";

    if(port == 3)
        return "head orientation";

    if(port == 4)
        return "screen upper left";

    if(port == 5)
        return "screen lower left";

    if(port == 6)
        return "screen lower right";

    if(port == 7)
        return "data";

    return dtkComposerNodeLeaf::inputLabelHint(port);
}

QString dtkComposerNodeView::outputLabelHint(int port)
{
    return dtkComposerNodeLeaf::outputLabelHint(port);
}

void dtkComposerNodeView::run(void)
{
    if (this->implementationHasChanged())
        d->view = this->view();

    if (!d->view) {
        dtkWarn() << "no view, abort "<< this->currentImplementation();
        return;
    }

    if(!d->receiver_fullscreen.isEmpty() && d->receiver_fullscreen.data()) {
        d->view->widget()->showFullScreen();
    } else {
        d->view->widget()->resize(1024, 1024);
        d->view->widget()->show();
    }

    if(!d->receiver_head_position.isEmpty())
        d->view->setHeadPosition(*d->receiver_head_position.data());

    if(!d->receiver_head_orientation.isEmpty())
        d->view->setHeadOrientation(*d->receiver_head_orientation.data());

    if(!d->receiver_screen_upper_left.isEmpty())
        d->view->setUpperLeft(*d->receiver_screen_upper_left.data());

    if(!d->receiver_screen_lower_left.isEmpty())
        d->view->setLowerLeft(*d->receiver_screen_lower_left.data());

    if(!d->receiver_screen_lower_right.isEmpty())
        d->view->setLowerRight(*d->receiver_screen_lower_right.data());

    if(!d->receiver_data.isEmpty())
        foreach (QVariant var, d->receiver_data.allData())
            d->view->setData(var.value<dtkAbstractData*>());
}

// 
// dtkComposerNodeView.cpp ends here
