/* dtkCreatorPluginBrowser.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 10:30:24 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep 10 09:37:36 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 29
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
#include <dtkGui/dtkUi.h>

class dtkAbstractData;
class dtkAbstractProcess;
class dtkAbstractView;

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
    void onPluginClicked(QString type);

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
    void addWidget(QWidget *ui);

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

public slots:
    void onDataSelected(dtkAbstractData *data);
    void onProcessSelected(dtkAbstractProcess *process);
    void onViewSelected(dtkAbstractView *view);

private:
    dtkCreatorPluginBrowserPrivate *d;
};

#endif
