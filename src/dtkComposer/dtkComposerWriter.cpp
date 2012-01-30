/* dtkComposerWriter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:42:34 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 23:44:47 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerWriter.h"

#include <QtCore>

class dtkComposerWriterPrivate
{
public:
};

dtkComposerWriter::dtkComposerWriter(void) : d(new dtkComposerWriterPrivate)
{

}

dtkComposerWriter::~dtkComposerWriter(void)
{
    delete d;

    d = NULL;
}
