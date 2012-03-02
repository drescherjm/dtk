/* dtkLogView_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Mar  2 15:30:16 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Mar  2 19:03:52 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 35
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

// /////////////////////////////////////////////////////////////////
// dtkLogViewTree
// /////////////////////////////////////////////////////////////////

class dtkLogViewTree : public QTreeWidget
{
    Q_OBJECT

public:
     dtkLogViewTree(QWidget *parent = 0);
    ~dtkLogViewTree(void);
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

public:
    void setRuntime(void);

public:
    void append(const QString& message);

private:
    QStringList list;
    QStringListModel model;
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
