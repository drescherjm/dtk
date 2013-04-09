/* dtk3DMesh.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Sun Mar 24 16:42:30 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Apr  9 18:07:05 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 228
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

public:
    QGLSceneNode *node;

public:
    int count;
};

dtk3DMesh::dtk3DMesh(QObject *parent) : dtk3DItem(parent), d(new dtk3DMeshPrivate)
{
    d->count = 0;
    d->node = NULL;
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

    if (d->count != d->data.count()) {

	if (d->node) {
	    this->removeNode(d->node);
	    delete d->node;
	}

	QGLBuilder builder;
	builder << QGL::Faceted;
	builder << d->data;
	
	d->node = builder.finalizedSceneNode();
	d->count = d->data.count();

	this->addNode(d->node);	
    }

    dtk3DItem::draw(painter);
}
