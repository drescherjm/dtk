/* dtkCreatorMainWindow.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug  3 17:40:34 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Mar 20 14:01:41 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 1099
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkCreatorMainWindow.h"
#include "dtkCreatorMainWindow_p.h"

#include <dtkComposer/dtkComposer.h>
#include <dtkComposer/dtkComposerFactoryView.h>
#include <dtkComposer/dtkComposerGraph.h>
#include <dtkComposer/dtkComposerGraphView.h>
#include <dtkComposer/dtkComposerScene.h>
#include <dtkComposer/dtkComposerSceneModel.h>
#include <dtkComposer/dtkComposerSceneNodeEditor.h>
#include <dtkComposer/dtkComposerSceneView.h>
#include <dtkComposer/dtkComposerStack.h>
#include <dtkComposer/dtkComposerStackView.h>
#include <dtkComposer/dtkComposerView.h>

#include <dtkGui/dtkRecentFilesMenu.h>

#include <dtkCore/dtkGlobal.h>

#include <dtkLog/dtkLog.h>
#include <dtkLog/dtkLogView.h>

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkCreatorMainWindowTitleBar
// /////////////////////////////////////////////////////////////////

dtkCreatorMainWindowTitleBar::dtkCreatorMainWindowTitleBar(QWidget *parent)
{
    this->minimize = new QToolButton(this);
    this->minimize->setObjectName("minimize");

    this->zoom = new QToolButton(this);
    this->zoom->setObjectName("zoom");

    this->close = new QToolButton(this);
    this->close->setObjectName("close");

    this->full = new QToolButton(this);
    this->full->setObjectName("full");

    this->label = new QLabel(this);
    this->label->setText("dtkCreator - untitled.txt");
    this->label->setAlignment(Qt::AlignCenter);
    
    QPushButton *compo_button = new QPushButton("Composition", this);
    compo_button->setCheckable(true);
    compo_button->setChecked(true);
    compo_button->setObjectName("compo");

    QPushButton *debug_button = new QPushButton("Debug", this);
    debug_button->setCheckable(true);
    debug_button->setChecked(false);
    debug_button->setObjectName("debug");

    QButtonGroup *button_group = new QButtonGroup(this);
    button_group->addButton(compo_button);
    button_group->addButton(debug_button);
    button_group->setExclusive(true);

    QHBoxLayout *t_layout = new QHBoxLayout;
    t_layout->setContentsMargins(3, 3, 3, 0);
    t_layout->setSpacing(0);
    t_layout->setAlignment(Qt::AlignTop);
    t_layout->addWidget(close);
    t_layout->addWidget(minimize);
    t_layout->addWidget(zoom);
    t_layout->addWidget(label);
    t_layout->addWidget(full);

    QHBoxLayout *b_layout = new QHBoxLayout;
    b_layout->setContentsMargins(0, 0, 10, 20);
    b_layout->setSpacing(12);
    b_layout->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    b_layout->addWidget(compo_button);
    b_layout->addWidget(debug_button);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addLayout(t_layout);
    layout->addLayout(b_layout);

    this->setFixedHeight(70);
    this->setMouseTracking(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    this->maxNormal = false;
    this->mouse_down = false;

    connect(close, SIGNAL(clicked()), parent, SLOT(close()));
    connect(minimize, SIGNAL(clicked()), this, SLOT(showSmall()));
    connect(zoom, SIGNAL(clicked()), this, SLOT(showMaxRestore()));
    connect(full, SIGNAL(clicked()), parent, SLOT(showFullScreen()));

    connect(compo_button, SIGNAL(clicked()), this, SIGNAL(switchToCompo()));
    connect(debug_button, SIGNAL(clicked()), this, SIGNAL(switchToDebug()));
}

void dtkCreatorMainWindowTitleBar::setTitle(const QString& title)
{
    this->label->setText(title);
}

void dtkCreatorMainWindowTitleBar::showSmall(void)
{
    this->window()->showMinimized();
}

void dtkCreatorMainWindowTitleBar::showMaxRestore(void)
{
    if (maxNormal) {
        this->window()->showNormal();
        maxNormal = !maxNormal;
    } else {
        this->window()->showMaximized();
        maxNormal = !maxNormal;
    }
}

void dtkCreatorMainWindowTitleBar::mousePressEvent(QMouseEvent *event)
{
    startPos = event->globalPos();
    clickPos = mapTo(this->window(), event->pos());

    mouse_down = event->button() == Qt::LeftButton;
}

void dtkCreatorMainWindowTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    this->setCursor(Qt::ArrowCursor);

    if (maxNormal)
        return;

    if(mouse_down)
        this->window()->move(event->globalPos() - clickPos);
}

void dtkCreatorMainWindowTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    mouse_down = false;
}

// /////////////////////////////////////////////////////////////////
// dtkCreatorMainWindowPrivate
// /////////////////////////////////////////////////////////////////

bool dtkCreatorMainWindowPrivate::maySave(void)
{
    if(this->closing)
        return true;

    if (q->isWindowModified()) {
        QMessageBox::StandardButton ret = QMessageBox::warning(0,
            q->tr("Creator"),
            q->tr("The composition has been modified.\n Do you want to save your changes?"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
            QMessageBox::Save);

        if (ret == QMessageBox::Save)
            return q->compositionSave();
        else
            if(ret == QMessageBox::Cancel)
                return false;
    }

    return true;
}

void dtkCreatorMainWindowPrivate::setCurrentFile(const QString &file)
{
     this->current_composition = file;

     q->setWindowModified(false);

     QString shownName = this->current_composition;
     if (shownName.isEmpty())
         shownName = "untitled.dtk";

     q->setWindowFilePath(shownName);
}

void dtkCreatorMainWindowPrivate::setModified(bool modified)
{
    q->setWindowModified(modified);
}

// /////////////////////////////////////////////////////////////////
// dtkCreatorMainWindow
// /////////////////////////////////////////////////////////////////

dtkCreatorMainWindow::dtkCreatorMainWindow(QWidget *parent) : QMainWindow(parent), d(new dtkCreatorMainWindowPrivate)
{
    d->q = this;

    // Fonts

    // int id;
    // id = QFontDatabase::addApplicationFont(":dtkCreator/fonts/maven_medium.otf");
    // id = QFontDatabase::addApplicationFont(":dtkCreator/fonts/maven_regular.otf");
    // qApp->setFont(QFont("Maven Pro"));

    // Elements

    d->composer = new dtkComposer;

    d->editor = new dtkComposerSceneNodeEditor(this);
    d->editor->setScene(d->composer->scene());
    d->editor->setStack(d->composer->stack());
    d->editor->setGraph(d->composer->graph());
    d->editor->setFixedWidth(250);

    d->model = new dtkComposerSceneModel(this);
    d->model->setScene(d->composer->scene());

    d->scene = new dtkComposerSceneView(this);
    d->scene->setScene(d->composer->scene());
    d->scene->setModel(d->model);
    d->scene->setFixedWidth(250);

    d->stack = new dtkComposerStackView(this);
    d->stack->setStack(d->composer->stack());
    d->stack->setFixedWidth(250);

    d->nodes = new dtkComposerFactoryView(this);
    d->nodes->setFixedWidth(250);
    d->nodes->setFactory(d->composer->factory());

    d->graph = new dtkComposerGraphView(this);
    d->graph->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);
    d->graph->setScene(d->composer->graph());
    d->graph->setVisible(false);

    d->title_bar = new dtkCreatorMainWindowTitleBar(this);

    d->log_view = new dtkLogView(this);
    d->log_view->setVisible(false);

    d->closing = false;
    d->full = false;

    d->mouse_down = false;

    d->canvas = new QFrame(this);
    d->canvas->setFixedHeight(15);
    d->canvas->setStyleSheet("background-image: url(:dtkCreator/pixmaps/canvas.png); background-repeat: repeat-x; height: 15px;");

    // Menus & Actions

    QMenuBar *menu_bar = new QMenuBar(this);

    d->composition_open_action = new QAction("Open", this);
    d->composition_open_action->setShortcut(QKeySequence::Open);

    d->composition_save_action = new QAction("Save", this);
    d->composition_save_action->setShortcut(QKeySequence::Save);

    d->composition_saveas_action = new QAction("Save As...", this);
    d->composition_saveas_action->setShortcut(QKeySequence::SaveAs);

    d->composition_insert_action = new QAction("Insert", this);
    d->composition_insert_action->setShortcut(Qt::ControlModifier + Qt::ShiftModifier + Qt::Key_I);

    d->composition_quit_action = new QAction("Quit", this);
    d->composition_quit_action->setShortcut(QKeySequence::Quit);

    d->recent_compositions_menu = new dtkRecentFilesMenu("Open recent...", this);

    d->composition_menu = menu_bar->addMenu("Composition");
    d->composition_menu->addAction(d->composition_open_action);
    d->composition_menu->addMenu(d->recent_compositions_menu);
    d->composition_menu->addAction(d->composition_save_action);
    d->composition_menu->addAction(d->composition_saveas_action);
    d->composition_menu->addSeparator();
    d->composition_menu->addAction(d->composition_insert_action);
    d->composition_menu->addSeparator();
    d->composition_menu->addAction(d->composition_quit_action);

    d->undo_action = d->composer->stack()->createUndoAction(this);
    d->undo_action->setShortcut(QKeySequence::Undo);

    d->redo_action = d->composer->stack()->createRedoAction(this);
    d->redo_action->setShortcut(QKeySequence::Redo);

    d->edit_menu = menu_bar->addMenu("Edit");
    d->edit_menu->addAction(d->undo_action);
    d->edit_menu->addAction(d->redo_action);

    // Connections

    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(close()));

    connect(d->composer, SIGNAL(modified(bool)), d, SLOT(setModified(bool)));

    connect(d->composition_open_action, SIGNAL(triggered()), this, SLOT(compositionOpen()));
    connect(d->composition_save_action, SIGNAL(triggered()), this, SLOT(compositionSave()));
    connect(d->composition_saveas_action, SIGNAL(triggered()), this, SLOT(compositionSaveAs()));
    connect(d->composition_insert_action, SIGNAL(triggered()), this, SLOT(compositionInsert()));
    connect(d->composition_quit_action, SIGNAL(triggered()), qApp, SLOT(quit()));

    connect(d->recent_compositions_menu, SIGNAL(recentFileTriggered(const QString&)), this, SLOT(compositionOpen(const QString&)));

    connect(d->title_bar, SIGNAL(switchToCompo()), this, SLOT(switchToCompo()));
    connect(d->title_bar, SIGNAL(switchToDebug()), this, SLOT(switchToDebug()));

    // Layout

    QVBoxLayout *l_lateral = new QVBoxLayout;
    l_lateral->setContentsMargins(0, 0, 0, 0);
    l_lateral->setSpacing(0);
    l_lateral->addWidget(d->nodes);

    QVBoxLayout *r_lateral = new QVBoxLayout;
    r_lateral->setContentsMargins(0, 0, 0, 0);
    r_lateral->setSpacing(0);
    r_lateral->addWidget(d->scene);
    r_lateral->addWidget(d->editor);
    r_lateral->addWidget(d->stack);

    QHBoxLayout *b_layout = new QHBoxLayout;
    b_layout->setContentsMargins(0, 0, 0, 0);
    b_layout->setSpacing(0);
    b_layout->addWidget(d->log_view);

    QHBoxLayout *i_layout = new QHBoxLayout;
    i_layout->setContentsMargins(0, 0, 0, 0);
    i_layout->setSpacing(0);
    i_layout->addLayout(l_lateral);
    i_layout->addWidget(d->graph);
    i_layout->addWidget(d->composer);
    i_layout->addLayout(r_lateral);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(0);
    layout->addWidget(d->title_bar);
    layout->addWidget(d->canvas);
    layout->addLayout(i_layout);
    layout->addLayout(b_layout);

    QWidget *central = new QWidget(this);
    central->setLayout(layout);

    this->readSettings();

    this->setCentralWidget(central);
    this->setMouseTracking(true);
    this->setStyleSheet(dtkReadFile(":dtkCreator/dtkCreator.qss"));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setUnifiedTitleAndToolBarOnMac(true);

#if defined(Q_WS_MAC) && (MAC_OS_X_VERSION_MAX_ALLOWED > MAC_OS_X_VERSION_10_6)
    d->enableFullScreenSupport();
#endif

    d->setCurrentFile("");
}

dtkCreatorMainWindow::~dtkCreatorMainWindow(void)
{
    delete d;
}

void dtkCreatorMainWindow::readSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("creator");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(600, 400)).toSize();
    move(pos);
    resize(size);
    settings.endGroup();
}

void dtkCreatorMainWindow::writeSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("creator");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.endGroup();
}

bool dtkCreatorMainWindow::compositionOpen(void)
{
    if(!d->maySave())
        return true;

    QFileDialog *dialog = new QFileDialog(this, tr("Open composition"), QDir::homePath(), QString("dtk composition (*.dtk)"));
    dialog->setStyleSheet("background-color: none ; color: none;");
    dialog->setAcceptMode(QFileDialog::AcceptOpen);
    dialog->setFileMode(QFileDialog::AnyFile);
    dialog->open(this, SLOT(compositionOpen(const QString&)));

    return true;
}

bool dtkCreatorMainWindow::compositionOpen(const QString& file)
{
    bool status = d->composer->open(file);

    if(status) {
        d->recent_compositions_menu->addRecentFile(file);
        d->setCurrentFile(file);
    }

    return status;
}

bool dtkCreatorMainWindow::compositionSave(void)
{
    bool status;

    if(d->current_composition.isEmpty() || d->current_composition == "untitled.dtk")
        status = this->compositionSaveAs();
    else
        status = d->composer->save();

    if(status)
        this->setWindowModified(false);

    return status;
}

bool dtkCreatorMainWindow::compositionSaveAs(void)
{
    bool status = false;

    QStringList nameFilters;
    nameFilters <<  "Ascii composition (*.dtk)";
    nameFilters << "Binary composition (*.dtk)";

    QFileDialog dialog(this, "Save composition as ...", QDir::homePath(), QString("dtk composition (*.dtk)"));
    dialog.setStyleSheet("background-color: none ; color: none;");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setConfirmOverwrite(true);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilters(nameFilters);
    dialog.setDefaultSuffix("dtk");

    if(dialog.exec()) {

        if(dialog.selectedNameFilter() == nameFilters.at(0))
            status = this->compositionSaveAs(dialog.selectedFiles().first(), dtkComposerWriter::Ascii);
        else
            status = this->compositionSaveAs(dialog.selectedFiles().first(), dtkComposerWriter::Binary);
    }

    return status;
}

bool dtkCreatorMainWindow::compositionSaveAs(const QString& file, dtkComposerWriter::Type type)
{
    bool status = false;

    if(file.isEmpty())
        return status;

    status = d->composer->save(file, type);

    if(status) {
        d->setCurrentFile(file);
        this->setWindowModified(false);
    }

    return status;
}

bool dtkCreatorMainWindow::compositionInsert(void)
{
    QFileDialog *dialog = new QFileDialog(this, tr("Insert composition"), QDir::homePath(), QString("dtk composition (*.dtk)"));
    dialog->setStyleSheet("background-color: none ; color: none;");
    dialog->setAcceptMode(QFileDialog::AcceptOpen);
    dialog->setFileMode(QFileDialog::AnyFile);
    dialog->open(this, SLOT(compositionInsert(const QString&)));

    return true;
}

bool dtkCreatorMainWindow::compositionInsert(const QString& file)
{
    bool status = d->composer->insert(file);

    if(status)
        this->setWindowModified(true);

    return status;
}

void dtkCreatorMainWindow::setWindowModified(bool modified)
{
    QMainWindow::setWindowModified(modified);

    d->title_bar->setTitle(this->windowTitle());
}

void dtkCreatorMainWindow::setWindowFilePath(const QString& path)
{
    QMainWindow::setWindowFilePath(path);

    d->title_bar->setTitle(this->windowTitle());
}

void dtkCreatorMainWindow::showFullScreen(void)
{
#if defined(Q_WS_MAC) && (MAC_OS_X_VERSION_MAX_ALLOWED > MAC_OS_X_VERSION_10_6)
    d->showFullScreen();
#else
    d->full = !d->full;

    if(d->full)
        QMainWindow::showFullScreen();
    else
        QMainWindow::showNormal();
#endif
}

void dtkCreatorMainWindow::switchToCompo(void)
{
    d->nodes->setVisible(true);
    d->scene->setVisible(true);
    d->editor->setVisible(true);
    d->stack->setVisible(true);

    d->graph->setVisible(false);
    d->log_view->setVisible(false);
}

void dtkCreatorMainWindow::switchToDebug(void)
{
    d->nodes->setVisible(false);
    d->scene->setVisible(false);
    d->editor->setVisible(false);
    d->stack->setVisible(false);

    d->graph->setVisible(true);
    d->log_view->setVisible(true);
}

void dtkCreatorMainWindow::closeEvent(QCloseEvent *event)
{
    if (d->maySave()) {
         writeSettings();
         d->closing = true;
         event->accept();
     } else {
         event->ignore();
     }
}

void dtkCreatorMainWindow::mousePressEvent(QMouseEvent *e)
{
    d->old_pos = e->pos();
    d->mouse_down = e->button() == Qt::LeftButton;
}

void dtkCreatorMainWindow::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();

    if (d->mouse_down) {
        int dx = x - d->old_pos.x();
        int dy = y - d->old_pos.y();

        QRect g = geometry();

        if (d->top)
            g.setTop(g.top() + dy);
        if (d->left)
            g.setLeft(g.left() + dx);
        if (d->right)
            g.setRight(g.right() + dx);
        if (d->bottom)
            g.setBottom(g.bottom() + dy);

        setGeometry(g);

        d->old_pos = QPoint(!d->left ? e->x() : d->old_pos.x(), !d->top ? e->y() : d->old_pos.y());

    } else {

        QRect r = rect();

        d->left = qAbs(x - r.left()) <= 10;
        d->right = qAbs(x - r.right()) <= 10;
        d->bottom = qAbs(y - r.bottom()) <= 10;
        d->top = qAbs(y - r.top()) <= 10;

        bool hor = d->left | d->right;
        bool ver = d->bottom | d->top;

        if (hor && d->bottom) {
            if (d->left)
                setCursor(Qt::SizeBDiagCursor);
            else
                setCursor(Qt::SizeFDiagCursor);
        } else if (hor && d->top) {
            if (d->left)
                setCursor(Qt::SizeFDiagCursor);
            else
                setCursor(Qt::SizeBDiagCursor);
        } else if (hor) {
            setCursor(Qt::SizeHorCursor);
        } else if (ver) {
            setCursor(Qt::SizeVerCursor);
        } else {
            setCursor(Qt::ArrowCursor);
        }
    }
}

void dtkCreatorMainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    d->mouse_down = false;
}

void dtkCreatorMainWindow::resizeEvent(QResizeEvent *event)
{
    QImage image(this->size(), QImage::Format_Mono); image.fill(0);

    if(!this->isFullScreen() && !this->isMaximized())
    {
        image.setPixel(0, 0, 1); image.setPixel(1, 0, 1); image.setPixel(2, 0, 1); image.setPixel(3, 0, 1);
        image.setPixel(0, 1, 1); image.setPixel(1, 1, 1);
        image.setPixel(0, 2, 1);
        image.setPixel(0, 3, 1);

        image.setPixel(width() - 4, 0, 1); image.setPixel(width() - 3, 0, 1); image.setPixel(width() - 2, 0, 1); image.setPixel(width() - 1, 0, 1);
        image.setPixel(width() - 2, 1, 1); image.setPixel(width() - 1, 1, 1);
        image.setPixel(width() - 1, 2, 1);
        image.setPixel(width() - 1, 3, 1);

        image.setPixel(0, height() - 4, 1);
        image.setPixel(0, height() - 3, 1);
        image.setPixel(0, height() - 2, 1); image.setPixel(1, height() - 2, 1);
        image.setPixel(0, height() - 1, 1); image.setPixel(1, height() - 1, 1); image.setPixel(2, height() - 1, 1); image.setPixel(3, height() - 1, 1);

        image.setPixel(width() - 1, height() - 4, 1);
        image.setPixel(width() - 1, height() - 3, 1);
        image.setPixel(width() - 2, height() - 2, 1); image.setPixel(width() - 1, height() - 2, 1);
        image.setPixel(width() - 4, height() - 1, 1); image.setPixel(width() - 3, height() - 1, 1); image.setPixel(width() - 2, height() - 1, 1); image.setPixel(width() - 1, height() - 1, 1);
    }

#if defined(Q_WS_MAC)
    image.invertPixels();
#endif

    this->setMask(QPixmap::fromImage(image));
}
