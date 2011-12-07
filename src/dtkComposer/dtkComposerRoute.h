/* dtkComposerRoute.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Dec  7 14:13:33 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec  7 15:04:45 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 15
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERROUTE_H
#define DTKCOMPOSERROUTE_H

class dtkComposerNodeProperty;
class dtkComposerRoutePrivate;

class dtkComposerRoute
{
public:
     dtkComposerRoute(void);
    ~dtkComposerRoute(void);

public:
    bool active(void);

public:
    dtkComposerNodeProperty *source(void);
    dtkComposerNodeProperty *destination(void);

public:
    void setSource(dtkComposerNodeProperty *property);
    void setDestination(dtkComposerNodeProperty *property);

private:
    dtkComposerRoutePrivate *d;
};

#endif
