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

#include "dtkCoreWidgetFactory.h"

dtkCoreWidgetFactory::dtkCoreWidgetFactory(void)
{

}

dtkCoreWidgetFactory::~dtkCoreWidgetFactory(void)
{

}

// /////////////////////////////////////////////////////////////////
// Type creator registration
// /////////////////////////////////////////////////////////////////

void dtkCoreWidgetFactory::record(const QString& key, QWidget* widget)
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

QWidget *dtkCoreWidgetFactory::get(const QString& key) const
{
    if(!this->widgets.contains(key))
        return NULL;

    return this->widgets.value(key);
}

// /////////////////////////////////////////////////////////////////
// Type creator inspection
// /////////////////////////////////////////////////////////////////

QStringList dtkCoreWidgetFactory::keys(void) const
{
    return this->widgets.keys();
}

//
// dtkCoreWidgetFactory_t.h ends here
