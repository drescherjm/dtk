/* dtkAboutPlugin.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Sep  5 13:21:30 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Sep 28 12:38:24 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKABOUTPLUGIN_H
#define DTKABOUTPLUGIN_H

#include "dtkGuiExport.h"

#include <QtGui/QWidget>

class dtkAboutPluginPrivate;
class dtkPlugin;

class DTKGUI_EXPORT dtkAboutPlugin : public QWidget
{
    Q_OBJECT

public:
     dtkAboutPlugin(dtkPlugin *plugin, QWidget *parent = 0);
     dtkAboutPlugin(const QString& plugin, QWidget *parent = 0);
    ~dtkAboutPlugin(void);

     bool openExternalLinks(void);

     void setOpenExternalLinks(bool open);

protected:
    void setup(dtkPlugin *plugin);

private:
    dtkAboutPluginPrivate *d;
};

#endif