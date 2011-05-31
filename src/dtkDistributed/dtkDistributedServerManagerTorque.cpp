/* dtkDistributedServerManagerTorque.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:10:24 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 31 23:15:29 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedServerManagerTorque.h"

class dtkDistributedServerManagerTorquePrivate
{
public:
};

dtkDistributedServerManagerTorque::dtkDistributedServerManagerTorque(void) : d(new dtkDistributedServerManagerTorquePrivate)
{

}

dtkDistributedServerManagerTorque::~dtkDistributedServerManagerTorque(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedServerManagerTorque::discover(const QUrl& url)
{
    Q_UNUSED(url);
}
