/* dtkFinder.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Jun 12 15:45:12 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Sat Jun 12 15:47:29 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKFINDER_H
#define DTKFINDER_H

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkFinderSideView
// /////////////////////////////////////////////////////////////////

class dtkFinderSideViewPrivate;

class dtkFinderSideView : public QTreeWidget
{
    Q_OBJECT

public:
     dtkFinderSideView(QWidget *parent = 0);
    ~dtkFinderSideView(void);

    void populate(void);

signals:
    void changed(const QString& path);

public slots:
    void setPath(const QString& path);
    void addBookmark(const QString& path);
    void clearBookmarks(void);

private slots:
    void onItemCicked(QTreeWidgetItem *, int);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    dtkFinderSideViewPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkFinderPathBar
// /////////////////////////////////////////////////////////////////

class dtkFinderPathBarPrivate;

class dtkFinderPathBar : public QFrame
{
    Q_OBJECT

public:
     dtkFinderPathBar(QWidget *parent = 0);
    ~dtkFinderPathBar(void);

signals:
    void changed(const QString& path);

public slots:
    void setPath(const QString &path);

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    dtkFinderPathBarPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkFinderListView
// /////////////////////////////////////////////////////////////////

class dtkFinderListView : public QListView
{
    Q_OBJECT

public:
     dtkFinderListView(QWidget *parent = 0);
    ~dtkFinderListView(void);

signals:
    void changed(const QString& path);
    void bookmarked(const QString& path);

protected slots:
    void updateContextMenu(const QPoint&);
    void onBookmarkContextMenuClicked(void);

protected:
     void keyPressEvent(QKeyEvent *event);
     void startDrag(Qt::DropActions supportedActions);
};

// /////////////////////////////////////////////////////////////////
// dtkFinderTreeView
// /////////////////////////////////////////////////////////////////

class dtkFinderTreeView : public QTreeView
{
    Q_OBJECT

public:
     dtkFinderTreeView(QWidget *parent = 0);
    ~dtkFinderTreeView(void);

    int	sizeHintForColumn(int column) const;

signals:
    void changed(const QString& path);
    void bookmarked(const QString& path);

protected:
     void keyPressEvent(QKeyEvent *event);
     void startDrag(Qt::DropActions supportedActions);
};

// /////////////////////////////////////////////////////////////////
// dtkFinder
// /////////////////////////////////////////////////////////////////

class dtkFinderPrivate;

class dtkFinder : public QWidget
{
    Q_OBJECT

public:
     dtkFinder(QWidget *parent = 0);
    ~dtkFinder(void);

signals:
    void changed(const QString& path);
    void bookmarked(const QString& path);

public slots:
    void setPath(const QString& path);
    void switchToListView(void);
    void switchToTreeView(void);

protected slots:
    void onIndexDoubleClicked(QModelIndex);

private:
    dtkFinderPrivate *d;
};

#endif // DTKFINDER_H
