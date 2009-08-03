/* dtkAbstractFactory.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 12 11:05:50 2008 (+0100)
 * Version: $Id$
 * Last-Updated:  Wed Mar 25 13:19:44 2009
 *           By: Jean-Christophe Lombardo
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore/QtGlobal>

#include <dtkCore/dtkAbstractFactory.h>

dtkAbstractFactory::dtkAbstractFactory(void)
{
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(clear()) );
}

dtkAbstractFactory::~dtkAbstractFactory(void)
{

}
