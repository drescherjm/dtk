/* dtkCreatorWidgetFactory.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Aug  6 18:05:54 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Aug  6 18:08:02 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCreatorWidgetFactory.h"

dtkCreatorWidgetFactory *dtkCreatorWidgetFactory::instance()
{
    if(!m_instance)
	m_instance = new dtkCreatorWidgetFactory;

    return m_instance;
}

dtkCreatorWidgetFactory::dtkCreatorWidgetFactory(void)
{

}

dtkCreatorWidgetFactory::~dtkCreatorWidgetFactory(void)
{

}

dtkCreatorWidgetFactoryButton *dtkCreatorWidgetFactory::createButton(QString title, QString callback)
{
    dtkCreatorWidgetFactoryButton *button = new dtkCreatorWidgetFactoryButton(title, callback);
    connect(button, SIGNAL(interpret(const QString&, int *)), 
	    this,   SIGNAL(interpret(const QString&, int *)));
    return button;
}

dtkCreatorWidgetFactoryGroupBox *dtkCreatorWidgetFactory::createGroupBox(QString title)
{
    return new dtkCreatorWidgetFactoryGroupBox(title);
}

dtkCreatorWidgetFactory *dtkCreatorWidgetFactory::m_instance = NULL;
