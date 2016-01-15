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

#include "dtkMonitorBoolean.h"

#include <dtkComposer/dtkComposerNodeBoolean.h>

dtkMonitorBoolean::dtkMonitorBoolean(QGraphicsItem *parent) : dtkMonitor(parent)
{

}

dtkMonitorBoolean::~dtkMonitorBoolean(void)
{

}

bool dtkMonitorBoolean::value(void)
{
    return dynamic_cast<dtkComposerNodeBoolean *>(this->node())->value();
}

void dtkMonitorBoolean::setValue(bool value)
{
    dynamic_cast<dtkComposerNodeBoolean *>(this->node())->setValue(value);
}

//
// dtkMonitorBoolean.cpp ends here
