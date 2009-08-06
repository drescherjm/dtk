/* dtkCreatorController.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Aug  6 17:53:03 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Aug  6 20:05:19 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCREATORCONTROLLER_H
#define DTKCREATORCONTROLLER_H

class dtkCreatorControllerPrivate;
class dtkCreatorPluginBrowser;
class dtkCreatorScriptBrowser;
class dtkCreatorViewer;

class dtkCreatorController
{
public:
    static dtkCreatorController *instance(void);

    void attach(dtkCreatorPluginBrowser *pluginBrowser);
    void attach(dtkCreatorScriptBrowser *scriptBrowser);
    void attach(dtkCreatorViewer *viewer);

    dtkCreatorPluginBrowser *pluginBrowser(void);
    dtkCreatorScriptBrowser *scriptBrowser(void);
    dtkCreatorViewer *viewer(void);

protected:
     dtkCreatorController(void);
    ~dtkCreatorController(void);

    static dtkCreatorController* s_instance;

private:
    dtkCreatorControllerPrivate *d;
};

#endif
