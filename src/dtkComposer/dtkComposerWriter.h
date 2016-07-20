/* dtkComposerWriter.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:40:30 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mer. avril  2 13:07:54 2014 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 55
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

#include <QDomDocument>

class dtkComposerScene;
class dtkComposerSceneEdge;
class dtkComposerSceneNode;
class dtkComposerSceneNodeComposite;
class dtkComposerSceneNote;
class dtkComposerWriterPrivate;

class  DTKCOMPOSER_EXPORT dtkComposerWriter
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
    void writeNode(dtkComposerSceneNodeComposite *node, const QString& file, Type type = Ascii);

public:
    QDomDocument toXML(dtkComposerSceneNodeComposite *rootNode, bool addSelf = true);

protected:
    virtual QDomElement writeNote(dtkComposerSceneNote *note, QDomElement& element, QDomDocument& document);
    virtual QDomElement writeNode(dtkComposerSceneNode *node, QDomElement& element, QDomDocument& document);
    virtual QDomElement writeEdge(dtkComposerSceneEdge *edge, QDomElement& element, QDomDocument& document);

protected:
    virtual void extend(dtkComposerSceneNode *node, QDomElement& element, QDomDocument& document);

private:
    dtkComposerWriterPrivate *d;
};

