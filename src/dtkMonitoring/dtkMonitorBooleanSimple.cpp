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
#include "dtkMonitorBooleanSimple.h"

#include <QGraphicsPixmapItem>

class dtkMonitorBooleanSimplePrivate
{
public:
    QGraphicsPixmapItem *pixmap_on;
    QGraphicsPixmapItem *pixmap_off;
};

dtkMonitorBooleanSimple::dtkMonitorBooleanSimple(QGraphicsItem *parent) : dtkMonitorBoolean(parent)
{
    d = new dtkMonitorBooleanSimplePrivate;

    d->pixmap_on  = new QGraphicsPixmapItem(this);
    d->pixmap_off = new QGraphicsPixmapItem(this);
}

dtkMonitorBooleanSimple::~dtkMonitorBooleanSimple(void)
{
    delete d;
}
//
// dtkMonitorBooleanSimple.cpp ends here
