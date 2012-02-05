/* dtkCreatorMainWindow_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  1 12:37:28 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb  5 15:45:22 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 29
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
class dtkComposerSceneModel;
class dtkComposerSceneView;
class dtkComposerStackView;

class dtkRecentFilesMenu;

class dtkCreatorMainWindow;

class dtkCreatorMainWindowPrivate : public QObject
{
    Q_OBJECT

public:
    bool maySave(void);

public:
    void setCurrentFile(const QString& file);

#if defined(Q_WS_MAC) && (MAC_OS_X_VERSION_MAX_ALLOWED > MAC_OS_X_VERSION_10_6)
    void enableFullScreenSupport(void);
#endif

public slots:
    void setModified(bool modified);

public:
    dtkComposer *composer;
    dtkComposerFactoryView *nodes;
    dtkComposerSceneModel *model;
    dtkComposerSceneView *scene;
    dtkComposerStackView *stack;

public:
    QMenu *composition_menu;
    QAction *composition_open_action;
    QAction *composition_save_action;
    QAction *composition_saveas_action;
    QAction *composition_insert_action;
    QAction *composition_quit_action;

    QMenu *edit_menu;
    QAction *undo_action;
    QAction *redo_action;

    dtkRecentFilesMenu *recent_compositions_menu;

public:
    bool closing;

public:
    QString current_composition;

public:
    dtkCreatorMainWindow *q;
};

#endif
