/* dtkComposerSceneNodeEditor.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 10:08:29 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:43:40 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 51
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include <QtGui>

class dtkComposerScene;
class dtkComposerSceneNode;
class dtkComposerSceneNodeEditorPrivate;
class dtkComposerStack;
class dtkComposerGraph;

class DTKCOMPOSER_EXPORT dtkComposerSceneNodeEditor : public QWidget
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

