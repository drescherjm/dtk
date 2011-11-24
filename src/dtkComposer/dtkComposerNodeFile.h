/* dtkComposerNodeFile.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul  8 13:26:20 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Nov 24 14:42:59 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 41
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

    const QUrl& url(void);
    const QString& name(void);

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

public:
    bool onLeftRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *destination);
    bool onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeFilePrivate *d;
};

#endif
