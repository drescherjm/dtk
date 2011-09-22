/* dtkComposerReader.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug 16 15:01:36 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Sep 20 15:20:42 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 19
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

#include <QtCore/QObject>

#include <QtXml/QDomNode>

class dtkComposerNode;
class dtkComposerScene;
class dtkComposerReaderPrivate;

class DTKCOMPOSER_EXPORT dtkComposerReader : public QObject
{
    Q_OBJECT

public:
    dtkComposerReader(dtkComposerScene *scene);
   ~dtkComposerReader(void);

   void read(const QString& fileName, bool append = false);

protected:
   virtual dtkComposerNode *readNode(QDomNode node);

private:
    dtkComposerReaderPrivate *d;
};

#endif
