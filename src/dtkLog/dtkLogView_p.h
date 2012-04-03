/* dtkLogView_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Mar  2 15:30:16 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar  6 10:04:35 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 66
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKLOGVIEW_P_H
#define DTKLOGVIEW_P_H

#include "dtkLogger.h"

#include <QtGui>

class dtkLogModel;

// /////////////////////////////////////////////////////////////////
// dtkLogViewBar
// /////////////////////////////////////////////////////////////////

class dtkLogViewBar : public QFrame
{
    Q_OBJECT

public:
     dtkLogViewBar(QWidget *parent = 0);
    ~dtkLogViewBar(void);

signals:
    void displayTrace(bool);
    void displayDebug(bool);
    void displayInfo(bool);
    void displayWarn(bool);
    void displayError(bool);
    void displayFatal(bool);
};

// /////////////////////////////////////////////////////////////////
// dtkLogViewTree
// /////////////////////////////////////////////////////////////////

class dtkLogViewTree : public QTreeWidget
{
    Q_OBJECT

public:
     dtkLogViewTree(QWidget *parent = 0);
    ~dtkLogViewTree(void);

signals:
    void runtimeClicked(void);
    void fileClicked(const QString& path);

protected slots:
    void onItemClicked(QTreeWidgetItem *, int);

private:
    QTreeWidgetItem *runtime;
    QTreeWidgetItem *file;
};

// /////////////////////////////////////////////////////////////////
// dtkLogViewList
// /////////////////////////////////////////////////////////////////

class dtkLogViewList : public QListView
{
    Q_OBJECT

public:
     dtkLogViewList(QWidget *parent = 0);
    ~dtkLogViewList(void);

public slots:
    void setRuntime(void);
    void setFile(const QString& path);

public:
    void setFilter(const QRegExp& expression);

private:
    dtkLogModel *model;

private:
    QHash<QString, QStringListModel *> models;

private:
    QSortFilterProxyModel *proxy;
};

// /////////////////////////////////////////////////////////////////
// dtkLogViewPrivate
// /////////////////////////////////////////////////////////////////

class dtkLogViewPrivate
{
public:
    QRegExp expression(void);

public:
    dtkLogViewBar  *bar;
    dtkLogViewTree *tree;
    dtkLogViewList *list;

public:
    QStringList exclude;
};

#endif
