/* dtk3DMesh.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Sun Mar 24 16:42:30 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Mar 26 21:35:44 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 67
 */

/* Change Log:
 * 
 */

#include "dtk3DMesh.h"

#include <Qt3D/QGLBuilder>

class dtk3DMeshPrivate
{
public:
    QGeometryData data;
};

dtk3DMesh::dtk3DMesh(QObject *parent) : dtk3DItem(parent), d(new dtk3DMeshPrivate)
{

}

dtk3DMesh::~dtk3DMesh(void)
{
    delete d;

    d = NULL;
}

QBox3D dtk3DMesh::boundingBox(void) const
{
    return d->data.boundingBox();
}

QGeometryData& dtk3DMesh::data(void) const
{
    return d->data;
}

void dtk3DMesh::read(const QString& path)
{
    Q_UNUSED(path);
}

void dtk3DMesh::write(const QString& path)
{
    Q_UNUSED(path);
}

void dtk3DMesh::initialize(QGLView *view, QGLPainter *painter)
{
    dtk3DItem::initialize(view, painter);
}

void dtk3DMesh::paint(QGLView *view, QGLPainter *painter)
{
    Q_UNUSED(view);

    // Here comes the interesting part -- see PoC
}
