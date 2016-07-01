/* dtkComposerEvaluatorToolbar.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2016 - Nicolas Niclausse, Inria.
 * Created: 2016/05/18 08:03:55
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerEvaluatorToolBar.h"

#include "dtkComposerEvaluator.h"
#include "dtkComposerGraphNode.h"
#include "dtkComposerScene.h"
#include "dtkComposerWidget.h"

class dtkComposerEvaluatorToolBarPrivate {

public:
    QAction *run_action;
    QAction *stop_action;
    QAction *step_action;
    QAction *continue_action;
    QAction *next_action;
    QAction *reset_action;
    QAction *pause_action;

public:
    dtkComposerWidget *composer;
    dtkComposerEvaluatorToolBar *q;

public:
    void init(void);
};

void dtkComposerEvaluatorToolBarPrivate::init(void)
{
    composer = NULL;
    q->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    q->setIconSize(QSize(32, 32));

    run_action = q->addAction(QIcon(":dtkComposer/pixmaps/dtkCreatorToolbarButton_Run_Active.png"), "Run");
    run_action->setShortcut(Qt::ControlModifier + Qt::ShiftModifier + Qt::Key_R);

    step_action = q->addAction(QIcon(":dtkComposer/pixmaps/dtkCreatorToolbarButton_Step_Active.png"), "Step");
    step_action->setShortcut(Qt::ControlModifier + Qt::ShiftModifier + Qt::Key_N);
    step_action->setEnabled(false);

    continue_action = q->addAction(QIcon(":dtkComposer/pixmaps/dtkCreatorToolbarButton_Continue_Active.png"), "Cont");
    continue_action->setShortcut(Qt::ControlModifier + Qt::ShiftModifier + Qt::Key_C);
    continue_action->setEnabled(false);

    next_action = q->addAction(QIcon(":dtkComposer/pixmaps/dtkCreatorToolbarButton_Continue_Active.png"), "Next");
    next_action->setShortcut(Qt::ControlModifier + Qt::ShiftModifier + Qt::Key_T);
    next_action->setEnabled(false);

    pause_action = q->addAction(QIcon(":dtkComposer/pixmaps/dtkCreatorToolbarButton_Pause_Active.png"), "Pause");
    pause_action->setShortcut(Qt::ControlModifier + Qt::ShiftModifier + Qt::Key_Period);
    pause_action->setEnabled(false);

    // stop_action = q->addAction(QIcon(":dtkComposer/pixmaps/dtkCreatorToolbarButton_Stop_Active.png"), "Stop");
    // stop_action->setShortcut(Qt::ControlModifier + Qt::ShiftModifier + Qt::Key_Period);
    // stop_action->setEnabled(false);

    reset_action = q->addAction(QIcon(":dtkComposer/pixmaps/dtkCreatorToolbarButton_Reset_Active.png"), "Reset");
    reset_action->setShortcut(Qt::ControlModifier + Qt::ShiftModifier + Qt::Key_D);

}


// -------------------------------- dtkComposerEvaluatorToolBar ---------------------

dtkComposerEvaluatorToolBar::dtkComposerEvaluatorToolBar(const QString & title, QWidget *parent) : QToolBar(title, parent), d(new dtkComposerEvaluatorToolBarPrivate)
{
    d->q = this;
    d->init();
}

dtkComposerEvaluatorToolBar::dtkComposerEvaluatorToolBar(QWidget *parent) : QToolBar(parent), d(new dtkComposerEvaluatorToolBarPrivate)
{
    d->q = this;
    d->init();
}

dtkComposerEvaluatorToolBar::~dtkComposerEvaluatorToolBar(void)
{
    if (d) {
        delete d;
    }
}

QMenu *dtkComposerEvaluatorToolBar::menu(QWidget *parent)
{
    QMenu *debug_menu = new QMenu("Run/Debug", parent);
    debug_menu->addAction(d->run_action);
    debug_menu->addAction(d->step_action);
    debug_menu->addAction(d->continue_action);
    debug_menu->addAction(d->next_action);
    debug_menu->addAction(d->pause_action);
    // debug_menu->addAction(d->stop_action);
    debug_menu->addAction(d->reset_action);
    return debug_menu;
}

void dtkComposerEvaluatorToolBar::setComposerWidget(dtkComposerWidget *composer)
{
    // -- Connections

    d->composer = composer;
    connect(d->run_action, SIGNAL(triggered()), this, SLOT(onEvaluatorStarted()));
    connect(d->composer->evaluator(), SIGNAL(evaluationStopped()), this, SLOT(onEvaluatorFinished()));
    connect(d->composer, SIGNAL(evaluationStopped()), this, SLOT(onEvaluatorFinished()));
    connect(d->composer->evaluator(), SIGNAL(evaluationPaused(dtkComposerGraphNode*)), this, SLOT(onEvaluatorPaused(dtkComposerGraphNode*)));

    connect(d->step_action, SIGNAL(triggered()), d->composer, SLOT(step()));
    connect(d->continue_action, SIGNAL(triggered()), d->composer, SLOT(cont()));
    connect(d->next_action, SIGNAL(triggered()), d->composer, SLOT(next()));
    connect(d->pause_action, SIGNAL(triggered()), d->composer, SLOT(stop()));
    connect(d->reset_action, SIGNAL(triggered()), d->composer, SLOT(reset()));

}

void dtkComposerEvaluatorToolBar::onEvaluatorPaused(dtkComposerGraphNode *node)
{
    d->step_action->setEnabled(true);
    d->next_action->setEnabled(true);
    d->continue_action->setEnabled(true);
    d->run_action->setEnabled(false);
    d->pause_action->setEnabled(false);

    d->composer->scene()->onEvaluationPaused(node->wrapee());

}

void dtkComposerEvaluatorToolBar::onEvaluatorStarted(void)
{
    d->step_action->setEnabled(false);
    d->next_action->setEnabled(false);
    d->continue_action->setEnabled(false);
    d->run_action->setEnabled(false);
    d->pause_action->setEnabled(true);

    d->composer->run();
}

void dtkComposerEvaluatorToolBar::onEvaluatorFinished(void)
{
    d->step_action->setEnabled(false);
    d->next_action->setEnabled(false);
    d->continue_action->setEnabled(false);
    d->run_action->setEnabled(true);
    d->pause_action->setEnabled(false);

    d->composer->scene()->onEvaluationFinished();
}

