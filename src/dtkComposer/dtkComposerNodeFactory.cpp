/* dtkComposerNodeFactory.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb  7 22:37:03 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jul 12 14:11:00 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 115
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
#include "dtkComposerNodeFactory.h"
#include "dtkComposerNodeFile.h"
#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeString.h"

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
        
        dtkComposerNode *node = new dtkComposerNode;
        node->setType(dtkComposerNode::Data);
        node->setObject(data);
        node->addOutputProperty(new dtkComposerNodeProperty("this", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Multiple, node));
        return node;
    }

    if (dtkAbstractProcess *process = dtkAbstractProcessFactory::instance()->create(type)) {
        
        dtkComposerNode *node = new dtkComposerNode;
        node->setType(dtkComposerNode::Process);
        node->setObject(process);
        node->addInputProperty(new dtkComposerNodeProperty("input", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, node));
        node->addOutputProperty(new dtkComposerNodeProperty("output", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Single, node));
        return node;
    }

    if (dtkAbstractView *view = dtkAbstractViewFactory::instance()->create(type)) {
        
        dtkComposerNode *node = new dtkComposerNode;
        node->setType(dtkComposerNode::View);
        node->setObject(view);
        node->addInputProperty(new dtkComposerNodeProperty("data", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, node));
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
