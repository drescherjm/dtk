/* dtkPlugin.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Oct 31 14:14:48 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Aug  4 19:24:48 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 55
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkPlugin.h>

// /////////////////////////////////////////////////////////////////
// dtkPluginPrivate
// /////////////////////////////////////////////////////////////////

class dtkPluginPrivate
{
public:
};

// /////////////////////////////////////////////////////////////////
// dtkPlugin
// /////////////////////////////////////////////////////////////////

dtkPlugin::dtkPlugin(QObject * parent) : QObject(parent), d(new dtkPluginPrivate)
{

}

dtkPlugin::~dtkPlugin(void)
{

}

//! Returns a widget reprensenting the user interface of the plugin.

/*! Plugins use to be loaded at runtime by an application. Overload
 *  this method into your plugin if you whish to provide an interface
 *  for users to control the behaviour of the plugins.
 * 
 *  For plugins providing a proxy for a concept among dtkAbstractData,
 *  dtkAbstractDevice, dtkAbstractProcess or dtkAbstractView, it is a
 *  good habit to let the proxy handle its user interface.

\code
QWidget *dtkConcreteDataPlugin::ui(void)
{
    return dtkConcreteDataPlugin::ui();
}

class dtkConcreteDataUi;

class dtkConcreteData : public dtkAbstractData
{
    ...

public:
    ...
    static QWidget *ui(void) {
        if(!s_ui)
            s_ui = new dtkConcreteDataUi;

        return s_ui;
    }
    ...

private:
    static dtkConcreteDataUi *s_ui;
};

dtkConcreteDataWidget *dtkConcreteData::s_ui = NULL;
\endcode

   Consider using dtkUiView and dtkUiItem to provide uniform look and feel to your users.

 * \return A widget containing a user interface that will be parented by the host application.
 */

QWidget *dtkPlugin::ui(void)
{
    return NULL;
}
