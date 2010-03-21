/* dtkDistributedDiscovererTorque.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Mar 17 09:53:41 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar 21 23:02:09 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDDISCOVERERTORQUE_H
#define DTKDISTRIBUTEDDISCOVERERTORQUE_H

#include "dtkDistributedDiscoverer.h"

class DTKDISTRIBUTED_EXPORT dtkDistributedDiscovererTorque : public dtkDistributedDiscoverer
{
public slots:
    void discover(const QUrl& url);
};

#endif
