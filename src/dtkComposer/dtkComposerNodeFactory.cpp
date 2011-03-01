/* dtkComposerNodeFactory.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb  7 22:37:03 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar  1 15:12:28 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 163
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewFactory.h>

#include "dtkComposerNode.h"
#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeBooleanOperator.h"
#include "dtkComposerNodeCase.h"
#include "dtkComposerNodeConditional.h"
#include "dtkComposerNodeData.h"
#include "dtkComposerNodeFactory.h"
#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeLog.h"
#include "dtkComposerNodeNumber.h"
#include "dtkComposerNodeProcess.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerNodeStringComparator.h"
#include "dtkComposerNodeStringOperator.h"
#include "dtkComposerNodeView.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFactoryPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeFactoryPrivate
{
public:
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFactory
// /////////////////////////////////////////////////////////////////

dtkComposerNodeFactory::dtkComposerNodeFactory(void) : QObject(), d(new dtkComposerNodeFactoryPrivate)
{

}

dtkComposerNodeFactory::~dtkComposerNodeFactory(void)
{
    delete d;

    d = NULL;
}

dtkComposerNode *dtkComposerNodeFactory::create(QString type)
{
    if (type == "dtkComposerNumber")
        return new dtkComposerNodeNumber;

    if (type == "dtkComposerBoolean")
        return new dtkComposerNodeBoolean;

    if (type == "dtkComposerBooleanOperator")
        return new dtkComposerNodeBooleanOperator;

    if (type == "dtkComposerCase")
        return new dtkComposerNodeCase;

    if (type == "dtkComposerConditional")
        return new dtkComposerNodeConditional;

    if (type == "dtkComposerLog")
        return new dtkComposerNodeLog;

    if (type == "dtkComposerFile")
        return new dtkComposerNodeFile;

    if (type == "dtkComposerString")
        return new dtkComposerNodeString;

    if (type == "dtkComposerStringComparator")
        return new dtkComposerNodeStringComparator;

    if (type == "dtkComposerStringOperator")
        return new dtkComposerNodeStringOperator;

    if (dtkAbstractData *data = dtkAbstractDataFactory::instance()->create(type)) {
        dtkComposerNodeData *node = new dtkComposerNodeData;
        node->setObject(data);
        node->setType(type);
        return node;
    }

    if (dtkAbstractProcess *process = dtkAbstractProcessFactory::instance()->create(type)) {
        dtkComposerNodeProcess *node = new dtkComposerNodeProcess;
        node->setObject(process);
        node->setType(type);
        return node;
    }

    if (dtkAbstractView *view = dtkAbstractViewFactory::instance()->create(type)) {
        dtkComposerNodeView *node = new dtkComposerNodeView;
        node->setObject(view);
        node->setType(type);
        node->addAction("Show view", view, SLOT(show()));

        return node;
    }

    return NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFactory documentation
// /////////////////////////////////////////////////////////////////

/*! \class dtkComposerNodeFactory
 *
 *  \brief The dtkComposerNodeFactory class defines a factory for
 *  creating composition nodes based on the type of the object that is
 *  attached to it.
 *
 */
