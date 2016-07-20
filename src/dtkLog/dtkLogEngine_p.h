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

#include <QtCore>

class dtkLogEnginePrivate
{
public:
    dtkLogEnginePrivate(void) : level(dtkLog::Info), stream(&buffer), custom(false) {}

public:
    void write(void);

public:
    dtkLog::Level level;

public:
    QDebug stream;

public:
    QString buffer;

public:
    bool custom;
};

//
// dtkLogEngine_p.h ends here
