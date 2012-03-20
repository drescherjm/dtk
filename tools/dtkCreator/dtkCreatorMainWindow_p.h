/* dtkCreatorMainWindow_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  1 12:37:28 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar 20 09:49:11 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 88
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCREATORMAINWINDOW_P_H
#define DTKCREATORMAINWINDOW_P_H

#include <QtCore>
#include <QtGui>

class dtkComposer;
class dtkComposerFactoryView;
class dtkComposerGraphView;
class dtkComposerSceneModel;
class dtkComposerSceneNodeEditor;
class dtkComposerSceneView;
class dtkComposerStackView;

class dtkRecentFilesMenu;

class dtkCreatorMainWindow;

// /////////////////////////////////////////////////////////////////
// dtkCreatorMainWindowTitleBar
// /////////////////////////////////////////////////////////////////

class dtkCreatorMainWindowTitleBar : public QFrame
{
    Q_OBJECT

public:
    dtkCreatorMainWindowTitleBar(QWidget *parent = 0);

public slots:
    void setTitle(const QString& title);
    void showSmall(void);
    void showMaxRestore(void);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QToolButton *minimize;
    QToolButton *zoom;
    QToolButton *close;
    QToolButton *full;
    QPixmap restorePix, maxPix;
    bool maxNormal;
    bool mouse_down;
    QPoint startPos;
    QPoint clickPos;
    QLabel *label;
};

// /////////////////////////////////////////////////////////////////
// dtkCreatorMainWindowPrivate
// /////////////////////////////////////////////////////////////////

class dtkCreatorMainWindowPrivate : public QObject
{
    Q_OBJECT

public:
    bool maySave(void);

public:
    void setCurrentFile(const QString& file);

#if defined(Q_WS_MAC) && (MAC_OS_X_VERSION_MAX_ALLOWED > MAC_OS_X_VERSION_10_6)
    void enableFullScreenSupport(void);
    void showFullScreen(void);
#endif

public slots:
    void setModified(bool modified);

public:
    dtkComposer *composer;
    dtkComposerFactoryView *nodes;
    dtkComposerGraphView *graph;
    dtkComposerSceneModel *model;
    dtkComposerSceneNodeEditor *editor;
    dtkComposerSceneView *scene;
    dtkComposerStackView *stack;

public:
    QMenu *composition_menu;
    QAction *composition_open_action;
    QAction *composition_save_action;
    QAction *composition_saveas_action;
    QAction *composition_insert_action;
    QAction *composition_quit_action;

    QMenu *view_menu;
    QAction *view_graph_action;

    QMenu *edit_menu;
    QAction *undo_action;
    QAction *redo_action;

    dtkRecentFilesMenu *recent_compositions_menu;

public:
    dtkCreatorMainWindowTitleBar *title_bar;

public:
    QFrame *canvas;

public:
    bool closing;

public:
    QString current_composition;

public:
    QPoint old_pos;

public:
    bool mouse_down;

public:
    bool left;
    bool right;
    bool bottom;
    bool top;

public:
    dtkCreatorMainWindow *q;
};

#endif
