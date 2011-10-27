/* dtkComposerWriter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug 16 15:01:36 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Oct 19 15:04:07 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 28
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

#include <QtCore/QObject>

#include <QtXml/QDomElement>

class dtkComposerNode;
class dtkComposerScene;
class dtkComposerWriterPrivate;

class DTKCOMPOSER_EXPORT dtkComposerWriter : public QObject
{
    Q_OBJECT

public:
    enum Type {
         Ascii,
        Binary
    };

public:
    dtkComposerWriter(dtkComposerScene *scene);
   ~dtkComposerWriter(void);

   void write(const QString& fileName, Type type = Ascii);

protected:
   virtual QDomElement writeNode(dtkComposerNode *node, QDomElement& element, QDomDocument& document);

   virtual void extend(dtkComposerNode *node, QDomElement& element, QDomDocument& document);

private:
    dtkComposerWriterPrivate *d;
};

#endif
