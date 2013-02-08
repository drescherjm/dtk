/* dtkCoreSettings.h --- 
 * 
 * Author: Julien Wintz
 * Created: Fri Feb  8 16:51:14 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Feb  8 16:53:10 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>

class dtkCoreSettings : public QSettings
{
public:
    explicit dtkCoreSettings(void);
};
