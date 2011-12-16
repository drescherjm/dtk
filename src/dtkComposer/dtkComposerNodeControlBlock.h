/* dtkComposerNodeControlBlock.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Mar  3 14:46:36 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Sep 16 17:13:23 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 90
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONTROLBLOCK_H
#define DTKCOMPOSERNODECONTROLBLOCK_H

#include <dtkCore/dtkGlobal.h>

#include "dtkComposerExport.h"
#include "dtkComposerNodeProperty.h"

#include <QtGui>

class dtkComposerNode;
class dtkComposerNodeControl;
class dtkComposerNodeControlBlockPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeControlBlock : public QObject, public QGraphicsRectItem
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

    void        addNode(dtkComposerNode *node);
    void     removeNode(dtkComposerNode *node);
    void removeAllNodes(void);

    QList<dtkComposerNodeProperty *>  inputProperties(void);
    QList<dtkComposerNodeProperty *> outputProperties(void);

    dtkComposerNodeProperty  *addInputProperty(QString name, dtkComposerNode *parent = 0);
    dtkComposerNodeProperty *addOutputProperty(QString name, dtkComposerNode *parent = 0);

    dtkComposerNodeProperty  *addInputPassThroughProperty(QString name, dtkComposerNode *parent = 0);
    dtkComposerNodeProperty *addOutputPassThroughProperty(QString name, dtkComposerNode *parent = 0);

    dtkComposerNodeProperty  *addInputProperty(QString name, dtkComposerNodeProperty::Type type, dtkComposerNodeProperty::Multiplicity multiplicity, dtkComposerNodeProperty::Behavior behavior, dtkComposerNode *parent = 0);
    dtkComposerNodeProperty *addOutputProperty(QString name, dtkComposerNodeProperty::Type type, dtkComposerNodeProperty::Multiplicity multiplicity, dtkComposerNodeProperty::Behavior behavior, dtkComposerNode *parent = 0);

    void  removeInputProperty(dtkComposerNodeProperty *property);
    void removeOutputProperty(dtkComposerNodeProperty *property);
    void  removeAllProperties(void);

public:
    qreal height(void);
    qreal heightRatio(void);

    void setHeight(qreal height);
    void setHeightRatio(qreal height_ratio);
    void adjustChildNodes(qreal dw, qreal dh);
    QRectF minimalBoundingRect(void);
    
public:
    void highlight(bool ok);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
        
private:
    dtkComposerNodeControlBlockPrivate *d;
};

#endif
