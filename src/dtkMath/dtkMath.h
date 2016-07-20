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

#include "dtkMathExport.h"

#include <QtCore>

class dtkMatrix;
class dtkMatrixPluginFactory;
class dtkMatrixPluginManager;

namespace dtkMath {
    namespace matrix {
        DTKMATH_EXPORT dtkMatrixPluginFactory& pluginFactory(void);
        DTKMATH_EXPORT dtkMatrixPluginManager& pluginManager(void);
    }
}

//
// dtkMath.h ends here
