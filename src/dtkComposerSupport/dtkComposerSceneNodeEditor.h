/* dtkComposerSceneNodeEditor.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 10:08:29 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Sep 23 14:55:58 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 53
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERSCENENODEEDITOR_H
#define DTKCOMPOSERSCENENODEEDITOR_H

#include "dtkComposerSupportExport.h"

#include <QtWidgets>

class dtkComposerScene;
class dtkComposerSceneNode;
class dtkComposerSceneNodeEditorPrivate;
class dtkComposerStack;
class dtkComposerGraph;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerSceneNodeEditor : public QWidget
{
    Q_OBJECT

public:
    dtkComposerSceneNodeEditor(QWidget *parent = 0);
    ~dtkComposerSceneNodeEditor(void);

public slots:
    virtual void setNode(dtkComposerSceneNode *node);
    virtual void setScene(dtkComposerScene *scene);
    virtual void setStack(dtkComposerStack *stack);
    virtual void setGraph(dtkComposerGraph *graph);

public slots:
    virtual void clear(void);

protected slots:
    void addLoopPort(void);
    void removeLoopPort(void);

protected slots:
    void addBlock(void);
    void removeBlock(void);

protected slots:
    void addInputPort(void);
    void removeInputPort(void);

protected slots:
    void addOutputPort(void);
    void removeOutputPort(void);

protected slots:
    void onBlockChanged(int index);
    void onTitleChanged(const QString& text);

protected slots:
    void onBrowse(void);
    void onBrowseDirectory(void);
    void onValueChanged(bool);
    void onValueChanged(int);
    void onValueChanged(double);
    void onValueChanged(const QString&);
    void onImplementationChanged(const QString&);

protected:
    dtkComposerSceneNodeEditorPrivate *d;
};

#endif
