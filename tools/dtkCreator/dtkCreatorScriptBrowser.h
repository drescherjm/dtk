/* dtkCreatorScriptBrowser.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 10:06:37 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Aug  5 09:31:47 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCREATORSCRIPTBROWSER_H
#define DTKCREATORSCRIPTBROWSER_H

#include <QtCore>
#include <QtGui>

#include <dtkGui/dtkSplitter.h>

// /////////////////////////////////////////////////////////////////
// dtkCreatorScriptList
// /////////////////////////////////////////////////////////////////

class dtkCreatorScriptListPrivate;

class dtkCreatorScriptList : public dtkSplitter
{
    Q_OBJECT

public:
     dtkCreatorScriptList(QWidget *parent = 0);
    ~dtkCreatorScriptList(void);

signals:
    void loaded(const QString&);

public slots:
    void preloadScript(const QString& fileName);
    void loadScript(const QString& fileName);

private slots:
    void onModelIndexClicked(const QModelIndex& index);
    void onModelIndexDoubleClicked(const QModelIndex& index);

private:
    dtkCreatorScriptListPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkCreatorScriptWidget
// /////////////////////////////////////////////////////////////////

class dtkCreatorScriptWidgetPrivate;

class dtkCreatorScriptWidget : public QStackedWidget
{
    Q_OBJECT

public:
     dtkCreatorScriptWidget(QWidget *parent = 0);
    ~dtkCreatorScriptWidget(void);

public slots:
    void addWidget(QWidget *widget);

private:
    dtkCreatorScriptWidgetPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkCreatorScriptBrowser
// /////////////////////////////////////////////////////////////////

class dtkCreatorScriptBrowserPrivate;

class dtkCreatorScriptBrowser : public dtkSplitter
{
    Q_OBJECT
    
public:
     dtkCreatorScriptBrowser(QWidget *parent = 0);
    ~dtkCreatorScriptBrowser(void);

    QSize sizeHint(void) const;

    dtkCreatorScriptList *list(void);
    dtkCreatorScriptWidget *widget(void);

private:
    dtkCreatorScriptBrowserPrivate *d;
};

#endif
