/* dtkComposerWriter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug 16 15:01:36 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Nov 30 20:30:05 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 11
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
