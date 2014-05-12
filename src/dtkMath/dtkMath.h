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

class dtkMatrix;
class dtkMatrixPluginFactory;
class dtkMatrixPluginManager;

namespace dtkMath
{
    namespace matrix {
        dtkMatrixPluginFactory& pluginFactory(void);
        dtkMatrixPluginManager& pluginManager(void);
    }
}

//
// dtkMath.h ends here
