/* dtkComposerReader.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:38:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. févr. 28 10:31:58 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 38
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERREADER_H
#define DTKCOMPOSERREADER_H

#include "dtkComposerExport.h"

#include <QtCore>
#include <QtXml>

class dtkComposerFactory;
class dtkComposerGraph;
class dtkComposerReaderPrivate;
class dtkComposerScene;
class dtkComposerSceneEdge;
class dtkComposerSceneNode;
class dtkComposerSceneNote;

class DTKCOMPOSER_EXPORT dtkComposerReader
{
public:
             dtkComposerReader(void);
    virtual ~dtkComposerReader(void);

public:
    void setFactory(dtkComposerFactory *factory);
    void setScene(dtkComposerScene *scene);
    void setGraph(dtkComposerGraph *graph);

public:
   bool read(const QString& file, bool append = false);

protected:
   virtual dtkComposerSceneNote *readNote(QDomNode node);
   virtual dtkComposerSceneNode *readNode(QDomNode node);
   virtual dtkComposerSceneEdge *readEdge(QDomNode node);

private:
    dtkComposerReaderPrivate *d;
};

#endif
