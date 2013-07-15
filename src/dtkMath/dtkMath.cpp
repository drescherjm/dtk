/* dtkMath.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Jul 15 16:15:50 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Jul 15 16:16:42 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Change Log:
 * 
 */

#include "dtkMath.h"
#include "dtkMatrix.h"

namespace dtkMath
{
    namespace matrix
    {
	namespace _private {
	    dtkMatrixPluginFactory factory;
	    dtkMatrixPluginManager manager;
	}
	
	dtkMatrixPluginFactory& pluginFactory(void) {
	    return _private::factory;
	}
	
	dtkMatrixPluginManager& pluginManager(void) {
	    return _private::manager;
	}
    }
}
