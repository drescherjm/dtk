/* dtkComposerSceneNodeEditor.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 10:08:29 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Jun 28 11:17:36 2012 (+0200)
 *           By: tkloczko
 *     Update #: 46
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENENODEEDITOR_H
#define DTKCOMPOSERSCENENODEEDITOR_H

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
    void setNode(dtkComposerSceneNode *node);
    void setScene(dtkComposerScene *scene);
    void setStack(dtkComposerStack *stack);
    void setGraph(dtkComposerGraph *graph);

public slots:
    void clear(void);

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
    void onValueChanged(bool);
    void onValueChanged(int);
    void onValueChanged(double);
    void onValueChanged(const QString&);
    void onImplementationChanged(const QString&);

private:
    dtkComposerSceneNodeEditorPrivate *d;
};

#endif
