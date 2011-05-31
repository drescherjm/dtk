/* dtkDistributedServerManagerOar.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:10:24 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 31 23:15:20 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedServerManagerOar.h"

class dtkDistributedServerManagerOarPrivate
{
public:
};

dtkDistributedServerManagerOar::dtkDistributedServerManagerOar(void) : d(new dtkDistributedServerManagerOarPrivate)
{

}

dtkDistributedServerManagerOar::~dtkDistributedServerManagerOar(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedServerManagerOar::discover(const QUrl& url)
{
    Q_UNUSED(url);
}
