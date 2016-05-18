/* @(#)dtkComposerEvaluatorToolBar.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2016 - Nicolas Niclausse, Inria.
 * Created: 2016/05/18 07:58:26
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerExport.h"

#include <QtWidgets>

class dtkComposerWidget;
class dtkComposerGraphNode;
class dtkComposerEvaluatorToolBarPrivate;

class DTKCOMPOSER_EXPORT dtkComposerEvaluatorToolBar : public QToolBar
{
    Q_OBJECT

public:
             dtkComposerEvaluatorToolBar(const QString & title, QWidget *parent = 0);
             dtkComposerEvaluatorToolBar(QWidget *parent = 0);
    virtual ~dtkComposerEvaluatorToolBar(void);

public slots:
    void onEvaluatorFinished(void);
    void onEvaluatorStarted(void);
    void onEvaluatorPaused(dtkComposerGraphNode *node);

public:
    void setComposerWidget(dtkComposerWidget *composer);
    QMenu *menu(QWidget *parent = 0);

private:
    dtkComposerEvaluatorToolBarPrivate *d;
};



