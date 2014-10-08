/* dtkComposerReader.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:38:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:01:07 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 48
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include <QtCore>
#include <QtXml>

class dtkComposerNodeFactory;
class dtkComposerGraph;
class dtkComposerReaderPrivate;
class dtkComposerScene;
class dtkComposerSceneEdge;
class dtkComposerSceneNode;
class dtkComposerSceneNote;
class dtkComposerSceneNodeLeaf;

class  dtkComposerReader
{
public:
             dtkComposerReader(void);
    virtual ~dtkComposerReader(void);

public:
    void setFactory(dtkComposerNodeFactory *factory);
    void setScene(dtkComposerScene *scene);
    void setGraph(dtkComposerGraph *graph);

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

