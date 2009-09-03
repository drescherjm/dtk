/* dtkCreatorScriptBrowser.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 10:06:37 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep  3 15:50:20 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 28
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

class dtkCreatorScriptList : public QWidget
{
    Q_OBJECT

public:
     dtkCreatorScriptList(QWidget *parent = 0);
    ~dtkCreatorScriptList(void);

signals:
    void scriptClicked(const QString&);

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

    QSize sizeHint(void) const;

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

signals:
    void scriptClicked(const QString&);

private:
    dtkCreatorScriptBrowserPrivate *d;
};

#endif
