/* dtkComposerReader.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug 16 15:01:36 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Aug 16 15:42:00 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERREADER_H
#define DTKCOMPOSERREADER_H

#include <QObject>

class dtkComposerScene;
class dtkComposerReaderPrivate;

class dtkComposerReader : public QObject
{
    Q_OBJECT

public:
    dtkComposerReader(dtkComposerScene *scene);
   ~dtkComposerReader(void);

   void read(const QString& fileName);

private:
    dtkComposerReaderPrivate *d;
};

#endif
