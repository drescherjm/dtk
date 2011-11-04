/* dtkComposerNodeLoopDataComposite.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Oct 12 15:59:53 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Nov  4 15:48:29 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 12
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
    bool evaluate(dtkComposerEvaluatorPrivate *evaluator);

public:
    QVariant value(dtkComposerNodeProperty *property);

private:
    dtkComposerNodeLoopDataCompositePrivate *d;

private:
    friend class dtkComposerEvaluatorPrivate;
};

#endif
