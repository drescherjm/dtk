/* dtk3DQuickPoint.h ---
 * 
 * Author: Julien Wintz
 * Created: Fri Apr  5 13:41:55 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr  5 13:56:56 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 12
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtk3DQuickItem.h"

#include <QtCore>
#include <QtQuick>

class dtk3DQuickPoint : public dtk3DQuickItem
{
    Q_OBJECT

public:
    dtk3DQuickPoint(QObject *parent = 0);
};

QML_DECLARE_TYPE(dtk3DQuickPoint)
