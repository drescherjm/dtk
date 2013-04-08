/* dtk3DMesh.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Sun Mar 24 16:42:30 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Apr  9 01:29:47 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 142
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

void dtk3DMesh::draw(QGLPainter *painter)
{
    if (!d->data.count())
	return;

    painter->clearAttributes();
    if (d->data.colors().count())
    	painter->setStandardEffect(QGL::FlatPerVertexColor);
    else
    	painter->setStandardEffect(QGL::FlatColor);
    painter->setVertexAttribute(QGL::Position, d->data.vertices());
    if (d->data.colors().count())
    	painter->setVertexAttribute(QGL::Color, d->data.colors());
    else
    	painter->setColor(Qt::darkGreen);
    painter->setVertexAttribute(QGL::Normal, d->data.normals());
    painter->draw(QGL::Triangles, d->data.count());
}
