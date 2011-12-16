/* dtkComposerNodeLoopDataComposite.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Oct 12 15:59:53 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 17 16:25:47 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */


#ifndef DTKCOMPOSERNODELOOPDATACOMPOSITE_H
#define DTKCOMPOSERNODELOOPDATACOMPOSITE_H

#include "dtkComposerExport.h"
#include <dtkComposer/dtkComposerNodeLoop>

class dtkComposerNode;
class dtkComposerNodeProperty;

class dtkComposerNodeLoopDataCompositePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeLoopDataComposite : public dtkComposerNodeLoop
{
    Q_OBJECT

public:
     dtkComposerNodeLoopDataComposite(dtkComposerNode *parent = 0);
    ~dtkComposerNodeLoopDataComposite(void);

public:
    void layout(void);

public slots:
    void update(void);

public:
    QVariant value(dtkComposerNodeProperty *property);

public:
    void onEdgeConnected(dtkComposerEdge *edge);

private:
    dtkComposerNodeLoopDataCompositePrivate *d;
};

#endif
