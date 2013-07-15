/* dtkMath.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Jul 15 16:14:50 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Jul 15 16:18:59 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkMath.h"
#include "dtkMatrix.h"

namespace dtkMath
{
    namespace matrix {
	dtkMatrixPluginFactory& pluginFactory(void);
	dtkMatrixPluginManager& pluginManager(void);
    }
}
