/* dtkCommunicatorTcp.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 16:50:54 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 21:10:47 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMMUNICATORTCP_H
#define DTKCOMMUNICATORTCP_H

#include "dtkAbstractCommunicator.h"

class dtkCommunicatorTcpPrivate;

class DTKDISTRIBUTED_EXPORT dtkCommunicatorTcp : public dtkAbstractCommunicator
{
    Q_OBJECT

public:
     dtkCommunicatorTcp(void);
    ~dtkCommunicatorTcp(void);

private:
    dtkCommunicatorTcpPrivate *d;
};

#endif
