/* dtkCommunicatorUdp.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 16:51:02 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 21:11:48 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCommunicatorUdp.h"

class dtkCommunicatorUdpPrivate
{
public:
    
};

dtkCommunicatorUdp::dtkCommunicatorUdp(void) : dtkAbstractCommunicator(), d(new dtkCommunicatorUdpPrivate)
{

}

dtkCommunicatorUdp::~dtkCommunicatorUdp(void)
{
    delete d;

    d = NULL;
}
