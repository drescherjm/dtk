/* dtkDistributedSettings.cpp --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb 11 14:50:53 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb 11 15:34:32 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Change Log:
 * 
 */

#include "dtkDistributedSettings.h"

dtkDistributedSettings::dtkDistributedSettings(void) : QSettings(QSettings::IniFormat, QSettings::UserScope, "inria", "dtk-distributed")
{
    this->beginGroup("communicator");
    if(!this->allKeys().contains("plugins"))
	this->setValue("plugins", QString());
    this->sync();
    this->endGroup();
}

dtkDistributedSettings::~dtkDistributedSettings(void)
{

}
