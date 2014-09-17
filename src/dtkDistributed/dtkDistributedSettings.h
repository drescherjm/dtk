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

#pragma once

#include "dtkDistributedExport.h"

#include <QtCore>

class DTKDISTRIBUTED_EXPORT dtkDistributedSettings : public QSettings
{
public:
     dtkDistributedSettings(void);
    ~dtkDistributedSettings(void);
};

//
// dtkDistributedSettings.h ends here
