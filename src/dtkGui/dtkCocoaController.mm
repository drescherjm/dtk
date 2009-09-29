/* dtkCocoaController.mm --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 13 18:50:55 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Sep 21 10:37:06 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <Cocoa/Cocoa.h>

#include <dtkGui/dtkCocoaController.h>

class dtkCocoaControllerPrivate
{
public:
    NSAutoreleasePool *pool;
};

dtkCocoaController *dtkCocoaController::instance(void)
{
    if(!s_instance)
	s_instance = new dtkCocoaController;

    return s_instance;
}

void dtkCocoaController::initialize(void)
{
    d->pool = [[NSAutoreleasePool alloc] init];

    NSApplicationLoad();
}

void dtkCocoaController::uninitialize(void)
{
    [d->pool release];
}

dtkCocoaController::dtkCocoaController(void) : d(new dtkCocoaControllerPrivate)
{

}

dtkCocoaController::~dtkCocoaController(void)
{
    delete d;

    d = NULL;
}

dtkCocoaController *dtkCocoaController::s_instance = NULL;
