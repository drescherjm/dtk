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

#include <dtkDistributedExport>

#include <QtCore>

class DTKDISTRIBUTED_EXPORT dtkDistributedSettings : public QSettings
{
public:
    explicit dtkDistributedSettings(void);
    virtual ~dtkDistributedSettings(void);
};

//
// dtkDistributedSettings.h ends here
