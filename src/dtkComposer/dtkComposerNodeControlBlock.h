/* dtkComposerNodeControlBlock.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Mar  3 14:46:36 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Nov  4 10:16:48 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 94
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
    QList<dtkComposerNode *> startNodes(QList<dtkComposerNode *> parents = QList<dtkComposerNode *>());
    QList<dtkComposerNode *>   endNodes(QList<dtkComposerNode *> parents = QList<dtkComposerNode *>());

    void        addNode(dtkComposerNode *node);
    void     removeNode(dtkComposerNode *node);
    void removeAllNodes(void);

    QList<dtkComposerNodeProperty *>  leftProperties(void);
    QList<dtkComposerNodeProperty *> rightProperties(void);

    dtkComposerNodeProperty  *appendLeftProperty(QString name, dtkComposerNode *parent = 0);
    dtkComposerNodeProperty *appendRightProperty(QString name, dtkComposerNode *parent = 0);

    dtkComposerNodeProperty  *appendLeftPassThroughProperty(QString name, dtkComposerNode *parent = 0);
    dtkComposerNodeProperty *appendRightPassThroughProperty(QString name, dtkComposerNode *parent = 0);

    dtkComposerNodeProperty  *appendLeftProperty(QString name, dtkComposerNodeProperty::Type type, dtkComposerNodeProperty::Multiplicity multiplicity, dtkComposerNodeProperty::Behavior behavior, dtkComposerNode *parent = 0);
    dtkComposerNodeProperty *appendRightProperty(QString name, dtkComposerNodeProperty::Type type, dtkComposerNodeProperty::Multiplicity multiplicity, dtkComposerNodeProperty::Behavior behavior, dtkComposerNode *parent = 0);

    void  removeLeftProperty(dtkComposerNodeProperty *property);
    void removeRightProperty(dtkComposerNodeProperty *property);
    void removeAllProperties(void);

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
