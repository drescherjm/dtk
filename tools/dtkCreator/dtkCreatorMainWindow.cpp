/* dtkCreatorMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug  3 17:40:34 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Aug  4 11:24:04 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 105
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCreatorMainWindow.h"
#include "dtkCreatorPluginBrowser.h"
#include "dtkCreatorScriptBrowser.h"

#include <dtkScript/dtkScriptInterpreter.h>
#include <dtkScript/dtkScriptInterpreterPool.h>
#include <dtkScript/dtkScriptInterpreterPython.h>
#include <dtkScript/dtkScriptInterpreterTcl.h>

#include <dtkGui/dtkInterpreter.h>
#include <dtkGui/dtkInterpreterPreferencesWidget.h>
#include <dtkGui/dtkSplitter.h>
#include <dtkGui/dtkTextEditor.h>
#include <dtkGui/dtkTextEditorCompleter.h>
#include <dtkGui/dtkTextEditorPreferencesWidget.h>
#include <dtkGui/dtkTextEditorSyntaxHighlighterCpp.h>
#include <dtkGui/dtkTextEditorSyntaxHighlighterPython.h>
#include <dtkGui/dtkTextEditorSyntaxHighlighterTcl.h>

class dtkCreatorMainWindowPrivate
{
public:
    bool maySave(void);

public:
    QMenu *fileMenu;
    QAction *fileOpenAction;
    QAction *fileSaveAction;
    QAction *fileSaveAsAction;
    QAction *preferencesAction;

    QStackedWidget *stack;

    dtkCreatorScriptBrowser *script_browser;
    dtkCreatorPluginBrowser *plugin_browser;
    dtkInterpreter *interpreter;
    dtkTextEditor *editor;
    dtkTextEditorCompleter *completer;
    dtkTextEditorSyntaxHighlighter *highlighter;

public:
    dtkCreatorMainWindow *q;
};

bool dtkCreatorMainWindowPrivate::maySave(void)
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

dtkCreatorMainWindow::dtkCreatorMainWindow(QWidget *parent) : QMainWindow(parent)
{
    d = new dtkCreatorMainWindowPrivate;

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

    d->stack = new QStackedWidget(this);

    d->editor = new dtkTextEditor(d->stack);
    d->editor->readSettings();
    d->editor->setFrameStyle(QFrame::NoFrame);
    d->editor->setAttribute(Qt::WA_MacShowFocusRect, false);

    d->completer = new dtkTextEditorCompleterDocument(d->editor);
    d->editor->setCompleter(d->completer);

    d->highlighter = new dtkTextEditorSyntaxHighlighterCpp(d->editor);
    Q_UNUSED(d->highlighter);

    connect(d->editor, SIGNAL(titleChanged(QString)), this, SLOT(onTitleChanged(QString)));
    connect(d->editor, SIGNAL(documentChanged()), this, SLOT(onDocumentChanged()));

    d->interpreter = new dtkInterpreter(this);
    d->interpreter->readSettings();
    d->interpreter->setFrameStyle(QFrame::NoFrame);
    d->interpreter->setAttribute(Qt::WA_MacShowFocusRect, false);
    d->interpreter->setMaximumHeight(200);
    d->interpreter->registerInterpreter(dtkScriptInterpreterPool::instance()->python());
    d->interpreter->setFocus();

    d->stack->addWidget(d->editor);

    dtkSplitter *inner_splitter = new dtkSplitter(this, true);
    inner_splitter->setOrientation(Qt::Vertical);
    inner_splitter->addWidget(d->stack);
    inner_splitter->addWidget(d->interpreter);

    d->script_browser = new dtkCreatorScriptBrowser(this);
    d->plugin_browser = new dtkCreatorPluginBrowser(this);

    dtkSplitter *outer_splitter = new dtkSplitter(this);
    outer_splitter->setOrientation(Qt::Horizontal);
    outer_splitter->addWidget(d->script_browser);
    outer_splitter->addWidget(inner_splitter);
    outer_splitter->addWidget(d->plugin_browser);

    this->setWindowTitle(d->editor->fileName());
    this->setCentralWidget(outer_splitter);
}

dtkCreatorMainWindow::~dtkCreatorMainWindow(void)
{
    delete d->interpreter;
    delete d->editor;
    delete d->highlighter;
    delete d;
}

bool dtkCreatorMainWindow::fileOpen(void)
{
    if(d->maySave()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath());

        return d->editor->open(fileName);
    }

    return false;
}

bool dtkCreatorMainWindow::fileSave(void)
{
    if(d->editor->fileName() == "untitled")
        return fileSaveAs();
    else
        return d->editor->save();
}

bool dtkCreatorMainWindow::fileSaveAs(void)
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), QDir::homePath());

    if(!fileName.isEmpty())
        return d->editor->save(fileName);

    return false;
}

void dtkCreatorMainWindow::showPreferences(void)
{
    dtkInterpreterPreferencesWidget *widget = d->interpreter->preferencesWidget(this);
    widget->setWindowFlags(Qt::Sheet);
    widget->show();

    // dtkTextEditorPreferencesWidget *widget = d->editor->preferencesWidget(this);
    // widget->setWindowFlags(Qt::Sheet);
    // widget->show();
}

void dtkCreatorMainWindow::closeEvent(QCloseEvent *event)
{
    if (d->maySave()) {
        d->interpreter->writeSettings();
        d->editor->writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void dtkCreatorMainWindow::onTitleChanged(QString title)
{
    this->setWindowTitle(title);
}

void dtkCreatorMainWindow::onDocumentChanged(void)
{
    if(!this->windowTitle().endsWith("*"))
        this->setWindowTitle(this->windowTitle() + "*");
}
