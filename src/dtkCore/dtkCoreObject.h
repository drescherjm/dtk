/* dtkCoreObject.h --- 
 * 
 * Author: Julien Wintz
 * Created: Thu Feb 28 17:59:25 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Mar 25 13:11:37 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 5
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>

class dtkCoreObject : public QObject 
{
    Q_OBJECT

public:
    virtual dtkCoreObject *clone(void) const = 0;
};
