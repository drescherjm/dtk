/* dtkComposerReaderNoScene.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:38:40 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include <QtCore>
#include <QtXml>

class dtkComposerNode;
class dtkComposerNodeFactory;
class dtkComposerNodeLeaf;
class dtkComposerGraph;
class dtkComposerReaderNoScenePrivate;

class DTKCOMPOSER_EXPORT dtkComposerReaderNoScene
{
public:
             dtkComposerReaderNoScene(void);
    virtual ~dtkComposerReaderNoScene(void);

public:
    void setFactory(dtkComposerNodeFactory *factory);
    void setGraph(dtkComposerGraph *graph);

public:
    void clear(void);

public:
   bool read(const QString& file);

public:
   bool readString(const QString& data);

protected:
   virtual dtkComposerNode *readNode(QDomNode node);
   virtual void readEdge(QDomNode node);

 protected:
   virtual void extend(const QDomNode& node, dtkComposerNodeLeaf* leaf);

private:
    dtkComposerReaderNoScenePrivate *d;
};

