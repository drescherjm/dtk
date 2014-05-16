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

namespace dtkLog {

    enum HandlerFlag {
        Console = 0x00,
           File = 0x01
    };

    Q_DECLARE_FLAGS(HandlerFlags, HandlerFlag);
    Q_DECLARE_OPERATORS_FOR_FLAGS(HandlerFlags);
};

//
// dtkLog.h ends here
