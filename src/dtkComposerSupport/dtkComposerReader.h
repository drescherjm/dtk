/* dtkComposerReader.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerSupportExport.h"

#include <QDomNode>

class dtkComposerFactory;
class dtkComposerGraph;
class dtkComposerReaderPrivate;
class dtkComposerScene;
class dtkComposerSceneEdge;
class dtkComposerSceneNode;
class dtkComposerSceneNote;
class dtkComposerSceneNodeLeaf;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerReader
{
public:
             dtkComposerReader(void);
    virtual ~dtkComposerReader(void);

public:
    void setScene(dtkComposerScene *scene);
    void setGraph(dtkComposerGraph *graph);
    void setFactory(dtkComposerFactory *factory);

public:
    void clear(void);

public:
   bool read(const QString& file, bool append = false);

public:
   bool readString(const QString& data, bool append = false, bool paste = false);

protected:
   virtual dtkComposerSceneNote *readNote(QDomNode node);
   virtual dtkComposerSceneNode *readNode(QDomNode node, bool paste = false);
   virtual dtkComposerSceneEdge *readEdge(QDomNode node);

protected:
   virtual void extend(const QDomNode& node, dtkComposerSceneNodeLeaf* leaf);

private:
   dtkComposerReaderPrivate *d;
};
