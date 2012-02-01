/* dtkComposerWriter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 23:42:34 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  1 13:44:31 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerScene.h"
#include "dtkComposerWriter.h"

#include <QtCore>

class dtkComposerWriterPrivate
{
public:
    dtkComposerScene *scene;
};

dtkComposerWriter::dtkComposerWriter(void) : d(new dtkComposerWriterPrivate)
{
    d->scene = NULL;
}

dtkComposerWriter::~dtkComposerWriter(void)
{
    delete d;

    d = NULL;
}

void dtkComposerWriter::setScene(dtkComposerScene *scene)
{
    d->scene = scene;
}

void dtkComposerWriter::write(const QString& file, Type type)
{
    Q_UNUSED(file);
    Q_UNUSED(type);
}
