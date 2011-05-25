/* dtkDistributedServer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:15:13 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 25 14:45:17 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedServer.h"

#include <QtNetwork>

class dtkDistributedServerPrivate : public QTcpServer
{
public:
};

dtkDistributedServer::dtkDistributedServer(void) : d(new dtkDistributedServerPrivate)
{

}

dtkDistributedServer::~dtkDistributedServer(void)
{
    delete d;

    d = NULL;
}
