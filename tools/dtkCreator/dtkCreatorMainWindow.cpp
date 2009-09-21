/* dtkCreatorMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug  3 17:40:34 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep 21 13:53:11 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 433
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

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkLog.h>

#include <dtkScript/dtkScriptInterpreter.h>
#include <dtkScript/dtkScriptInterpreterPool.h>
#include <dtkScript/dtkScriptInterpreterPython.h>
#include <dtkScript/dtkScriptInterpreterTcl.h>

#include <dtkGui/dtkInspector.h>
#include <dtkGui/dtkInspectorScene.h>
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

#include <dtkComposer/dtkComposer.h>

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

    QAction *toolEditorAction;
    QAction *toolComposerAction;
    QAction *toolViewerAction;
    QAction *toolRunAction;
    QAction *toolStopAction;
    QAction *toolInspectorAction;

    QToolBar *toolBar;

    QStackedWidget *stack;

    dtkInspector *inspector;
    dtkPreferencesWidget *preferences;
    dtkCreatorScriptBrowser *script_browser;
    dtkCreatorPluginBrowser *plugin_browser;
    dtkTextEditor *editor;
    dtkTextEditorSyntaxHighlighter *highlighter;
    dtkComposer *composer;
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

extern "C" int init_core(void);                  // -- Initialization core layer python wrapped functions
extern "C" int Core_Init(Tcl_Interp *interp);    // -- Initialization core layer tcl    wrapped functions

extern "C" int init_creator(void);               // -- Initialization creator layer python wrapped functions
extern "C" int Creator_Init(Tcl_Interp *interp); // -- Initialization creator layer tcl    wrapped functions

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

    d->toolEditorAction = new QAction("Editor", this);
#if defined(Q_WS_MAC)
    d->toolEditorAction->setShortcut(Qt::MetaModifier+Qt::Key_1);
#else
    d->toolEditorAction->setShortcut(Qt::ControlModifier+Qt::Key_1);
#endif
    d->toolEditorAction->setToolTip("Switch to the textual editor (Ctrl+1)");
    d->toolEditorAction->setIcon(QIcon(":icons/widget.tiff"));
    connect(d->toolEditorAction, SIGNAL(triggered()), this, SLOT(switchToEditor()));
    d->toolEditorAction->setEnabled(false);

    d->toolComposerAction = new QAction("Composer", this);
#if defined(Q_WS_MAC)
    d->toolComposerAction->setShortcut(Qt::MetaModifier+Qt::Key_2);
#else
    d->toolComposerAction->setShortcut(Qt::ControlModifier+Qt::Key_2);
#endif
    d->toolComposerAction->setToolTip("Switch to the visual editor (Ctrl+2)");
    d->toolComposerAction->setIcon(QIcon(":icons/widget.tiff"));
    connect(d->toolComposerAction, SIGNAL(triggered()), this, SLOT(switchToComposer()));
    d->toolComposerAction->setEnabled(true);

    d->toolViewerAction = new QAction("Viewer", this);
#if defined(Q_WS_MAC)
    d->toolViewerAction->setShortcut(Qt::MetaModifier+Qt::Key_3);
#else
    d->toolViewerAction->setShortcut(Qt::ControlModifier+Qt::Key_3);
#endif
    d->toolViewerAction->setToolTip("Switch to the viewer (Ctrl+3)");
    d->toolViewerAction->setIcon(QIcon(":icons/widget.tiff"));
    connect(d->toolViewerAction, SIGNAL(triggered()), this, SLOT(switchToViewer()));
    d->toolViewerAction->setEnabled(true);

    d->toolRunAction = new QAction("Run", this);
    d->toolRunAction->setShortcut(Qt::ControlModifier+Qt::Key_R);
    d->toolRunAction->setToolTip("Runs the current composition (Ctrl+R)");
    d->toolRunAction->setIcon(QIcon(":icons/run.tiff"));
    connect(d->toolRunAction, SIGNAL(triggered()), this, SLOT(run()));

    d->toolStopAction = new QAction("Stop", this);
    d->toolStopAction->setShortcut(Qt::ControlModifier+Qt::Key_Period);
    d->toolStopAction->setToolTip("Stops the current composition (Ctrl+.)");
    d->toolStopAction->setIcon(QIcon(":icons/stop.tiff"));
    d->toolStopAction->setEnabled(false);
    connect(d->toolStopAction, SIGNAL(triggered()), this, SLOT(stop()));

    d->toolInspectorAction = new QAction("Inspector", this);
    d->toolInspectorAction->setShortcut(Qt::ControlModifier+Qt::Key_I);
    d->toolInspectorAction->setToolTip("Show/hide inspector");
    d->toolInspectorAction->setIcon(QIcon(":icons/inspector.tiff"));
    connect(d->toolInspectorAction, SIGNAL(triggered()), this, SLOT(showInspector()));

    d->toolBar = addToolBar("Editors");
    d->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    d->toolBar->setIconSize(QSize(32, 32));
    d->toolBar->addAction(d->toolEditorAction);
    d->toolBar->addAction(d->toolComposerAction);
    d->toolBar->addAction(d->toolViewerAction);
    d->toolBar->addWidget(new dtkSpacer(d->toolBar));
    d->toolBar->addAction(d->toolRunAction);
    d->toolBar->addAction(d->toolStopAction);
    d->toolBar->addWidget(new dtkSpacer(d->toolBar));
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

    d->composer = new dtkComposer(d->stack);

    d->stack->addWidget(d->composer);

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

    dtkInspectorScene *inspector_scene = new dtkInspectorScene;

    d->inspector = new dtkInspector(this);
    d->inspector->addPage("Scene", inspector_scene);

    connect(dtkAbstractDataFactory::instance(), SIGNAL(created(dtkAbstractData *, QString)), inspector_scene, SLOT(addData(dtkAbstractData *, QString)));
    connect(dtkAbstractProcessFactory::instance(), SIGNAL(created(dtkAbstractProcess *, QString)), inspector_scene, SLOT(addProcess(dtkAbstractProcess *, QString)));
    connect(dtkAbstractViewFactory::instance(), SIGNAL(created(dtkAbstractView *, QString)), inspector_scene, SLOT(addView(dtkAbstractView *, QString)));

    connect(dtkAbstractDataFactory::instance(), SIGNAL(created(dtkAbstractData *, QString)), this, SLOT(registerData(dtkAbstractData *, QString)));
    connect(dtkAbstractProcessFactory::instance(), SIGNAL(created(dtkAbstractProcess *, QString)), this, SLOT(registerProcess(dtkAbstractProcess *, QString)));
    connect(dtkAbstractViewFactory::instance(), SIGNAL(created(dtkAbstractView *, QString)), this, SLOT(registerView(dtkAbstractView *, QString)));

    connect(inspector_scene, SIGNAL(dataSelected(dtkAbstractData *)), d->plugin_browser, SLOT(onDataSelected(dtkAbstractData *)));
    connect(inspector_scene, SIGNAL(processSelected(dtkAbstractProcess *)), d->plugin_browser, SLOT(onProcessSelected(dtkAbstractProcess *)));
    connect(inspector_scene, SIGNAL(viewSelected(dtkAbstractView *)), d->plugin_browser, SLOT(onViewSelected(dtkAbstractView *)));
    
    connect(inspector_scene, SIGNAL(dataSelected(dtkAbstractData *)), d->composer, SLOT(onDataSelected(dtkAbstractData *)));
    connect(inspector_scene, SIGNAL(processSelected(dtkAbstractProcess *)), d->composer, SLOT(onProcessSelected(dtkAbstractProcess *)));
    connect(inspector_scene, SIGNAL(viewSelected(dtkAbstractView *)), d->composer, SLOT(onViewSelected(dtkAbstractView *)));
    
    connect(d->composer, SIGNAL(dataSelected(dtkAbstractData *)), inspector_scene, SLOT(onDataSelected(dtkAbstractData *)));
    connect(d->composer, SIGNAL(processSelected(dtkAbstractProcess *)), inspector_scene, SLOT(onProcessSelected(dtkAbstractProcess *)));
    connect(d->composer, SIGNAL(viewSelected(dtkAbstractView *)), inspector_scene, SLOT(onViewSelected(dtkAbstractView *)));
    
    connect(d->composer, SIGNAL(dataSelected(dtkAbstractData *)), d->plugin_browser, SLOT(onDataSelected(dtkAbstractData *)));
    connect(d->composer, SIGNAL(processSelected(dtkAbstractProcess *)), d->plugin_browser, SLOT(onProcessSelected(dtkAbstractProcess *)));
    connect(d->composer, SIGNAL(viewSelected(dtkAbstractView *)), d->plugin_browser, SLOT(onViewSelected(dtkAbstractView *)));

    dtkSplitter *outer_splitter = new dtkSplitter(this);
    outer_splitter->setOrientation(Qt::Horizontal);
    outer_splitter->addWidget(d->script_browser);
    outer_splitter->addWidget(inner_splitter);
    outer_splitter->addWidget(d->plugin_browser);
    outer_splitter->setStretchFactor(0, 1);
    outer_splitter->setStretchFactor(1, 2);
    outer_splitter->setStretchFactor(2, 1);

    d->preferences = NULL;

    this->onTitleChanged(d->editor->fileName());
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setCentralWidget(outer_splitter);

    this->readSettings();

    dtkCreatorController::instance()->attach(d->plugin_browser);
    dtkCreatorController::instance()->attach(d->script_browser);
    dtkCreatorController::instance()->attach(d->viewer);

    // Setting up core python module

    dtkScriptInterpreterPythonModuleManager::instance()->registerInitializer(&init_core);
    dtkScriptInterpreterPythonModuleManager::instance()->registerCommand(
        "import core"
    );
    dtkScriptInterpreterPythonModuleManager::instance()->registerCommand(
        "dataFactory    = core.dtkAbstractDataFactory.instance()"
    );
    dtkScriptInterpreterPythonModuleManager::instance()->registerCommand(
        "processFactory = core.dtkAbstractProcessFactory.instance()"
    );
    dtkScriptInterpreterPythonModuleManager::instance()->registerCommand(
        "viewFactory    = core.dtkAbstractViewFactory.instance()"
    );
    dtkScriptInterpreterPythonModuleManager::instance()->registerCommand(
        "pluginManager  = core.dtkPluginManager.instance()"
    );
    dtkScriptInterpreterPythonModuleManager::instance()->registerCommand(
        "deviceFactory  = core.dtkAbstractDeviceFactory.instance()"
    );

    // Setting up creator python module

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

    // Setting up core tcl module

    // -- Setting up core module
    dtkScriptInterpreterTclModuleManager::instance()->registerInitializer(&Core_Init);
    dtkScriptInterpreterTclModuleManager::instance()->registerCommand(
        "set dataFactory    [dtkAbstractDataFactory_instance]"
    );
    dtkScriptInterpreterTclModuleManager::instance()->registerCommand(
        "set processFactory [dtkAbstractProcessFactory_instance]"
    );
    dtkScriptInterpreterTclModuleManager::instance()->registerCommand(
        "set viewFactory    [dtkAbstractViewFactory_instance]"
    );
    dtkScriptInterpreterTclModuleManager::instance()->registerCommand(
        "set pluginManager  [dtkPluginManager_instance]"
    );

    // Setting up creator tcl module

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

    d->interpreter->registerInterpreter(dtkScriptInterpreterPool::instance()->python());
    d->interpreter->registerAsHandler(dtkCreatorRedirectLogHandler);
}

dtkCreatorMainWindow::~dtkCreatorMainWindow(void)
{
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
    QSize size = settings.value("size", QSize(600, 400)).toSize();
    move(pos);
    resize(size);
    settings.endGroup();

    d->editor->readSettings();
    d->interpreter->readSettings();
    d->inspector->readSettings();
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
    d->inspector->writeSettings();
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
    QPoint pos = d->inspector->pos();

    d->inspector->setVisible(!d->inspector->isVisible());
    d->inspector->move(pos);
}

void dtkCreatorMainWindow::showPreferences(void)
{
    if(!d->preferences) {
        d->preferences = new dtkPreferencesWidget(this);
        d->preferences->addPage("Editor", d->editor->preferencesWidget(this));
        d->preferences->addPage("Interpreter", d->interpreter->preferencesWidget(this));
    }

    d->preferences->show();
}

void dtkCreatorMainWindow::switchToEditor(void)
{
    d->stack->setCurrentIndex(0);

    d->toolEditorAction->setEnabled(false);
    d->toolComposerAction->setEnabled(true);
    d->toolViewerAction->setEnabled(true);
}

void dtkCreatorMainWindow::switchToComposer(void)
{
    d->stack->setCurrentIndex(1);

    d->toolEditorAction->setEnabled(true);
    d->toolComposerAction->setEnabled(false);
    d->toolViewerAction->setEnabled(true);
}

void dtkCreatorMainWindow::switchToViewer(void)
{
    d->stack->setCurrentIndex(2);

    d->toolEditorAction->setEnabled(true);
    d->toolComposerAction->setEnabled(true);
    d->toolViewerAction->setEnabled(false);
}

void dtkCreatorMainWindow::closeEvent(QCloseEvent *event)
{
    if (d->maySave()) {
        this->writeSettings();
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
        this->setWindowTitle(this->windowTitle() + "*");
}

void dtkCreatorMainWindow::run(void)
{
    d->toolRunAction->setEnabled(false);
    d->toolStopAction->setEnabled(true);

    d->composer->run();
}

void dtkCreatorMainWindow::stop(void)
{
    d->toolRunAction->setEnabled(true);
    d->toolStopAction->setEnabled(false);

    d->composer->stop();
}

void dtkCreatorMainWindow::registerData(dtkAbstractData *data, QString type)
{
    int stat;

    d->interpreter->interpreter()->blockSignals(true);

    if(dtkScriptInterpreterPython *interpreter = dynamic_cast<dtkScriptInterpreterPython *>(d->interpreter->interpreter()))
        interpreter->interpret(QString("%1 = dataFactory.get(\"%2\", \"%1\")").arg(data->name()).arg(type), &stat);

    if(dtkScriptInterpreterTcl *interpreter = dynamic_cast<dtkScriptInterpreterTcl *>(d->interpreter->interpreter()))
        interpreter->interpret(QString("set $1 [$dataFactory get \"2\" \"1\"]").arg(data->name()).arg(type), &stat);

    d->interpreter->interpreter()->blockSignals(false);
}

void dtkCreatorMainWindow::registerProcess(dtkAbstractProcess *process, QString type)
{
    int stat;

    d->interpreter->interpreter()->blockSignals(true);

    if(dtkScriptInterpreterPython *interpreter = dynamic_cast<dtkScriptInterpreterPython *>(d->interpreter->interpreter()))
        interpreter->interpret(QString("%1 = processFactory.get(\"%2\", \"%1\")").arg(process->name()).arg(type), &stat);

    if(dtkScriptInterpreterTcl *interpreter = dynamic_cast<dtkScriptInterpreterTcl *>(d->interpreter->interpreter()))
        interpreter->interpret(QString("set $1 [$processFactory get \"2\" \"1\"]").arg(process->name()).arg(type), &stat);

    d->interpreter->interpreter()->blockSignals(false);
}

void dtkCreatorMainWindow::registerView(dtkAbstractView *view, QString type)
{
    int stat;

    d->interpreter->interpreter()->blockSignals(true);

    if(dtkScriptInterpreterPython *interpreter = dynamic_cast<dtkScriptInterpreterPython *>(d->interpreter->interpreter()))
        interpreter->interpret(QString("%1 = viewFactory.get(\"%2\", \"%1\")").arg(view->name()).arg(type), &stat);

    if(dtkScriptInterpreterTcl *interpreter = dynamic_cast<dtkScriptInterpreterTcl *>(d->interpreter->interpreter()))
        interpreter->interpret(QString("set $1 [$viewFactory get \"2\" \"1\"]").arg(view->name()).arg(type), &stat);

    d->interpreter->interpreter()->blockSignals(false);
}
