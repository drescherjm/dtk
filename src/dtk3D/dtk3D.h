/* dtk3D.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Mar 25 09:21:47 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Mar 25 09:33:31 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Change Log:
 * 
 */

#pragma once

class dtk3DItemMeshPlugin;
class dtk3DItemMeshPluginFactory;
class dtk3DItemMeshPluginManager;

namespace dtk3D
{
    namespace mesh {
	dtk3DItemMeshPluginFactory& pluginFactory(void);
	dtk3DItemMeshPluginManager& pluginManager(void);
    }
}
