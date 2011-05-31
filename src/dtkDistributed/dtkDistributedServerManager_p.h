/* dtkDistributedServerManager_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:38:18 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 31 23:39:07 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDSERVERMANAGER_P_H
#define DTKDISTRIBUTEDSERVERMANAGER_P_H

#include <QtCore>

class dtkDistributedNode;

class dtkDistributedServerManagerPrivate
{
public:
    QList<dtkDistributedNode *> nodes;
};

#endif
