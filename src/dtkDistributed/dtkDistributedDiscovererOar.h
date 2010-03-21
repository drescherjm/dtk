/* dtkDistributedDiscovererOar.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Mar 17 09:56:45 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar 21 23:02:22 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDDISCOVEREROAR_H
#define DTKDISTRIBUTEDDISCOVEREROAR_H

#include "dtkDistributedDiscoverer.h"

class DTKDISTRIBUTED_EXPORT dtkDistributedDiscovererOar : public dtkDistributedDiscoverer
{
public slots:
    void discover(const QUrl& url);
};

#endif
