/* dtkComposerWriter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:40:30 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 23:40:51 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
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

class dtkComposerWriterPrivate;

class DTKCOMPOSER_EXPORT dtkComposerWriter
{
public:
             dtkComposerWriter(void);
    virtual ~dtkComposerWriter(void);

private:
    dtkComposerWriterPrivate *d;
};

#endif
