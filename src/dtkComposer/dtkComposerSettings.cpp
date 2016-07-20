/* dtkComposerSettings.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2016 - Nicolas Niclausse, Inria.
 * Created: 2016/02/15 12:39:05
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */



#include "dtkComposerSettings.h"
#include <dtkLog>


dtkComposerSettings::dtkComposerSettings(void) : QSettings(QSettings::IniFormat, QSettings::UserScope, "inria", "dtk-composer")
{
    this->beginGroup("extension");

    if (!this->allKeys().contains("plugins")) {
        this->setValue("plugins", QString());
    }

    this->sync();
    this->endGroup();
}

dtkComposerSettings::~dtkComposerSettings(void)
{

}


//
// dtkComposerSettings.cpp ends here
