/* dtk3DQuickItem.h ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr  3 14:56:54 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr  3 16:18:31 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 21
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtk3D>

#include <QtCore>
#include <QtQuick>

class dtk3DQuickItem : public dtk3DItem
{
    Q_OBJECT

public:
     dtk3DQuickItem(QObject *parent = 0);
    ~dtk3DQuickItem(void);
};

QML_DECLARE_TYPE(dtk3DQuickItem)
