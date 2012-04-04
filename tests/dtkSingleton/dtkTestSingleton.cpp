/* dtkTestSingleton.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Aug 18 19:42:04 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr  3 16:52:09 2012 (+0200)
 *           By: tkloczko
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkTestSingleton.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkSingleton.h>

#include <dtkLog/dtkLog.h>

int dtkTestSingleton::ms_count = 0;

DTK_IMPLEMENT_SINGLETON( dtkTestSingleton );

dtkTestSingleton::dtkTestSingleton()
{
    dtkDebug() << DTK_LINK_TEXT << "Constructor";
    ++ms_count;
}

dtkTestSingleton::~dtkTestSingleton()
{
    dtkDebug() << DTK_LINK_TEXT << "Destructor";
    --ms_count;
}

int dtkTestSingleton::InstanceCount()
{
    return ms_count;
}


