/* dtkCreatorMainWindow_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  1 12:37:28 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 19 23:03:05 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 66
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
    dtkCreatorMainWindowTitleBar(QWidget *parent)
    {
        this->setMouseTracking(true);

        minimize = new QToolButton(this);
        zoom = new QToolButton(this);
        close = new QToolButton(this);
        full = new QToolButton(this);

        this->label = new QLabel(this);
        this->label->setText("dtkCreator - untitled.txt");
        this->label->setAlignment(Qt::AlignCenter);

        QHBoxLayout *hbox = new QHBoxLayout(this);
        hbox->setContentsMargins(3, 3, 3, 3);
        hbox->setSpacing(0);
        hbox->setAlignment(Qt::AlignTop);
        hbox->addWidget(close);
        hbox->addWidget(minimize);
        hbox->addWidget(zoom);
        hbox->addWidget(label);
        hbox->addWidget(full);

        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        this->setFixedHeight(70);

        maxNormal = false;
        mouse_down = false;

        connect(close, SIGNAL(clicked()), parent, SLOT(close()));
        connect(minimize, SIGNAL(clicked()), this, SLOT(showSmall()));
        connect(zoom, SIGNAL(clicked()), this, SLOT(showMaxRestore()));
        connect(full, SIGNAL(clicked()), parent, SLOT(showFullScreen()));

        this->setStyleSheet(
                            "QFrame {"
                            "background: url(:dtkCreator/pixmaps/leather.png);"
                            "background-repeat: repeat-x;"
                            "border:none;"
                            "border-bottom: 1px solid #555555;"
                            "color: #777777;"
                            "font-size: 12px;"
                            "height: 70px;"
                            "}"
                            "QFrame:active {color: #444444;}"
                            "QLabel { background: transparent; border: none; }");

        close->setStyleSheet("QToolButton { background: transparent; background-repeat: no-repeat; border: none; border-bottom: none; width: 16px; height: 16px; }"
                             "QToolButton { background-image: url(:dtkCreator/pixmaps/inactive.png); }"
                             "QToolButton:active { background-image: url(:dtkCreator/pixmaps/close-active.png); }"
                             "QToolButton:active:hover { background-image: url(:dtkCreator/pixmaps/close-rollover.png); }"
                             "QToolButton:active:pressed { background-image: url(:dtkCreator/pixmaps/close-pressed.png); }");

        zoom->setStyleSheet("QToolButton { background: transparent; background-repeat: no-repeat; border: none; border-bottom: none; width: 16px; height: 16px; }"
                            "QToolButton { background-image: url(:dtkCreator/pixmaps/inactive.png); }"
                            "QToolButton:active { background-image: url(:dtkCreator/pixmaps/zoom-active.png); }"
                            "QToolButton:active:hover { background-image: url(:dtkCreator/pixmaps/zoom-rollover.png); }"
                            "QToolButton:active:pressed { background-image: url(:dtkCreator/pixmaps/zoom-pressed.png); }");

        minimize->setStyleSheet("QToolButton { background: transparent; background-repeat: no-repeat; border: none; border-bottom: none; width: 16px; height: 16px; }"
                                "QToolButton { background-image: url(:dtkCreator/pixmaps/inactive.png); }"
                                "QToolButton:active { background-image: url(:dtkCreator/pixmaps/minimize-active.png); }"
                                "QToolButton:active:hover { background-image: url(:dtkCreator/pixmaps/minimize-rollover.png); }"
                                "QToolButton:active:pressed { background-image: url(:dtkCreator/pixmaps/minimize-pressed.png); }");
        
        full->setStyleSheet("QToolButton { background: transparent; background-repeat: no-repeat; border: none; border-bottom: none; width: 16px; height: 16px; }"
                            "QToolButton { background-image: url(:dtkCreator/pixmaps/fullscreen-active.png); }"
                            "QToolButton:active { background-image: url(:dtkCreator/pixmaps/fullscreen-active.png); }"
                            "QToolButton:active:hover { background-image: url(:dtkCreator/pixmaps/fullscreen-rollover.png); }"
                            "QToolButton:active:pressed { background-image: url(:dtkCreator/pixmaps/fullscreen-pressed.png); }");
    }

public slots:

    void setTitle(const QString& title)
    {
        this->label->setText(title);
    }

    void showSmall()
    {
        this->window()->showMinimized();
    }

    void showMaxRestore()
    {
        if (maxNormal) {
            this->window()->showNormal();
            maxNormal = !maxNormal;
        } else {
            this->window()->showMaximized();
            maxNormal = !maxNormal;
        }
    }

public:
    QSize sizeHint(void) const {
        return QSize(640, 480);
    }

protected:
    void mousePressEvent(QMouseEvent *e)
    {
        startPos = e->globalPos();
        clickPos = mapTo(this->window(), e->pos());

        mouse_down = e->button() == Qt::LeftButton;
    }

    void mouseMoveEvent(QMouseEvent *e)
    {
        this->setCursor(Qt::ArrowCursor);

        if (maxNormal)
            return;

        if(mouse_down)
            this->window()->move(e->globalPos() - clickPos);
    }

    void mouseReleaseEvent(QMouseEvent *e)
    {
        mouse_down = false;
    }

public:
    QLabel *label;

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
