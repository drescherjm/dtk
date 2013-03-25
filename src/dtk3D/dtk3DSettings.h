/* dtk3DSettings.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Mar 25 15:02:26 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Mar 25 15:02:44 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>

class dtk3DSettings : public QSettings
{
public:
    explicit dtk3DSettings(void);
    virtual ~dtk3DSettings(void);
};
