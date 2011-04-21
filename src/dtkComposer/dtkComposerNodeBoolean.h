/* dtkComposerNodeBoolean.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 25 10:04:24 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr  8 16:26:28 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEBOOLEAN_H
#define DTKCOMPOSERNODEBOOLEAN_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeBooleanPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeBoolean : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeBoolean(dtkComposerNode *parent = 0);
    ~dtkComposerNodeBoolean(void);

    QVariant value(dtkComposerNodeProperty *property);

public:
    bool value(void);

    void setValue(bool value);

protected:
    void pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeBooleanPrivate *d;
};

#endif
