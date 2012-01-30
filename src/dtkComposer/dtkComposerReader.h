/* dtkComposerReader.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:38:40 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 23:40:23 2012 (+0100)
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

#include "dtkComposerExport.h"

class dtkComposerReaderPrivate;

class DTKCOMPOSER_EXPORT dtkComposerReader
{
public:
             dtkComposerReader(void);
    virtual ~dtkComposerReader(void);

private:
    dtkComposerReaderPrivate *d;
};

#endif
