/* dtk3DItemMesh.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Sun Mar 24 16:42:30 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Mar 25 09:35:47 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Change Log:
 * 
 */

#include "dtk3DItemMesh.h"

class dtk3DItemMeshPrivate
{
public:

};

dtk3DItemMesh::dtk3DItemMesh(QObject *parent) : dtk3DItem(parent), d(new dtk3DItemMeshPrivate)
{

}

dtk3DItemMesh::~dtk3DItemMesh(void)
{
    delete d;

    d = NULL;
}

