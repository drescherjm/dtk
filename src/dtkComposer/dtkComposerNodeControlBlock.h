/* dtkComposerNodeControlBlock.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Mar  3 14:46:36 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar  3 18:14:49 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONTROLBLOCK_H
#define DTKCOMPOSERNODECONTROLBLOCK_H

#include <QtGui>

class dtkComposerNode;
class dtkComposerNodeControlBlockPrivate;

class dtkComposerNodeControlBlock : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)

#if QT_VERSION >= 0x040600
    Q_INTERFACES(QGraphicsItem)
#endif

public:
     dtkComposerNodeControlBlock(const QString& title, QGraphicsItem *parent);
    ~dtkComposerNodeControlBlock(void);

    QString title(void) const;
    QColor penColor(void) const;
    void setPenColor(const QColor& color);

    QList<dtkComposerNode *>      nodes(void);
    QList<dtkComposerNode *> startNodes(void);
    QList<dtkComposerNode *>   endNodes(void);
    
public:
    void highlight(void);

private:
    dtkComposerNodeControlBlockPrivate *d;
};

#endif
