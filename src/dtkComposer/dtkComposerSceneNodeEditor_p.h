/* dtkComposerSceneNodeEditor_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 10:28:04 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  8 13:38:43 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 30
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENENODEEDITOR_P_H
#define DTKCOMPOSERSCENENODEEDITOR_P_H

#include <QtGui>

class dtkComposerScene;
class dtkComposerSceneNode;
class dtkComposerScenePort;
class dtkComposerStack;

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeEditorList
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodeEditorList : public QListWidget
{
    Q_OBJECT

public:
     dtkComposerSceneNodeEditorList(QWidget *parent = 0);
    ~dtkComposerSceneNodeEditorList(void);

public:
    void  addInputPort(dtkComposerScenePort *port);
    void addOutputPort(dtkComposerScenePort *port);

protected slots:
    void onItemChanged(QListWidgetItem *item);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeEditorListItem
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodeEditorListItem : public QListWidgetItem
{
public:
     dtkComposerSceneNodeEditorListItem(dtkComposerScenePort *port, dtkComposerSceneNodeEditorList *parent);
    ~dtkComposerSceneNodeEditorListItem(void);

    int type(void) const;

    dtkComposerScenePort *port(void);

private:
    dtkComposerScenePort *m_port;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeEditor
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodeEditorPrivate
{
public:
    dtkComposerSceneNodeEditorList *input_ports;
    dtkComposerSceneNodeEditorList *output_ports;

public:
    dtkComposerScene *scene;
    dtkComposerSceneNode *node;
    dtkComposerStack *stack;

public:
    QPushButton *add_input_port;
    QPushButton *rem_input_port;
    QPushButton *add_output_port;
    QPushButton *rem_output_port;
};

#endif
