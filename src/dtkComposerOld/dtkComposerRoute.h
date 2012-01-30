/* dtkComposerRoute.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Dec  7 14:13:33 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Dec 13 12:30:51 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 20
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
    bool   active(void);
    void   activate(void);
    void inactivate(void);

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
