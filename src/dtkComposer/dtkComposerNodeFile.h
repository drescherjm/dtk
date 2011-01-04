/* dtkComposerNodeFile.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul  8 13:26:20 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Dec 20 18:00:39 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEFILE_H
#define DTKCOMPOSERNODEFILE_H

#include "dtkComposerNode.h"

class dtkComposerNodeFilePrivate;

class dtkComposerNodeFile : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeFile(dtkComposerNode *parent = 0);
    ~dtkComposerNodeFile(void);

    QVariant value(dtkComposerNodeProperty *property);

public slots:
    void editFile(void);
    void getFileName(void);
    void setFileName(const QString& file);

protected:
    void  onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeFilePrivate *d;
};

#endif
