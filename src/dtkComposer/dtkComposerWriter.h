/* dtkComposerWriter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:40:30 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  1 13:43:49 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 15
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

class dtkComposerScene;
class dtkComposerWriterPrivate;

class DTKCOMPOSER_EXPORT dtkComposerWriter
{
public:
             dtkComposerWriter(void);
    virtual ~dtkComposerWriter(void);

public:
    enum Type { Ascii, Binary };

public:
    void setScene(dtkComposerScene *scene);

public:
   void write(const QString& file, Type type = Ascii);

private:
    dtkComposerWriterPrivate *d;
};

#endif
