/* dtk3DMesh.h ---
 * 
 * Author: Julien Wintz
 * Created: Sun Mar 24 16:41:03 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Apr  9 01:34:58 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 54
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtk3DItem.h"

#include <dtkCore>

class dtk3DMeshPrivate;

class dtk3DMesh : public dtk3DItem
{
    Q_OBJECT

public:
             dtk3DMesh(QObject *parent = 0);
    virtual ~dtk3DMesh(void);

#pragma mark -
#pragma mark Geometric attributes

    QBox3D boundingBox(void) const;

#pragma mark -
#pragma mark Geometry data
    
    QGeometryData& data(void) const;

#pragma mark -
#pragma mark I/O

    virtual void  read(const QString& path);
    virtual void write(const QString& path);

protected:
    virtual void draw(QGLPainter *painter);

private:
    dtk3DMeshPrivate *d;
};

DTK_DECLARE_OBJECT(dtk3DMesh*)
DTK_DECLARE_PLUGIN(dtk3DMesh)
DTK_DECLARE_PLUGIN_FACTORY(dtk3DMesh)
DTK_DECLARE_PLUGIN_MANAGER(dtk3DMesh)
