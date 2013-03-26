/* dtk3DItemMesh.h ---
 * 
 * Author: Julien Wintz
 * Created: Sun Mar 24 16:41:03 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Mar 25 14:53:43 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 36
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtk3DItem.h"

#include <dtkCore>

class dtk3DItemMeshPrivate;

class dtk3DItemMesh : public dtk3DItem
{
    Q_OBJECT

public:
             dtk3DItemMesh(QObject *parent = 0);
    virtual ~dtk3DItemMesh(void);

#pragma mark -
#pragma mark Management

    void initialize(QGLView *view, QGLPainter *painter);

#pragma mark -
#pragma mark Geometry
    
    virtual const QGeometryData& geometry(void) const = 0;

#pragma mark -
#pragma mark I/O

    virtual void  read(const QString& path);
    virtual void write(const QString& path);

private:
    dtk3DItemMeshPrivate *d;
};

DTK_DECLARE_OBJECT(dtk3DItemMesh*)
DTK_DECLARE_PLUGIN(dtk3DItemMesh)
DTK_DECLARE_PLUGIN_FACTORY(dtk3DItemMesh)
DTK_DECLARE_PLUGIN_MANAGER(dtk3DItemMesh)
