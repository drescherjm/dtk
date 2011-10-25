/* dtkComposerNodeProcess.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:23:54 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Oct 25 11:52:03 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 118
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeProcess.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkGlobal.h>

class dtkComposerNodeProcessPrivate
{
public:
};

dtkComposerNodeProcess::dtkComposerNodeProcess(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeProcessPrivate)
{
    this->setKind(dtkComposerNode::Process);
}

dtkComposerNodeProcess::~dtkComposerNodeProcess(void)
{
    delete d;

    d = NULL;
}

QVariant dtkComposerNodeProcess::value(dtkComposerNodeProperty *property)
{
    Q_UNUSED(property);

    DTK_DEFAULT_IMPLEMENTATION;

    return QVariant();
}

QString dtkComposerNodeProcess::implementation(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return QString();
}

void dtkComposerNodeProcess::pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);

    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkComposerNodeProcess::run(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkComposerNodeProcess::push(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);

    DTK_DEFAULT_IMPLEMENTATION;
}
