/* dtkCoreSettings.cpp --- 
 * 
 * Author: Julien Wintz
 * Created: Fri Feb  8 16:53:22 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Feb  8 17:05:32 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Change Log:
 * 
 */

#include "dtkCoreSettings.h"

dtkCoreSettings::dtkCoreSettings(void) : QSettings("inria", "dtk")
{
    this->setDefaultFormat(QSettings::IniFormat);
}
