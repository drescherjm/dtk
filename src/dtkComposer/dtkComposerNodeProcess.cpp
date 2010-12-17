/* dtkComposerNodeProcess.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:23:54 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Nov 26 15:03:05 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 107
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
    if(this->object())
        delete this->object();

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

void dtkComposerNodeProcess::onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);

    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkComposerNodeProcess::onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);

    DTK_DEFAULT_IMPLEMENTATION;
}
