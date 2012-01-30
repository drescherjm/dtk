/* dtkComposer.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:34:49 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 10:34:56 2012 (+0100)
 *           By: tkloczko
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposer.h"
#include "dtkComposer_p.h"

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkComposer
// /////////////////////////////////////////////////////////////////

dtkComposer::dtkComposer(QWidget *parent) : QWidget(parent), d(new dtkComposerPrivate)
{

}

dtkComposer::~dtkComposer(void)
{
    delete d;
    
    d = NULL;
}
