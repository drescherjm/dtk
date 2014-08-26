// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

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

//
// dtkDistributedSettings.cpp ends here
