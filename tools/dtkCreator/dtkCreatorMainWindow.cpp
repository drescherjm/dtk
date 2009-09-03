/* dtkCreatorMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug  3 17:40:34 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep  3 16:26:17 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 269
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCreatorController.h"
#include "dtkCreatorMainWindow.h"
#include "dtkCreatorPluginBrowser.h"
#include "dtkCreatorScriptBrowser.h"
#include "dtkCreatorViewer.h"
#include "dtkCreatorWidgetFactory.h"

#include <dtkCore/dtkLog.h>

#include <dtkScript/dtkScriptInterpreter.h>
#include <dtkScript/dtkScriptInterpreterPool.h>
#include <dtkScript/dtkScriptInterpreterPython.h>
#include <dtkScript/dtkScriptInterpreterTcl.h>

#include <dtkGui/dtkInspector.h>
#include <dtkGui/dtkInterpreter.h>
#include <dtkGui/dtkInterpreterPreferencesWidget.h>
#include <dtkGui/dtkPreferencesWidget.h>
#include <dtkGui/dtkSearchBox.h>
#ifdef Q_WS_MAC
#include <dtkGui/dtkSearchBoxMac.h>
#endif
#include <dtkGui/dtkSpacer.h>
#include <dtkGui/dtkSplitter.h>
#include <dtkGui/dtkTextEditor.h>
#include <dtkGui/dtkTextEditorPreferencesWidget.h>
#include <dtkGui/dtkTextEditorSyntaxHighlighterCpp.h>
#include <dtkGui/dtkTextEditorSyntaxHighlighterPython.h>
#include <dtkGui/dtkTextEditorSyntaxHighlighterTcl.h>

// /////////////////////////////////////////////////////////////////
// log message handler
// /////////////////////////////////////////////////////////////////

QWidget *log_output;

void dtkCreatorRedirectLogHandler(dtkLog::Level level, const QString& msg)
{
    QCoreApplication::postEvent(log_output, new dtkLogEvent(level, msg));
}

// /////////////////////////////////////////////////////////////////
// dtkCreatorMainWindowPrivate
// /////////////////////////////////////////////////////////////////

class dtkCreatorMainWindowPrivate
{
public:
    bool maySave(void);

public:
    QMenu *fileMenu;
    QAction *fileOpenAction;
    QAction *fileSaveAction;
    QAction *fileSaveAsAction;
    QAction *fileQuitAction;
    QAction *preferencesAction;

    QAction *toolTextualEditorAction;
    QAction *toolVisualEditorAction;
    QAction *toolViewerAction;
    QAction *toolInspectorAction;

    QToolBar *toolBar;

    QStackedWidget *stack;

    dtkInspector *inspector;
    dtkPreferencesWidget *preferences;
    dtkCreatorScriptBrowser *script_browser;
    dtkCreatorPluginBrowser *plugin_browser;
    dtkTextEditor *editor;
    dtkTextEditorSyntaxHighlighter *highlighter;
    dtkCreatorViewer *viewer;
    dtkInterpreter *interpreter;

public:
    dtkCreatorMainWindow *q;
};

bool dtkCreatorMainWindowPrivate::maySave(void)
{
    if (editor->isModified()) {
        QMessageBox::StandardButton ret = QMessageBox::warning(q,
            q->tr("dtkCreator"),
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

extern "C" int init_creator(void);               // -- Initialization creator layer python wrapped functions
extern "C" int Creator_Init(Tcl_Interp *interp); // -- Initialization creator layer tcl wrapped functions

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

    d->fileQuitAction = new QAction("Quit", this);
    d->fileQuitAction->setShortcut(Qt::ControlModifier + Qt::Key_Q);
    connect(d->fileQuitAction, SIGNAL(triggered()), this, SLOT(close()));

    d->preferencesAction = new QAction("Preferences", this);
    d->preferencesAction->setShortcut(Qt::ControlModifier + Qt::Key_Comma);
    connect(d->preferencesAction, SIGNAL(triggered()), this, SLOT(showPreferences()));

    d->fileMenu = this->menuBar()->addMenu("File");
    d->fileMenu->addAction(d->fileOpenAction);
    d->fileMenu->addAction(d->fileSaveAction);
    d->fileMenu->addAction(d->fileSaveAsAction);
    d->fileMenu->addAction(d->preferencesAction);

    d->toolTextualEditorAction = new QAction("Textual editor", this);
    d->toolTextualEditorAction->setShortcut(Qt::MetaModifier+Qt::Key_1);
    d->toolTextualEditorAction->setToolTip("Switch to the textual editor (Ctrl+1)");
    d->toolTextualEditorAction->setIcon(QIcon(":icons/widget.tiff"));
    connect(d->toolTextualEditorAction, SIGNAL(triggered()), this, SLOT(switchToTextualEditor()));
    d->toolTextualEditorAction->setEnabled(false);

    d->toolVisualEditorAction = new QAction("Visual editor", this);
    d->toolVisualEditorAction->setShortcut(Qt::MetaModifier+Qt::Key_2);
    d->toolVisualEditorAction->setToolTip("Switch to the visual editor (Ctrl+3)");
    d->toolVisualEditorAction->setIcon(QIcon(":icons/widget.tiff"));
    connect(d->toolVisualEditorAction, SIGNAL(triggered()), this, SLOT(switchToVisualEditor()));
    d->toolVisualEditorAction->setEnabled(true);

    d->toolViewerAction = new QAction("Viewer", this);
    d->toolViewerAction->setShortcut(Qt::MetaModifier+Qt::Key_3);
    d->toolViewerAction->setToolTip("Switch to the viewer (Ctrl+3)");
    d->toolViewerAction->setIcon(QIcon(":icons/widget.tiff"));
    connect(d->toolViewerAction, SIGNAL(triggered()), this, SLOT(switchToViewer()));
    d->toolViewerAction->setEnabled(true);

    d->toolInspectorAction = new QAction("Inspector", this);
    d->toolInspectorAction->setShortcut(Qt::MetaModifier+Qt::Key_I);
    d->toolInspectorAction->setToolTip("Open inspector (Ctrl+I)");
    d->toolInspectorAction->setIcon(QIcon(":icons/inspector.tiff"));
    connect(d->toolInspectorAction, SIGNAL(triggered()), this, SLOT(showInspector()));

    d->toolBar = addToolBar("Editors");
    d->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    d->toolBar->setIconSize(QSize(32, 32));
    d->toolBar->addAction(d->toolTextualEditorAction);
    d->toolBar->addAction(d->toolVisualEditorAction);
    d->toolBar->addAction(d->toolViewerAction);
#ifdef Q_WS_MAC
    dtkSearchBoxAction *dtk_search_box = new dtkSearchBoxAction("Search", d->toolBar);
    d->toolBar->addWidget(new dtkSpacer(d->toolBar));
    d->toolBar->addAction(dtk_search_box);
#else
    dtkSearchBox *dtk_search_box = new dtkSearchBox(d->toolBar);
    d->toolBar->addWidget(new dtkSpacer(d->toolBar));
    d->toolBar->addWidget(dtk_search_box);
    d->toolBar->addWidget(new dtkSpacer(d->toolBar, 20, 0));
#endif
    d->toolBar->addAction(d->toolInspectorAction);

    d->q = this;

    d->stack = new QStackedWidget(this);

    d->editor = new dtkTextEditor(d->stack);
    d->editor->setFrameStyle(QFrame::NoFrame);
    d->editor->setAttribute(Qt::WA_MacShowFocusRect, false);

    d->highlighter = new dtkTextEditorSyntaxHighlighterCpp(d->editor);
    Q_UNUSED(d->highlighter);

    connect(d->editor, SIGNAL(titleChanged(QString)), this, SLOT(onTitleChanged(QString)));
    connect(d->editor, SIGNAL(documentChanged()), this, SLOT(onDocumentChanged()));

    d->stack->addWidget(d->editor);

    d->stack->addWidget(new QWidget(this)); // placeholder for visual editor

    d->viewer = new dtkCreatorViewer(this);
    d->viewer->setAttribute(Qt::WA_MacShowFocusRect, false);

    d->stack->addWidget(d->viewer);

    d->interpreter = new dtkInterpreter(this);
    d->interpreter->setFrameStyle(QFrame::NoFrame);
    d->interpreter->setAttribute(Qt::WA_MacShowFocusRect, false);
    d->interpreter->setMaximumHeight(200);
    log_output = d->interpreter;

    dtkSplitter *inner_splitter = new dtkSplitter(this, true);
    inner_splitter->setOrientation(Qt::Vertical);
    inner_splitter->addWidget(d->stack);
    inner_splitter->addWidget(d->interpreter);

    d->script_browser = new dtkCreatorScriptBrowser(this);
    d->plugin_browser = new dtkCreatorPluginBrowser(this);

    connect(d->script_browser, SIGNAL(scriptClicked(const QString&)), d->editor, SLOT(open(const QString&)));

    dtkSplitter *outer_splitter = new dtkSplitter(this);
    outer_splitter->setOrientation(Qt::Horizontal);
    outer_splitter->addWidget(d->script_browser);
    outer_splitter->addWidget(inner_splitter);
    outer_splitter->addWidget(d->plugin_browser);
    outer_splitter->setStretchFactor(0, 1);
    outer_splitter->setStretchFactor(1, 2);
    outer_splitter->setStretchFactor(2, 1);

    d->preferences = NULL;

    this->setWindowTitle(d->editor->fileName());
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setCentralWidget(outer_splitter);

    this->readSettings();

    dtkCreatorController::instance()->attach(d->plugin_browser);
    dtkCreatorController::instance()->attach(d->script_browser);
    dtkCreatorController::instance()->attach(d->viewer);

    dtkScriptInterpreterPythonModuleManager::instance()->registerInitializer(&init_creator);
    dtkScriptInterpreterPythonModuleManager::instance()->registerCommand(
        "import creator"
    );
    dtkScriptInterpreterPythonModuleManager::instance()->registerCommand(
        "viewer = creator.dtkCreatorController.instance().viewer()"
    );
    dtkScriptInterpreterPythonModuleManager::instance()->registerCommand(
        "holder = creator.dtkCreatorController.instance().scriptBrowser().widget()"
    );
    dtkScriptInterpreterPythonModuleManager::instance()->registerCommand(
        "widgetFactory = creator.dtkCreatorWidgetFactory.instance()"
    );

    dtkScriptInterpreterTclModuleManager::instance()->registerInitializer(&Creator_Init);
    dtkScriptInterpreterTclModuleManager::instance()->registerCommand(
        "set controller [dtkCreatorController_instance]"
    );
    dtkScriptInterpreterTclModuleManager::instance()->registerCommand(
        "set viewer [$controller viewer]"
    );
    dtkScriptInterpreterTclModuleManager::instance()->registerCommand(
        "set holder [[[$controller workspace] scriptBrowser] widget]"
    );
    dtkScriptInterpreterTclModuleManager::instance()->registerCommand(
	"set widgetFactory [dtkCreatorWidgetFactory_instance]"
    );

    d->interpreter->registerInterpreter(new dtkScriptInterpreterPython);
    d->interpreter->registerAsHandler(dtkCreatorRedirectLogHandler);
}

dtkCreatorMainWindow::~dtkCreatorMainWindow(void)
{
    this->writeSettings();

    delete d->interpreter;
    delete d->editor;
    delete d->highlighter;
    delete d;
}

void dtkCreatorMainWindow::readSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("creator");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    move(pos);
    resize(size);
    settings.endGroup();

    d->editor->readSettings();
    d->interpreter->readSettings();
}

void dtkCreatorMainWindow::writeSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("creator");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.endGroup();

    d->editor->writeSettings();
    d->interpreter->writeSettings();
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

void dtkCreatorMainWindow::showInspector(void)
{
    if(!d->inspector) {
        d->inspector = new dtkInspector(this);
        // ...
    }

    d->inspector->show();
}

void dtkCreatorMainWindow::showPreferences(void)
{
    if(!d->preferences) {
        d->preferences = new dtkPreferencesWidget(this);
        d->preferences->addPage("Textual editor", d->editor->preferencesWidget(this));
        d->preferences->addPage("Interpreter", d->interpreter->preferencesWidget(this));
    }

    d->preferences->show();
}

void dtkCreatorMainWindow::switchToTextualEditor(void)
{
    d->stack->setCurrentIndex(0);

    d->toolTextualEditorAction->setEnabled(false);
    d->toolVisualEditorAction->setEnabled(true);
    d->toolViewerAction->setEnabled(true);
}

void dtkCreatorMainWindow::switchToVisualEditor(void)
{
    d->stack->setCurrentIndex(1);

    d->toolTextualEditorAction->setEnabled(true);
    d->toolVisualEditorAction->setEnabled(false);
    d->toolViewerAction->setEnabled(true);
}

void dtkCreatorMainWindow::switchToViewer(void)
{
    d->stack->setCurrentIndex(2);

    d->toolTextualEditorAction->setEnabled(true);
    d->toolVisualEditorAction->setEnabled(true);
    d->toolViewerAction->setEnabled(false);
}

void dtkCreatorMainWindow::closeEvent(QCloseEvent *event)
{
    if (d->maySave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void dtkCreatorMainWindow::onTitleChanged(QString title)
{
    this->setWindowTitle("dtkCreator - " + title);
}

void dtkCreatorMainWindow::onDocumentChanged(void)
{
    if(!this->windowTitle().endsWith("*"))
        this->setWindowTitle("dtkCreator - " + this->windowTitle() + "*");
}
