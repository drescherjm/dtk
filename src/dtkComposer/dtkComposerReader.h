/* dtkComposerReader.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:38:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  1 21:24:09 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 24
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
class dtkComposerReaderPrivate;
class dtkComposerScene;
class dtkComposerSceneNode;

class DTKCOMPOSER_EXPORT dtkComposerReader
{
public:
             dtkComposerReader(void);
    virtual ~dtkComposerReader(void);

public:
    void setFactory(dtkComposerFactory *factory);
    void setScene(dtkComposerScene *scene);

public:
   bool read(const QString& file, bool append = false);

protected:
   virtual dtkComposerSceneNode *readNode(QDomNode node);

private:
    dtkComposerReaderPrivate *d;
};

#endif
