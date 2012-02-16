/* dtkComposerSceneNodeEditor.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 10:08:29 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 15 18:34:40 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENENODEEDITOR_H
#define DTKCOMPOSERSCENENODEEDITOR_H

#include <QtGui>

class dtkComposerScene;
class dtkComposerSceneNode;
class dtkComposerSceneNodeEditorPrivate;
class dtkComposerStack;

class dtkComposerSceneNodeEditor : public QWidget
{
    Q_OBJECT

public:
     dtkComposerSceneNodeEditor(QWidget *parent = 0);
    ~dtkComposerSceneNodeEditor(void);

public slots:
    void setNode(dtkComposerSceneNode *node);
    void setScene(dtkComposerScene *scene);
    void setStack(dtkComposerStack *stack);

public slots:
    void clear(void);

protected slots:
    void addInputPort(void);
    void removeInputPort(void);

protected slots:
    void addOutputPort(void);
    void removeOutputPort(void);

protected slots:
    void onTitleChanged(const QString& text);

private:
    dtkComposerSceneNodeEditorPrivate *d;
};

#endif
