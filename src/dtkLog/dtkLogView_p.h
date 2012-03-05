/* dtkLogView_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Mar  2 15:30:16 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar  5 13:14:13 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 50
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

private:
    dtkLogModel *model;

private:
    QHash<QString, QStringListModel *> models;
};

// /////////////////////////////////////////////////////////////////
// dtkLogViewPrivate
// /////////////////////////////////////////////////////////////////

class dtkLogViewPrivate
{
public:
    dtkLogViewTree *tree;
    dtkLogViewList *list;
};

#endif
