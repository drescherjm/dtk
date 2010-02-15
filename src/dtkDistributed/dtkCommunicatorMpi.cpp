/* dtkCommunicatorMpi.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 16:51:02 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 21:14:56 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCommunicatorMpi.h"

class dtkCommunicatorMpiPrivate
{
public:
    
};

dtkCommunicatorMpi::dtkCommunicatorMpi(void) : dtkAbstractCommunicator(), d(new dtkCommunicatorMpiPrivate)
{

}

dtkCommunicatorMpi::~dtkCommunicatorMpi(void)
{
    delete d;

    d = NULL;
}
