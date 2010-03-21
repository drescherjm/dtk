/* dtkDistributedDiscoverer_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Mar 21 22:56:17 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar 21 22:57:52 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDDISCOVERER_P_H
#define DTKDISTRIBUTEDDISCOVERER_P_H

#include <QtCore>

class dtkDistributedNode;

class dtkDistributedDiscovererPrivate
{
public:
    QList<dtkDistributedNode *> nodes;
};

#endif
