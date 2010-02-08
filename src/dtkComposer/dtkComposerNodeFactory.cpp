/* dtkComposerNodeFactory.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb  7 22:37:03 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb  8 14:25:17 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 76
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
#include "dtkComposerNodeFactory.h"
#include "dtkComposerNodeProperty.h"

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
