/* dtkComposerWriter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug 16 15:01:36 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Feb  3 17:34:54 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 24
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERWRITER_H
#define DTKCOMPOSERWRITER_H

#include <QtCore/QObject>

#include <QtXml/QDomElement>

class dtkComposerNode;
class dtkComposerScene;
class dtkComposerWriterPrivate;

class dtkComposerWriter : public QObject
{
    Q_OBJECT

public:
    dtkComposerWriter(dtkComposerScene *scene);
   ~dtkComposerWriter(void);

   void write(const QString& fileName);

protected:
   virtual QDomElement writeNode(dtkComposerNode *node, QDomElement& element, QDomDocument& document);

   virtual void extend(dtkComposerNode *node, QDomElement& element, QDomDocument& document);

private:
    dtkComposerWriterPrivate *d;
};

#endif
