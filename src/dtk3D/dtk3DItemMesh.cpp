/* dtk3DItemMesh.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Sun Mar 24 16:42:30 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Mar 25 18:58:48 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 49
 */

/* Change Log:
 * 
 */

#include "dtk3DItemMesh.h"

#include <Qt3D/QGLBuilder>

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

void dtk3DItemMesh::initialize(QGLView *view, QGLPainter *painter)
{
    QGLBuilder builder;
    builder << QGL::Faceted;
    builder << this->geometry();

    this->setNode(builder.finalizedSceneNode());

    dtk3DItem::initialize(view, painter);
}

void dtk3DItemMesh::read(const QString& path)
{
    Q_UNUSED(path);
}

void dtk3DItemMesh::write(const QString& path)
{
    Q_UNUSED(path);
}
