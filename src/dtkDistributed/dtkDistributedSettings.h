/* dtkDistributedSettings.h --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb 11 14:50:18 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb 11 14:52:11 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>

class dtkDistributedSettings : public QSettings
{
public:
    explicit dtkDistributedSettings(void);
    virtual ~dtkDistributedSettings(void);
};
