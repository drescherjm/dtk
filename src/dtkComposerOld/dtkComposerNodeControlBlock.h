/* dtkComposerNodeControlBlock.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Mar  3 14:46:36 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 10 13:44:03 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 126
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONTROLBLOCK_H
#define DTKCOMPOSERNODECONTROLBLOCK_H

#include <dtkCore/dtkGlobal>

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

public:
    dtkComposerNodeControl *parentNode(void) const;

    QString title(void) const;

public:
    void     appendNode(dtkComposerNode *node);
    void     removeNode(dtkComposerNode *node);
    void removeAllNodes(void);

    void appendLeftProperty(dtkComposerNodeProperty *property);
    void appendRightProperty(dtkComposerNodeProperty *property);

    void  removeLeftProperty(dtkComposerNodeProperty *property);
    void removeRightProperty(dtkComposerNodeProperty *property);
    void removeAllProperties(void);

    void clear(void);
    void clearProperty(dtkComposerNodeProperty *property);

public:
    const QList<dtkComposerNode *>&      nodes(void) const;
          QList<dtkComposerNode *>  startNodes(QList<dtkComposerNode *> parents = QList<dtkComposerNode *>());

    const QList<dtkComposerNodeProperty *>&  leftProperties(void) const;
    const QList<dtkComposerNodeProperty *>& rightProperties(void) const;

    dtkComposerNodeProperty *property(QString name, dtkComposerNodeProperty::Position position);

public:
    QColor brushColor(void) const;
    QColor penColor(void) const;

    void setRemoveButtonVisible(bool visible);

    void setBrushColor(const QColor& color);
    void setInteractive(bool interactive);
    void setPenColor(const QColor& color);
    void setRect(const QRectF& rectangle);
    void setRect(qreal x, qreal y, qreal width, qreal height);

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
