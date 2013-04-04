/* dtk3DQuickItem.h ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr  3 14:56:54 2013 (+0200)
 * Version: 
 * Last-Updated: Thu Apr  4 11:28:49 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 45
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

public:
     dtk3DQuickItem(QObject *parent = 0);
    ~dtk3DQuickItem(void);

#pragma mark -
#pragma mark Wrappee

    dtk3DItem *item(void);

#pragma mark -
#pragma mark Properties getters
    
    QColor color(void);
    qreal x(void);
    qreal y(void);
    qreal z(void);

#pragma mark -
#pragma mark Properties setters
    
    void setColor(const QColor& color);
    void setX(qreal x);
    void setY(qreal y);
    void setZ(qreal z);
    
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
