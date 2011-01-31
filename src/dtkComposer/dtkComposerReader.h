/* dtkComposerReader.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug 16 15:01:36 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jan 31 23:52:55 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERREADER_H
#define DTKCOMPOSERREADER_H

#include <QtCore/QObject>

#include <QtXml/QDomNode>

class dtkComposerNode;
class dtkComposerScene;
class dtkComposerReaderPrivate;

class dtkComposerReader : public QObject
{
    Q_OBJECT

public:
    dtkComposerReader(dtkComposerScene *scene);
   ~dtkComposerReader(void);

   void read(const QString& fileName);

protected:
   virtual dtkComposerNode *readNode(QDomNode node);

private:
    dtkComposerReaderPrivate *d;
};

#endif
