/* dtkComposerWriter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:40:30 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mer. avril  4 10:22:02 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 44
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERWRITER_H
#define DTKCOMPOSERWRITER_H

#include "dtkComposerExport.h"

#include <QtCore>
#include <QtXml>

class dtkComposerScene;
class dtkComposerSceneEdge;
class dtkComposerSceneNode;
class dtkComposerSceneNodeComposite;
class dtkComposerSceneNote;
class dtkComposerWriterPrivate;

class DTKCOMPOSER_EXPORT dtkComposerWriter
{
public:
             dtkComposerWriter(void);
    virtual ~dtkComposerWriter(void);

public:
    enum Type {
        Ascii,
        Binary
    };

public:
    void setScene(dtkComposerScene *scene);

public:
   void write(const QString& file, Type type = Ascii);

public:
    QDomDocument toXML(dtkComposerSceneNodeComposite *rootNode);

protected:
   virtual QDomElement writeNote(dtkComposerSceneNote *note, QDomElement& element, QDomDocument& document);
   virtual QDomElement writeNode(dtkComposerSceneNode *node, QDomElement& element, QDomDocument& document);
   virtual QDomElement writeEdge(dtkComposerSceneEdge *edge, QDomElement& element, QDomDocument& document);

protected:
   virtual void extend(dtkComposerSceneNode *node, QDomElement& element, QDomDocument& document);

private:
    dtkComposerWriterPrivate *d;
};

#endif
