/* dtkComposerReader.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:41:08 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  1 13:48:14 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerReader.h"
#include "dtkComposerScene.h"

#include <QtCore>

class dtkComposerReaderPrivate
{
public:
    dtkComposerScene *scene;
};

dtkComposerReader::dtkComposerReader(void) : d(new dtkComposerReaderPrivate)
{
    d->scene = NULL;
}

dtkComposerReader::~dtkComposerReader(void)
{
    delete d;

    d = NULL;
}

void dtkComposerReader::setScene(dtkComposerScene *scene)
{
    d->scene = scene;
}

bool dtkComposerReader::read(const QString& file, bool append)
{
    return true;
}
