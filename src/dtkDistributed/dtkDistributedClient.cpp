/* dtkDistributedClient.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:15:13 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 25 14:46:15 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedClient.h"

#include <QtNetwork>

class dtkDistributedClientPrivate : public QTcpSocket
{
public:
};

dtkDistributedClient::dtkDistributedClient(void) : d(new dtkDistributedClientPrivate)
{

}

dtkDistributedClient::~dtkDistributedClient(void)
{
    delete d;

    d = NULL;
}
