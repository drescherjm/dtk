/* dtkCreatorScriptBrowser.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 10:06:37 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Aug  4 11:26:26 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 15
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
    void preloadScript(const QModelIndex& index);
    void loadScript(const QModelIndex& index);

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
