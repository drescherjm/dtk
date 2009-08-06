/* dtkCreatorController.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Aug  6 17:55:16 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Aug  6 20:06:36 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 26
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCreatorController.h"

#include <QtCore>

class dtkCreatorControllerPrivate
{
public:
    dtkCreatorPluginBrowser *pluginBrowser;
    dtkCreatorScriptBrowser *scriptBrowser;
    dtkCreatorViewer *viewer;
};

dtkCreatorController *dtkCreatorController::instance(void)
{
    if(!s_instance)
        s_instance = new dtkCreatorController;

    return s_instance;
}

void dtkCreatorController::attach(dtkCreatorPluginBrowser *pluginBrowser)
{
    d->pluginBrowser = pluginBrowser;
}

void dtkCreatorController::attach(dtkCreatorScriptBrowser *scriptBrowser)
{
    d->scriptBrowser = scriptBrowser;
}

void dtkCreatorController::attach(dtkCreatorViewer *viewer)
{
    d->viewer = viewer;
}

dtkCreatorPluginBrowser *dtkCreatorController::pluginBrowser(void)
{
    return d->pluginBrowser;
}

dtkCreatorScriptBrowser *dtkCreatorController::scriptBrowser(void)
{
    return d->scriptBrowser;
}

dtkCreatorViewer *dtkCreatorController::viewer(void)
{
    return d->viewer;
}

dtkCreatorController::dtkCreatorController(void) : d(new dtkCreatorControllerPrivate)
{
    d->viewer = NULL;
}

dtkCreatorController::~dtkCreatorController(void)
{
    delete d;
    
    d = NULL;
}

dtkCreatorController *dtkCreatorController::s_instance = NULL;
