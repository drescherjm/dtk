/* dtk3DItem.h ---
 * 
 * Author: Julien Wintz
 * Created: Sat Mar 30 13:53:33 2013 (+0100)
 * Version: 
 * Last-Updated: Sat Mar 30 15:36:40 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Change Log:
 * 
 */

#pragma once

#include <Qt3D/QGLBuilder>
#include <Qt3D/QGLSceneNode>
#include <Qt3D/QGLView>

#include <QtGui>

class dtk3DItemPrivate;

class dtk3DItem : public QGLSceneNode
{
    Q_OBJECT

public:
     dtk3DItem(QObject *parent = 0);
    ~dtk3DItem(void);

#pragma mark -
#pragma mark Transformations

public:
    QMatrix4x4  localTransform(void);
    QMatrix4x4 globalTransform(void);

public:
    QVector3D  localPosition(void);
    QVector3D globalPosition(void);

public:
    void translate(const QVector3D& translation);
    void    rotate(const QVector3D& axis, qreal angle);

#pragma mark -
#pragma mark Coordinate mapping - to item

    const QVector3D mapToItem(const QPoint& point);
    const QVector3D mapToItem(const QVector3D& vector);

#pragma mark -
#pragma mark Item attributes

public:
    void setId(int id);
    void setColor(const QColor& color);

#pragma mark -
#pragma mark Scene management

    void initialize(QGLPainter *painter, QGLView *view);
    void       draw(QGLPainter *painter);
    void update(void);

#pragma mark -
#pragma mark Event emission

signals:
    void clicked(void);

#pragma mark -
#pragma mark Event handling 

protected:
    bool event(QEvent *event);

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

protected:
    void mouseTranslateEvent(QMouseEvent *event);
    void mouseRotateEvent(QMouseEvent *event);

#pragma mark -
#pragma mark Debug operators

private:
    friend QDebug operator<<(QDebug dbg,       dtk3DItem *item);
    friend QDebug operator<<(QDebug dbg, const dtk3DItem& item);

private:
     dtk3DItemPrivate *d;
};

QDebug operator<<(QDebug dbg,       dtk3DItem *item);
QDebug operator<<(QDebug dbg, const dtk3DItem& item);
