/* dtkComposerReader.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:38:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  1 13:48:20 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 16
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

class dtkComposerReaderPrivate;
class dtkComposerScene;

class DTKCOMPOSER_EXPORT dtkComposerReader
{
public:
             dtkComposerReader(void);
    virtual ~dtkComposerReader(void);

public:
    void setScene(dtkComposerScene *scene);

public:
   bool read(const QString& file, bool append = false);

private:
    dtkComposerReaderPrivate *d;
};

#endif
