/* dtk3DItem.h ---
 * 
 * Author: Julien Wintz
 * Created: Fri Mar 22 12:19:49 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Mar 22 14:48:25 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 67
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
    ~dtk3DItem(void);

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

#pragma mark -
#pragma mark Management

    void initialize(QGLView *view, QGLPainter *painter);
    void      paint(QGLView *view, QGLPainter *painter);

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

private:
    dtk3DItemPrivate *d;
};
