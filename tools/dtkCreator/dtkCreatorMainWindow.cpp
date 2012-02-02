/* dtkCreatorMainWindow.cpp ---
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug  3 17:40:34 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Feb  2 15:39:44 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 779
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
#include <dtkComposer/dtkComposerStack.h>
#include <dtkComposer/dtkComposerStackView.h>

#include <dtkGui/dtkRecentFilesMenu.h>

#include <QtCore>
#include <QtGui>

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

    d->composer = new dtkComposer;

    d->stack = new dtkComposerStackView;
    d->stack->setStack(d->composer->stack());
    d->stack->setFixedWidth(300);

    d->nodes = new dtkComposerFactoryView;
    d->nodes->setFixedWidth(300);
    d->nodes->setFactory(d->composer->factory());

    d->closing = false;

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

    // connect(d->undo_action, SIGNAL(triggered()), d->composer->stack(), SLOT(undo()));
    // connect(d->redo_action, SIGNAL(triggered()), d->composer->stack(), SLOT(redo()));

    // Layout

    QVBoxLayout *lateral = new QVBoxLayout;
    lateral->setContentsMargins(0, 0, 0, 0);
    lateral->setSpacing(0);
    lateral->addWidget(d->nodes);
    lateral->addWidget(d->stack);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addLayout(lateral);
    layout->addWidget(d->composer);

    QWidget *central = new QWidget(this);
    central->setLayout(layout);

    this->readSettings();

    this->setCentralWidget(central);
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setWindowTitle("Creator");

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
