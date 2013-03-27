/* dtk3DItem.h ---
 * 
 * Author: Julien Wintz
 * Created: Fri Mar 22 12:19:49 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Mar 27 16:01:32 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 99
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtGui/QVector3D>
#include <QtGui/QQuaternion>

#include <Qt3D/QGLPainter>
#include <Qt3D/QGLSceneNode>
#include <Qt3D/QGLView.h>

class dtk3DItemPrivate;

class dtk3DItem : public QObject
{
    Q_OBJECT

public:
             dtk3DItem(QObject *parent = 0);
    virtual ~dtk3DItem(void);

#pragma mark -
#pragma mark Geometric attributes

    virtual QBox3D boundingBox(void) const;

#pragma mark -
#pragma mark Scene attributes
    
    QGLSceneNode *node(void);
    QGLSceneNode *clone(void);

#pragma mark -
#pragma mark Picking attributes
    
    void setId(int id);

#pragma mark -
#pragma mark Geometric attributes

    void setNode(QGLSceneNode *node);

#pragma mark -
#pragma mark Frame attributes

    void setScale(qreal scale);
    void setPosition(const QVector3D& position);
    void setOrientation(const QVector3D& orientation, qreal angle);
    void setOrientation(const QQuaternion& orientation);

#pragma mark -
#pragma mark Visuals attributes

    void setEffect(QGLAbstractEffect *effect);

    void      setMaterial(QGLMaterial *material);
    void setHoverMaterial(QGLMaterial *material);

    void setColor(const QColor& color);

#pragma mark -
#pragma mark Management

    virtual void initialize(QGLView *view, QGLPainter *painter);
    virtual void      paint(QGLView *view, QGLPainter *painter);

#pragma mark -
#pragma mark Event handling
    
    bool event(QEvent *event);

signals:
    void pressed(void);
    void released(void);
    void clicked(void);
    void doubleClicked(void);
    void hoverChanged(void);
    void hovered(bool on);

protected:
    virtual void  predraw(QGLView *view, QGLPainter *painter);
    virtual void     draw(QGLView *view, QGLPainter *painter);
    virtual void postdraw(QGLView *view, QGLPainter *painter);

protected:
    // virtual void pan(int deltax, int deltay);
    // virtual void rot(int deltax, int deltay);

private:
    dtk3DItemPrivate *d;
};
