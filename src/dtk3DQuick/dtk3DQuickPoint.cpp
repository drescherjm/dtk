/* dtk3DQuickPoint.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Fri Apr  5 13:44:29 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr  5 13:58:51 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Change Log:
 * 
 */

#include "dtk3DQuickPoint"

#include <Qt3D/QGLBuilder>
#include <Qt3D/QGraphicsScale3D>
#include <Qt3D/QGLSceneNode>
#include <Qt3D/QGLSphere>

dtk3DQuickPoint::dtk3DQuickPoint(QObject *parent) : dtk3DQuickItem(parent)
{
    QGLBuilder builder;
    builder << QGL::Faceted;
    builder << QGLSphere();

    QGraphicsScale3D *transform = new QGraphicsScale3D;
    transform->setScale(QVector3D(0.25, 0.25, 0.25));

    QGLSceneNode *node = builder.finalizedSceneNode();
    node->setObjectName("point");
    node->addTransform(transform);
    node->setEffect(QGL::LitMaterial);

    this->item()->addNode(node);
}
