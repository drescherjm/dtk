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

#include "dtkMonitorInteger.h"

#include <dtkComposer/dtkComposerNodeInteger.h>

dtkMonitorInteger::dtkMonitorInteger(QGraphicsItem *parent) : dtkMonitor(parent)
{

}

dtkMonitorInteger::~dtkMonitorInteger(void)
{

}

double dtkMonitorInteger::value(void)
{
    return dynamic_cast<dtkComposerNodeInteger *>(this->node())->value();
}

void dtkMonitorInteger::setValue(int value)
{
    dynamic_cast<dtkComposerNodeInteger *>(this->node())->setValue(value);
}

//
// dtkMonitorInteger.cpp ends here
