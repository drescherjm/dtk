/* dtk3DSettings.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Mar 25 15:02:52 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Mar 25 15:03:09 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Change Log:
 * 
 */

#include "dtk3DSettings.h"

dtk3DSettings::dtk3DSettings(void) : QSettings(QSettings::IniFormat, QSettings::UserScope, "inria", "dtk-3D")
{
    this->beginGroup("mesh");
    if(!this->allKeys().contains("plugins"))
	this->setValue("plugins", QString());
    this->sync();
    this->endGroup();
}

dtk3DSettings::~dtk3DSettings(void)
{

}
