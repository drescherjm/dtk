/* @(#)dtkComposerControlsListItemFactory.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/06/04 13:22:42
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerControlsListItemFactory.h"

#include "dtkComposerControlsListItem.h"
#include "dtkComposerControlsListItemInteger.h"

#include "dtkComposerControlsListItemReal.h"
#include "dtkComposerControlsListItemBoolean.h"
#include "dtkComposerControlsListItemString.h"
#include "dtkComposerControlsListItemFile.h"
#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodeReal.h"
#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeString.h"
#include "dtkComposerNodeFile.h"


dtkComposerControlsListItemFactory::dtkComposerControlsListItemFactory(void)
{
}

dtkComposerControlsListItemFactory::~dtkComposerControlsListItemFactory(void)
{
}

dtkComposerControlsListItemFactory  *dtkComposerControlsListItemFactory::instance(void)
{
    if(!s_instance)
        s_instance = new dtkComposerControlsListItemFactory;

    return s_instance;
}


dtkComposerControlsListItem *dtkComposerControlsListItemFactory::create(QListWidget *list, dtkComposerSceneNode *node)
{
    if (dtkComposerNodeInteger *i_node = dynamic_cast<dtkComposerNodeInteger *>(node->wrapee()))
        return new dtkComposerControlsListItemInteger(list, node);
    else if (dtkComposerNodeBoolean *b_node = dynamic_cast<dtkComposerNodeBoolean *>(node->wrapee()))
        return new dtkComposerControlsListItemBoolean(list, node);
    else if (dtkComposerNodeReal *d_node = dynamic_cast<dtkComposerNodeReal *>(node->wrapee()))
        return new dtkComposerControlsListItemReal(list, node);
    else if (dtkComposerNodeString *s_node = dynamic_cast<dtkComposerNodeString *>(node->wrapee()))
        return new dtkComposerControlsListItemString(list, node);
    else if (dtkComposerNodeFile *f_node = dynamic_cast<dtkComposerNodeFile *>(node->wrapee()))
        return new dtkComposerControlsListItemFile(list, node);
    else
        return new dtkComposerControlsListItem(list, node);
}

dtkComposerControlsListItemFactory *dtkComposerControlsListItemFactory::s_instance = NULL;




