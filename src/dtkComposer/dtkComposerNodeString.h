/* dtkComposerNodeString.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 27 15:08:06 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb 27 17:37:10 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODESTRING_H
#define DTKCOMPOSERNODESTRING_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeStringPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeString : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeString(dtkComposerNode *parent = 0);
    ~dtkComposerNodeString(void);

    QVariant value(dtkComposerNodeProperty *property);

public:
    QString value(void);

    void setText(QString text);
    void setValue(QString value);

public:
    void expand(void);
    void collapse(void);

protected slots:
    void onCollapseFinised(void);

protected:
    void  onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void run(void);

private:
    dtkComposerNodeStringPrivate *d;
};

#endif
