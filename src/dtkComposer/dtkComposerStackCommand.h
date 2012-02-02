/* dtkComposerStackCommand.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 18:15:13 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb  2 23:52:42 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 63
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSTACKCOMMAND_H
#define DTKCOMPOSERSTACKCOMMAND_H

#include <QtCore>
#include <QtGui>

class dtkComposerFactory;
class dtkComposerScene;
class dtkComposerSceneNode;
class dtkComposerSceneNodeComposite;
class dtkComposerSceneNodeList;
class dtkComposerSceneNote;
class dtkComposerScenePort;
class dtkComposerStackCommandPrivate;

class dtkComposerStackCommand : public QUndoCommand
{
public:
             dtkComposerStackCommand(dtkComposerStackCommand *parent = 0);
    virtual ~dtkComposerStackCommand(void);

public:
    void setFactory(dtkComposerFactory *factory);
    void setScene(dtkComposerScene *scene);

public:
    // virtual void redo(void) = 0;
    // virtual void undo(void) = 0;

protected:
    dtkComposerStackCommandPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateNodePrivate;

class dtkComposerStackCommandCreateNode : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandCreateNode(void);
    ~dtkComposerStackCommandCreateNode(void);

public:
    void setPosition(const QPointF& position);
    void setName(const QString& name);
    void setType(const QString& type);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandCreateNodePrivate *e;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyNodePrivate;

class dtkComposerStackCommandDestroyNode : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandDestroyNode(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandDestroyNode(void);

public:
    void setNode(dtkComposerSceneNode *node);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandDestroyNodePrivate *e;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateEdgePrivate;

class dtkComposerStackCommandCreateEdge : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandCreateEdge(void);
    ~dtkComposerStackCommandCreateEdge(void);

public:
    void setSource(dtkComposerScenePort *source);
    void setDestination(dtkComposerScenePort *destination);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandCreateEdgePrivate *e;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerStackCommandCreateNote
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateNotePrivate;

class dtkComposerStackCommandCreateNote : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandCreateNote(void);
    ~dtkComposerStackCommandCreateNote(void);

public:
    void setPosition(const QPointF& position);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandCreateNotePrivate *e;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyNotePrivate;

class dtkComposerStackCommandDestroyNote : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandDestroyNote(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandDestroyNote(void);

public:
    void setNote(dtkComposerSceneNote *note);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandDestroyNotePrivate *e;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateGroupPrivate;

class dtkComposerStackCommandCreateGroup : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandCreateGroup(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandCreateGroup(void);

public:
    void setNodes(dtkComposerSceneNodeList nodes);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandCreateGroupPrivate *e;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandExplodeGroupPrivate;

class dtkComposerStackCommandExplodeGroup : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandExplodeGroup(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandExplodeGroup(void);

public:
    void setNode(dtkComposerSceneNodeComposite *node);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandExplodeGroupPrivate *e;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandEnterGroupPrivate;

class dtkComposerStackCommandEnterGroup : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandEnterGroup(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandEnterGroup(void);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandEnterGroupPrivate *e;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandLeaveGroupPrivate;

class dtkComposerStackCommandLeaveGroup : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandLeaveGroup(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandLeaveGroup(void);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandLeaveGroupPrivate *e;
};

#endif
