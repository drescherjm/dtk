/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 10 09:19:56 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr 17 13:57:14 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 22
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui>

#include "tstMainWindow.h"

#include <dtkGui/dtkTextEditor.h>
#include <dtkGui/dtkTextEditorCompleter.h>
#include <dtkGui/dtkTextEditorPreferencesWidget.h>
#include <dtkGui/dtkTextEditorSyntaxHighlighterCpp.h>
#include <dtkGui/dtkTextEditorSyntaxHighlighterPython.h>
#include <dtkGui/dtkTextEditorSyntaxHighlighterTcl.h>

class tstMainWindowPrivate
{
public:
    bool maySave(void);

public:
    QMenu *fileMenu;

    QAction *fileOpenAction;
    QAction *fileSaveAction;
    QAction *fileSaveAsAction;

    QAction *preferencesAction;

    dtkTextEditor *editor;
    dtkTextEditorCompleter *completer;
    dtkTextEditorSyntaxHighlighter *highlighter;

public:
    tstMainWindow *q;
};

bool tstMainWindowPrivate::maySave(void)
{
    if (editor->isModified()) {
        QMessageBox::StandardButton ret = QMessageBox::warning(q,
            q->tr("Editor"),
            q->tr("The document has been modified.\n"
                  "Do you want to save your changes?"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel
        );

         if (ret == QMessageBox::Save)
             return q->fileSave();
         else if (ret == QMessageBox::Cancel)
             return false;
     }
     return true;
}

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent)
{
    d = new tstMainWindowPrivate;

    d->editor = new dtkTextEditor(this);
    d->editor->readSettings();

    d->completer = new dtkTextEditorCompleterDocument(d->editor);
    d->editor->setCompleter(d->completer);

    d->highlighter = new dtkTextEditorSyntaxHighlighterCpp(d->editor);
    Q_UNUSED(d->highlighter);

    d->fileOpenAction = new QAction("Open", this);
    d->fileOpenAction->setShortcut(Qt::ControlModifier + Qt::Key_O);
    connect(d->fileOpenAction, SIGNAL(triggered()), this, SLOT(fileOpen()));

    d->fileSaveAction = new QAction("Save", this);
    d->fileSaveAction->setShortcut(Qt::ControlModifier + Qt::Key_S);
    connect(d->fileSaveAction, SIGNAL(triggered()), this, SLOT(fileSave()));

    d->fileSaveAsAction = new QAction("Save as...", this);
    d->fileSaveAsAction->setShortcut(Qt::ControlModifier + Qt::ShiftModifier + Qt::Key_S);
    connect(d->fileSaveAsAction, SIGNAL(triggered()), this, SLOT(fileSaveAs()));

    d->preferencesAction = new QAction("Preferences", this);
    d->preferencesAction->setShortcut(Qt::ControlModifier + Qt::Key_Comma);
    connect(d->preferencesAction, SIGNAL(triggered()), this, SLOT(showPreferences()));

    d->fileMenu = this->menuBar()->addMenu("File");
    d->fileMenu->addAction(d->fileOpenAction);
    d->fileMenu->addAction(d->fileSaveAction);
    d->fileMenu->addAction(d->fileSaveAsAction);
    d->fileMenu->addAction(d->preferencesAction);

    d->q = this;

    connect(d->editor, SIGNAL(titleChanged(QString)), this, SLOT(onTitleChanged(QString)));
    connect(d->editor, SIGNAL(documentChanged()), this, SLOT(onDocumentChanged()));

    this->setWindowTitle(d->editor->fileName());
    this->setCentralWidget(d->editor);
}

tstMainWindow::~tstMainWindow(void)
{
    delete d->editor;
    delete d->highlighter;
    delete d;
}

bool tstMainWindow::fileOpen(void)
{
    if(d->maySave()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath());

        return d->editor->open(fileName);
    }

    return false;
}

bool tstMainWindow::fileSave(void)
{
    if(d->editor->fileName() == "untitled")
        return fileSaveAs();
    else
        return d->editor->save();
}

bool tstMainWindow::fileSaveAs(void)
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), QDir::homePath());

    if(!fileName.isEmpty())
        return d->editor->save(fileName);

    return false;
}

void tstMainWindow::showPreferences(void)
{
    dtkTextEditorPreferencesWidget *widget = d->editor->preferencesWidget(this);
    widget->setWindowFlags(Qt::Sheet);
    widget->show();
}

void tstMainWindow::closeEvent(QCloseEvent *event)
{
    if (d->maySave()) {
        d->editor->writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void tstMainWindow::onTitleChanged(QString title)
{
    this->setWindowTitle(title);
}

void tstMainWindow::onDocumentChanged(void)
{
    if(!this->windowTitle().endsWith("*"))
        this->setWindowTitle(this->windowTitle() + "*");
}
