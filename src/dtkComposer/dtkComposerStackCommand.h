/* dtkComposerStackCommand.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 18:15:13 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb  6 22:08:42 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 97
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
class dtkComposerSceneEdge;
class dtkComposerSceneEdgeList;
class dtkComposerSceneNode;
class dtkComposerSceneNodeComposite;
class dtkComposerSceneNodeList;
class dtkComposerSceneNote;
class dtkComposerSceneNoteList;
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

protected:
    dtkComposerStackCommandPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Create Node Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateNodePrivate;

class dtkComposerStackCommandCreateNode : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandCreateNode(dtkComposerStackCommand *parent = 0);
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
// Destroy Node Command
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
// Create Edge Command
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
// Destroy Edge Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyEdgePrivate;

class dtkComposerStackCommandDestroyEdge : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandDestroyEdge(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandDestroyEdge(void);

public:
    void setEdge(dtkComposerSceneEdge *edge);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandDestroyEdgePrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Create Note Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateNotePrivate;

class dtkComposerStackCommandCreateNote : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandCreateNote(dtkComposerStackCommand *parent = 0);
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
// Destroy Note Command
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
// Create Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandCreateGroupPrivate;

class dtkComposerStackCommandCreateGroup : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandCreateGroup(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandCreateGroup(void);

public:
    void setNodes(dtkComposerSceneNodeList nodes);
    void setNotes(dtkComposerSceneNoteList notes);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandCreateGroupPrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Destroy Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandDestroyGroupPrivate;

class dtkComposerStackCommandDestroyGroup : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandDestroyGroup(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandDestroyGroup(void);

public:
    void setNode(dtkComposerSceneNodeComposite *node);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandDestroyGroupPrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Enter Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandEnterGroupPrivate;

class dtkComposerStackCommandEnterGroup : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandEnterGroup(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandEnterGroup(void);

public:
    void setNode(dtkComposerSceneNodeComposite *node);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandEnterGroupPrivate *e;
};

// /////////////////////////////////////////////////////////////////
// Leave Group Command
// /////////////////////////////////////////////////////////////////

class dtkComposerStackCommandLeaveGroupPrivate;

class dtkComposerStackCommandLeaveGroup : public dtkComposerStackCommand
{
public:
     dtkComposerStackCommandLeaveGroup(dtkComposerStackCommand *parent = 0);
    ~dtkComposerStackCommandLeaveGroup(void);

public:
    void setNode(dtkComposerSceneNodeComposite *node);

public:
    void redo(void);
    void undo(void);

private:
    dtkComposerStackCommandLeaveGroupPrivate *e;
};

#endif
