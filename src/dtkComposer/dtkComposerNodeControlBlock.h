/* dtkComposerNodeControlBlock.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Mar  3 14:46:36 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar 15 15:45:19 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 64
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
class dtkComposerNodeControl;
class dtkComposerNodeControlBlockPrivate;
class dtkComposerNodeProperty;

class dtkComposerNodeControlBlock : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QColor brushColor READ brushColor WRITE setBrushColor)
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)

#if QT_VERSION >= 0x040600
    Q_INTERFACES(QGraphicsItem)
#endif

public:
     dtkComposerNodeControlBlock(const QString& title, dtkComposerNodeControl *parent);
    ~dtkComposerNodeControlBlock(void);

    dtkComposerNodeControl *parentNode(void);

    QString title(void) const;
    QColor brushColor(void) const;
    QColor penColor(void) const;

    void setRemoveButtonVisible(bool visible);

    void setBrushColor(const QColor& color);
    void setInteractive(bool interactive);
    void setPenColor(const QColor& color);
    void setRect(const QRectF& rectangle);
    void setRect(qreal x, qreal y, qreal width, qreal height);

    QList<dtkComposerNode *>      nodes(void);
    QList<dtkComposerNode *> startNodes(void);
    QList<dtkComposerNode *>   endNodes(void);

    QList<dtkComposerNodeProperty *>  inputProperties(void);
    QList<dtkComposerNodeProperty *> outputProperties(void);

    dtkComposerNodeProperty  *addInputProperty(QString name, dtkComposerNode *parent = 0);
    dtkComposerNodeProperty *addOutputProperty(QString name, dtkComposerNode *parent = 0);

public:
    QRectF minimalBoundingRect(void);
    
public:
    static void highlight(dtkComposerNodeControlBlock *block);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
        
private:
    dtkComposerNodeControlBlockPrivate *d;
};

#endif
