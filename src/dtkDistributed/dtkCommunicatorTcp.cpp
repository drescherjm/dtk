/* dtkCommunicatorTcp.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 16:51:02 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 21:11:37 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCommunicatorTcp.h"

class dtkCommunicatorTcpPrivate
{
public:
    
};

dtkCommunicatorTcp::dtkCommunicatorTcp(void) : dtkAbstractCommunicator(), d(new dtkCommunicatorTcpPrivate)
{

}

dtkCommunicatorTcp::~dtkCommunicatorTcp(void)
{
    delete d;

    d = NULL;
}
