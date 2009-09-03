/* dtkCreatorPluginBrowser.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 10:30:24 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep  3 20:04:49 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 21
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCREATORPLUGINBROWSER_H
#define DTKCREATORPLUGINBROWSER_H

#include <QtCore>
#include <QtGui>

#include <dtkGui/dtkSplitter.h>

// /////////////////////////////////////////////////////////////////
// dtkCreatorPluginList
// /////////////////////////////////////////////////////////////////

class dtkCreatorPluginListPrivate;

class dtkCreatorPluginList : public dtkSplitter
{
    Q_OBJECT

public:
     dtkCreatorPluginList(QWidget *parent = 0);
    ~dtkCreatorPluginList(void);

signals:
    void pluginClicked(QWidget *);

public slots:
    void onPluginClicked(QString name);

private:
    dtkCreatorPluginListPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkCreatorPluginWidget
// /////////////////////////////////////////////////////////////////

class dtkCreatorPluginWidgetPrivate;

class dtkCreatorPluginWidget : public QWidget
{
    Q_OBJECT

public:
     dtkCreatorPluginWidget(QWidget *parent = 0);
    ~dtkCreatorPluginWidget(void);

    QSize sizeHint(void) const;

public slots:
    void addWidget(QWidget *widget);

private:
    dtkCreatorPluginWidgetPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkCreatorPluginBrowser
// /////////////////////////////////////////////////////////////////

class dtkCreatorPluginBrowserPrivate;

class dtkCreatorPluginBrowser : public dtkSplitter
{
    Q_OBJECT
    
public:
     dtkCreatorPluginBrowser(QWidget *parent = 0);
    ~dtkCreatorPluginBrowser(void);

    QSize sizeHint(void) const;

    dtkCreatorPluginList *list(void);
    dtkCreatorPluginWidget *widget(void);

private:
    dtkCreatorPluginBrowserPrivate *d;
};

#endif
