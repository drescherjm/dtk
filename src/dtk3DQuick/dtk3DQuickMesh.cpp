/* dtk3DQuickMesh.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Fri Apr  5 10:59:32 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Apr  9 17:58:33 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 110
 */

/* Change Log:
 * 
 */

#include "dtk3DQuickMesh.h"

#include <dtk3D>

class dtk3DQuickMeshPrivate
{
public:
    void update(void);

public:
    dtk3DQuickMesh *q;

public:
    dtk3DMesh *mesh;

public:
    QString file;
    QString type;
};

dtk3DQuickMesh::dtk3DQuickMesh(QObject *parent) : dtk3DQuickItem(parent), d(new dtk3DQuickMeshPrivate)
{
    d->q = this;
    d->mesh = NULL;
}

dtk3DQuickMesh::~dtk3DQuickMesh(void)
{
    delete d;
}

const QString& dtk3DQuickMesh::file(void)
{
    return d->file;
}

const QString& dtk3DQuickMesh::type(void)
{
    return d->type;
}

void dtk3DQuickMesh::setFile(const QString& file)
{
    d->file = file;

    d->update();
}

void dtk3DQuickMesh::setType(const QString& type)
{
    d->type = type;

    d->update();
}

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

void dtk3DQuickMeshPrivate::update(void)
{
    if(!this->mesh) {

	QString path;

	dtk3DSettings settings;
	settings.beginGroup("mesh");
	path = settings.value("plugins").toString();
	settings.endGroup();

	dtk3D::mesh::pluginManager().initialize(path);

	if((this->mesh = dtk3D::mesh::pluginFactory().create(type))) {
	    this->mesh->setEffect(QGL::LitMaterial);
	    q->setItem(this->mesh);
	}
    }

    if (this->mesh) {
	this->mesh->read(this->file);	
    }
}
