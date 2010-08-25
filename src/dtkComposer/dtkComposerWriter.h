/* dtkComposerWriter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug 16 15:01:36 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Aug 16 15:35:47 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERWRITER_H
#define DTKCOMPOSERWRITER_H

#include <QObject>

class dtkComposerScene;
class dtkComposerWriterPrivate;

class dtkComposerWriter : public QObject
{
    Q_OBJECT

public:
    dtkComposerWriter(dtkComposerScene *scene);
   ~dtkComposerWriter(void);

   void write(const QString& fileName);

private:
    dtkComposerWriterPrivate *d;
};

#endif
