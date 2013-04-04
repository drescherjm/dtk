/* dtk3DQuickItem.h ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr  3 14:56:54 2013 (+0200)
 * Version: 
 * Last-Updated: Thu Apr  4 10:07:04 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 26
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

public:
     dtk3DQuickItem(QObject *parent = 0);
    ~dtk3DQuickItem(void);

public:
    dtk3DItem *item(void);

private:
    dtk3DQuickItemPrivate *d;
};

QML_DECLARE_TYPE(dtk3DQuickItem)
