/* dtkComposerNodeFile.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul  8 13:26:20 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Nov 24 12:55:12 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 34
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEFILE_H
#define DTKCOMPOSERNODEFILE_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeFilePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeFile : public dtkComposerNode
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
    void getUrl(void);
    void setUrl(const QString& url);

public:
    virtual dtkComposerNodeAbstractTransmitter *emitter(dtkComposerNodeProperty *property);

protected:
    void pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeFilePrivate *d;
};

#endif
