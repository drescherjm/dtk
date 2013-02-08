/* dtkCoreSettings.cpp --- 
 * 
 * Author: Julien Wintz
 * Created: Fri Feb  8 16:53:22 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Feb  8 16:58:30 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Change Log:
 * 
 */

#include "dtkCoreSettings.h"

dtkCoreSettings::dtkCoreSettings(void) : QSettings(QSettings::IniFormat, QSettings::UserScope, "inria", "dtk")
{

}
