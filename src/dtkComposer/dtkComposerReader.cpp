/* dtkComposerReader.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:41:08 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 23:44:56 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerReader.h"

#include <QtCore>

class dtkComposerReaderPrivate
{
public:
};

dtkComposerReader::dtkComposerReader(void) : d(new dtkComposerReaderPrivate)
{

}

dtkComposerReader::~dtkComposerReader(void)
{
    delete d;

    d = NULL;
}
