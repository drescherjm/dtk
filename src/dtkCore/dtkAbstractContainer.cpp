/* dtkAbstractContainer.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Apr 27 16:15:20 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr 27 16:55:15 2012 (+0200)
 *           By: tkloczko
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkAbstractContainer.h"

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainer implementation
// /////////////////////////////////////////////////////////////////

dtkAbstractContainer::dtkAbstractContainer(dtkAbstractData *parent) : dtkAbstractData(parent)
{

}

dtkAbstractContainer::dtkAbstractContainer(const dtkAbstractContainer& other) : dtkAbstractData(other)
{

}

dtkAbstractContainer::~dtkAbstractContainer(void)
{

}

dtkAbstractContainer& dtkAbstractContainer::operator=(const dtkAbstractContainer& other)
{
    dtkAbstractData::operator=(other);

    return *this;
}

