/* dtkComposerNodeFactory.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb  7 22:37:03 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jul 16 11:57:42 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 125
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
#include "dtkComposerNodeCondition.h"
#include "dtkComposerNodeData.h"
#include "dtkComposerNodeFactory.h"
#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodeProcess.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeString.h"
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

dtkComposerNodeFactory *dtkComposerNodeFactory::instance(void)
{
    if(!s_instance)
        s_instance = new dtkComposerNodeFactory;

    return s_instance;
}

dtkComposerNode *dtkComposerNodeFactory::create(QString type)
{
    if (type == "integer")
        return new dtkComposerNodeInteger;

    if (type == "string")
        return new dtkComposerNodeString;

    if (type == "file")
        return new dtkComposerNodeFile;

    if (type == "condition")
        return new dtkComposerNodeCondition;

    if (dtkAbstractData *data = dtkAbstractDataFactory::instance()->create(type)) {
        
        dtkComposerNodeData *node = new dtkComposerNodeData;
        node->setObject(data);
        return node;
    }

    if (dtkAbstractProcess *process = dtkAbstractProcessFactory::instance()->create(type)) {
        
        dtkComposerNodeProcess *node = new dtkComposerNodeProcess;
        node->setObject(process);
        return node;
    }

    if (dtkAbstractView *view = dtkAbstractViewFactory::instance()->create(type)) {
        
        dtkComposerNodeView *node = new dtkComposerNodeView;
        node->setObject(view);
        node->addAction("Show view", view, SLOT(show()));

        return node;
    }

    return NULL;
}

dtkComposerNodeFactory::dtkComposerNodeFactory(void) : QObject(), d(new dtkComposerNodeFactoryPrivate)
{

}

dtkComposerNodeFactory::~dtkComposerNodeFactory(void)
{
    delete d;

    d = NULL;
}

dtkComposerNodeFactory *dtkComposerNodeFactory::s_instance = NULL;

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
