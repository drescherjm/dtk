/* dtk3DQuickItem.h ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr  3 14:56:54 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Apr  9 18:00:43 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 53
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtk3D>

#include <QtCore>
#include <QtQuick>

class dtk3DQuickItemPrivate;

class dtk3DQuickItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(qreal x READ x WRITE setX)
    Q_PROPERTY(qreal y READ y WRITE setY)
    Q_PROPERTY(qreal z READ z WRITE setZ)
    Q_PROPERTY(bool wireframe READ wireframe WRITE setWireframe)

public:
     dtk3DQuickItem(QObject *parent = 0);
    ~dtk3DQuickItem(void);

#pragma mark -
#pragma mark Wrappee

    dtk3DItem *item(void);
    void setItem(dtk3DItem *item);

#pragma mark -
#pragma mark Properties getters
    
    QColor color(void);
    qreal x(void);
    qreal y(void);
    qreal z(void);
    bool wireframe(void);

#pragma mark -
#pragma mark Properties setters
    
    void setColor(const QColor& color);
    void setX(qreal x);
    void setY(qreal y);
    void setZ(qreal z);
    void setWireframe(bool on);
    
#pragma mark -
#pragma mark Invokables

public slots:
    void translate(qreal dx, qreal dy, qreal dz);

signals:
    void initialized(void);

private:
    dtk3DQuickItemPrivate *d;
};

QML_DECLARE_TYPE(dtk3DQuickItem)
