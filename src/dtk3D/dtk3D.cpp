/* dtk3D.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Mar 25 09:23:28 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Apr  9 12:34:45 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 34
 */

/* Change Log:
 * 
 */

#include "dtk3D.h"
#include "dtk3DMesh.h"

namespace dtk3D
{
    namespace mesh
    {
	namespace _private {
	    dtk3DMeshPluginFactory factory;
	    dtk3DMeshPluginManager manager;
	}
	
	dtk3DMeshPluginFactory& pluginFactory(void) {
	    return _private::factory;
	}
	
	dtk3DMeshPluginManager& pluginManager(void) {
	    return _private::manager;
	}
    }
}
