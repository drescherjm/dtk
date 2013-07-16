/* dtkMath.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Jul 15 16:14:50 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Jul 16 11:33:26 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 17
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
