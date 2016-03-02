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

#include "dtkMonitorReal.h"

#include <dtkComposer/dtkComposerNodeReal.h>

dtkMonitorReal::dtkMonitorReal(QGraphicsItem *parent) : dtkMonitor(parent)
{

}

dtkMonitorReal::~dtkMonitorReal(void)
{

}

double dtkMonitorReal::value(void)
{
    return dynamic_cast<dtkComposerNodeReal *>(this->node())->value();
}

void dtkMonitorReal::setValue(double value)
{
    dynamic_cast<dtkComposerNodeReal *>(this->node())->setValue(value);
}

//
// dtkMonitorReal.cpp ends here
