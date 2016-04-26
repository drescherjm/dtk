// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkWidgetFactory.h"

dtkWidgetFactory::dtkWidgetFactory(void)
{

}

dtkWidgetFactory::~dtkWidgetFactory(void)
{

}

// /////////////////////////////////////////////////////////////////
// Type creator registration
// /////////////////////////////////////////////////////////////////

void dtkWidgetFactory::record(const QString& key, QWidget* widget)
{
    if (this->widgets.contains(key)) {
        qDebug() << Q_FUNC_INFO << "Factory already contains key" << key << ". Nothing is done";
        return;
    }

    this->widgets.insert(key, widget);
}

// /////////////////////////////////////////////////////////////////
// Type creator invokation
// /////////////////////////////////////////////////////////////////

QWidget *dtkWidgetFactory::get(const QString& key) const
{
    if(!this->widgets.contains(key))
        return NULL;

    return this->widgets.value(key);
}

// /////////////////////////////////////////////////////////////////
// Type creator inspection
// /////////////////////////////////////////////////////////////////

QStringList dtkWidgetFactory::keys(void) const
{
    return this->widgets.keys();
}

//
// dtkWidgetFactory_t.h ends here
