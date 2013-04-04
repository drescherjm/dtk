/* dtk3DItem.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Sat Mar 30 13:55:00 2013 (+0100)
 * Version: 
 * Last-Updated: Thu Apr  4 11:31:56 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 134
 */

/* Change Log:
 * 
 */

#include "dtk3DItem.h"
#include "dtk3DView.h"

#include <Qt3D/QGraphicsRotation3D>
#include <Qt3D/QGraphicsScale3D>
#include <Qt3D/QGraphicsTranslation3D>

#include <QtGui>
#include <QtCore>

// ///////////////////////////////////////////////////////////////////
// dtk3DItemPrivate
// ///////////////////////////////////////////////////////////////////

class dtk3DItemPrivate
{
public:
    void dump(void);
    void dump(QGLSceneNode *node, bool detailed, int indent = 0, const QSet<QGLSceneNode *> &loop = QSet<QGLSceneNode *>());

public:
    dtk3DItem *q;

public:
    dtk3DItem::Flags flags;

public:
           int p_id;
           int i_id;
    static int g_id;

public:
    bool hovered;
    bool rotated;
    bool panned;

public:
    QPoint last;

public:
    QGLMaterial      *material;
    QGLMaterial *hoverMaterial;

public:
    QMatrix4x4  local_transform;
    QMatrix4x4 global_transform;

public:
    QGLView *view;
};

int dtk3DItemPrivate::g_id = 0;

// ///////////////////////////////////////////////////////////////////
// dtk3DItem
// ///////////////////////////////////////////////////////////////////

dtk3DItem::dtk3DItem(QObject *parent) : QGLSceneNode(parent), d(new dtk3DItemPrivate)
{
    d->q = this;
    d->p_id = -1;
    d->i_id = -1;
    d->flags = 0;
    d->panned = false;
    d->rotated = false;
    d->hovered = false;
    d->material = new QGLMaterial(this);
    d->material->setColor(qRgb(170, 202, 0));
    d->hoverMaterial = new QGLMaterial(this);
    d->hoverMaterial->setColor(qRgb(255, 186, 210));
    d->view = NULL;

    this->setMaterial(d->material);
}

dtk3DItem::~dtk3DItem(void)
{
    delete d;
}

dtk3DItem::Flags dtk3DItem::flags(void) const
{
    return d->flags;
}

void dtk3DItem::setFlags(dtk3DItem::Flags flags)
{
    d->flags = flags;
}

void dtk3DItem::setFlag(dtk3DItem::Flag flag, bool value)
{
    dtk3DItem::Flags flags = d->flags;

    if (value)
	flags |=  flag;
    else
	flags &= ~flag;

    d->flags = flags;
}

QMatrix4x4 dtk3DItem::localTransform(void)
{
    return d->local_transform;
}

QMatrix4x4 dtk3DItem::globalTransform(void)
{
    return d->global_transform;
}

QVector3D dtk3DItem::localPosition(void)
{
    return d->local_transform.map(QVector4D(0.0, 0.0, 0.0, 1.0)).toVector3D();
}

QVector3D dtk3DItem::globalPosition(void)
{
    return d->global_transform.map(QVector4D(0.0, 0.0, 0.0, 1.0)).toVector3D();
}

void dtk3DItem::translate(const QVector3D& translation)
{
    d->local_transform.translate(translation);

    this->update();

    if (d->view)
	d->view->update();
}

void dtk3DItem::rotate(const QVector3D& axis, qreal angle)
{
    d->local_transform.rotate(angle, axis);

    this->update();

    if (d->view)
	d->view->update();
}

const QVector3D dtk3DItem::mapToItem(const QPoint& point)
{
    qreal w = qreal(d->view->width());
    qreal h = qreal(d->view->height());

    QMatrix4x4 objt = d->global_transform;
    QMatrix4x4 modl = d->view->camera()->modelViewMatrix();
    QMatrix4x4 proj = d->view->camera()->projectionMatrix(w/h);
    QMatrix4x4 trsf = (proj * modl * objt).inverted();

    qreal x = +(qreal(point.x())*2-w)/w;
    qreal y = -(qreal(point.y())*2-h)/h;

    return trsf.map(QVector3D(x, y, 0.0));
}

const QVector3D dtk3DItem::mapToItem(const QVector3D& point)
{
    QMatrix4x4 objt = d->global_transform;
    QMatrix4x4 modl = d->view->camera()->modelViewMatrix();
    QMatrix4x4 trsf = (modl * objt).inverted();

    return trsf.mapVector(point);
}

QColor dtk3DItem::color(void)
{
    return d->material->ambientColor().lighter();
}

void dtk3DItem::setColor(const QColor& color)
{
    d->material->setColor(color);    
}

void dtk3DItem::initialize(QGLPainter *painter, QGLView *view)
{
    Q_UNUSED(painter);

    this->update();

    d->view = view;
}

void dtk3DItem::draw(QGLPainter *painter)
{
    if(d->flags & dtk3DItem::Hidden)
	return;
    
    painter->clearAttributes();

    if(d->flags & dtk3DItem::Interactive) {

	if (d->i_id == -1) {
	    if (d->p_id == -1)
		d->view->registerObject((d->i_id = d->p_id = d->g_id++), this);
	    else
		d->i_id = d->p_id;
	}

	if(d->hovered)
	    this->setMaterial(d->hoverMaterial);
	else
	    this->setMaterial(d->material);

    } else {
	d->i_id = -1;
    }

    painter->modelViewMatrix().push();
    painter->modelViewMatrix() *= d->local_transform;
    painter->setObjectPickId(d->i_id);
    QGLSceneNode::draw(painter);
    painter->modelViewMatrix().pop();
}

void dtk3DItem::update(void)
{
    dtk3DItem *parent = NULL;

    if (this->parent())
	parent = qobject_cast<dtk3DItem *>(this->parent());

    if (parent)
	d->global_transform = parent->globalTransform() * d->local_transform;
    else
	d->global_transform = d->local_transform;
}

bool dtk3DItem::event(QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
	this->mousePressEvent(reinterpret_cast<QMouseEvent *>(event));

    if (event->type() == QEvent::MouseButtonRelease)
	this->mouseReleaseEvent(reinterpret_cast<QMouseEvent *>(event));

    if (event->type() == QEvent::MouseMove)
	this->mouseMoveEvent(reinterpret_cast<QMouseEvent *>(event));

    if (event->type() == QEvent::Enter)
	this->enterEvent(event);

    if (event->type() == QEvent::Leave)
	this->leaveEvent(event);

    return QObject::event(event);
}

void dtk3DItem::enterEvent(QEvent *event)
{
    Q_UNUSED(event);

    d->hovered = true;

    d->view->update();
}

void dtk3DItem::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

    d->hovered = false;

    d->view->update();
}

void dtk3DItem::mouseMoveEvent(QMouseEvent *event)
{
    if(!(d->rotated || d->panned))
	return;

    if (d->panned)
	this->mouseTranslateEvent(event);

    if (d->rotated)
	this->mouseRotateEvent(event);
}

void dtk3DItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
	return;

    d->panned  = (event->button() && (event->modifiers() & Qt::ShiftModifier));
    d->rotated = (event->button() && (event->modifiers()  ==  Qt::NoModifier));

    d->last = d->view->mapFromGlobal(event->globalPos());
}

void dtk3DItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
	return;

    d->panned = false;
    d->rotated = false;
    d->last = QPoint();

    emit clicked();
}

void dtk3DItem::mouseTranslateEvent(QMouseEvent *event)
{
    QPoint current = d->view->mapFromGlobal(event->globalPos());
    
    QVector3D start = this->mapToItem(d->last);
    QVector3D currt = this->mapToItem(current);
    QVector3D delta = currt - start;

    this->translate(delta);

    d->last = current;
}

void dtk3DItem::mouseRotateEvent(QMouseEvent *event)
{
    auto arc_vector = [this](qreal x, qreal y, qreal w, qreal h) -> QVector3D {
	
	QVector3D p;
	p.setX(x/w * 2.0 - 1.0);
	p.setY(y/h * 2.0 - 1.0);
	p.setZ(0.0);
	p.setY(-p.y());
	
	qreal s = p.x()*p.x() + p.y()*p.y();
	
	if(s <= 1)
	    p.setZ(sqrt(1-s));
	else
	    p.normalize();
	
	return p;
    };
    
    qreal w = qreal(d->view->width());
    qreal h = qreal(d->view->height());

    QPoint current = d->view->mapFromGlobal(event->globalPos());
    QPoint scenter = QPoint(w/2, h/2);
    QPoint ocenter = qobject_cast<dtk3DView *>(d->view)->mapToScreen(this->globalPosition());
    QPoint ooffset = scenter - ocenter;
    QPoint a = d->last + ooffset;
    QPoint b = current + ooffset;
    
    QVector3D va = arc_vector(a.x(), a.y(), w, h).normalized();
    QVector3D vb = arc_vector(b.x(), b.y(), w, h).normalized();
    QVector3D ax = this->mapToItem(QVector3D::crossProduct(va, vb)).normalized();
	
    qreal ag = acos(qMin(1.0f, QVector3D::dotProduct(va, vb)))*180.0/M_PI;

    this->rotate(ax, ag);

    d->last = current;
}

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

QDebug operator<<(QDebug dbg, dtk3DItem *item)
{
    item->d->dump();

    return dbg;
}

QDebug operator<<(QDebug dbg, const dtk3DItem& item)
{
    item.d->dump();

    return dbg;
}

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

void dtk3DItemPrivate::dump(void)
{
    return this->dump(q, true);
}

void dtk3DItemPrivate::dump(QGLSceneNode *node, bool detailed, int indent, const QSet<QGLSceneNode *> &loop)
{
    QSet<QGLSceneNode *> lp = loop;
    lp.insert(node);

    QString ind;
    ind.fill(QLatin1Char(' '), indent * 4);

    if (detailed) {
        qDebug("\n%s ======== Node: %p - %s =========", qPrintable(ind), node, qPrintable(node->objectName()));
    } else {
        qDebug("\n%s Node: %p - %s", qPrintable(ind), node, qPrintable(node->objectName()));
        return;
    }

    qDebug("%s start: %d   count: %d   children:", qPrintable(ind), node->start(), node->count()); {

        QList<QGLSceneNode*> children = node->children();
        QList<QGLSceneNode*>::const_iterator it = children.constBegin();
        for (int i = 0; it != children.constEnd(); ++it, ++i)
            qDebug("%s    %d: %p  ", qPrintable(ind), i, *it);
    }

    if (!node->position().isNull()) {
        QVector3D p = node->position();
        qDebug("%s position: (%0.4f, %0.4f, %0.4f)", qPrintable(ind), p.x(), p.y(), p.z());
    }
    
    if (node->localTransform().isIdentity()) {

        qDebug("%s local transform: identity", qPrintable(ind));

    } else {

        qDebug("%s local transform:", qPrintable(ind));

        QMatrix4x4 m = node->localTransform();
        for (int i = 0; i < 4; ++i)
            qDebug("%s     %0.4f   %0.4f   %0.4f   %0.4f", qPrintable(ind), m(i, 0), m(i, 1), m(i, 2), m(i, 3));
    }

    QList<QQuickQGraphicsTransform3D*> tx = node->transforms();

    if (tx.size() > 0)
        qDebug("%s transforms list:", qPrintable(ind));

    for (int i = 0; i < tx.size(); ++i) {
        const QMetaObject *obj = tx.at(i)->metaObject();
        qDebug("%s     %s", qPrintable(ind), obj->className());
    }

    if (!node->geometry().isEmpty()) {
        qDebug("%s geometry: %d indexes, %d vertices", qPrintable(ind), node->geometry().count(), node->geometry().count(QGL::Position));
    } else {
        qDebug("%s geometry: NULL", qPrintable(ind));
    }

    if (node->materialIndex() != -1) {

        qDebug("%s material: %d", qPrintable(ind), node->materialIndex());

        QGLMaterial *mat = node->material();
        QGLMaterialCollection *pal = node->palette().data();

        if (pal)
            qDebug("%s palette: %p", qPrintable(ind), pal);
        else
            qDebug("%s no palette", qPrintable(ind));

        if (pal) {
            mat = pal->material(node->materialIndex());

            if (mat)
                qDebug("%s mat name from pal: %s ", qPrintable(ind), qPrintable(pal->material(node->materialIndex())->objectName()));
            else
                qDebug("%s indexed material %d does not exist in palette!", qPrintable(ind), node->materialIndex());
        }

        if (mat) {

            QString mat_spx = QString(QLatin1String(" Amb: %1 - Diff: %2 - Spec: %3 - Shin: %4"))
                    .arg((mat->ambientColor().name()))
                    .arg(mat->diffuseColor().name())
                    .arg(mat->specularColor().name())
                    .arg(mat->shininess());

            if (mat->objectName().isEmpty())
                qDebug("%s    material pointer %p: %s", qPrintable(ind), mat, qPrintable(mat_spx));
            else
                qDebug("%s    \"%s\": %s", qPrintable(ind), qPrintable(mat->objectName()),  qPrintable(mat_spx));

            for (int i = 0; i < mat->textureLayerCount(); ++i) {

                if (mat->texture(i) != 0) {

                    QGLTexture2D *tex = mat->texture(i);

                    if (tex->objectName().isEmpty())
                        qDebug("%s         texture %p", qPrintable(ind), tex);
                    else
                        qDebug("%s         texture %s", qPrintable(ind),
                                qPrintable(tex->objectName()));

                    QSize sz = tex->size();

                    qDebug(" - size: %d (w) x %d (h)", sz.width(), sz.height());
                }
            }

        } else {

            qDebug("%s - could not find indexed material!!", qPrintable(ind));
        }

    } else {

        qDebug("%s material: NONE", qPrintable(ind));

    }

    if (node->hasEffect()) {

        if (node->userEffect()) {

            qDebug("%s user effect %p", qPrintable(ind), node->userEffect());

        } else {

            switch (node->effect())
            {
            case QGL::FlatColor:
                qDebug("%s flat color effect", qPrintable(ind)); break;
            case QGL::FlatPerVertexColor:
                qDebug("%s flat per vertex color effect", qPrintable(ind)); break;
            case QGL::FlatReplaceTexture2D:
                qDebug("%s flat replace texture 2D effect", qPrintable(ind)); break;
            case QGL::FlatDecalTexture2D:
                qDebug("%s flat decal texture 2D effect", qPrintable(ind)); break;
            case QGL::LitMaterial:
                qDebug("%s lit material effect", qPrintable(ind)); break;
            case QGL::LitDecalTexture2D:
                qDebug("%s lit decal texture 2D effect", qPrintable(ind)); break;
            case QGL::LitModulateTexture2D:
                qDebug("%s lit modulate texture 2D effect", qPrintable(ind)); break;
            }

        }

    } else {

        qDebug("%s no effect set", qPrintable(ind));

    }

    QList<QGLSceneNode*> children = node->children();
    QList<QGLSceneNode*>::const_iterator it = children.constBegin();

    for ( ; it != children.constEnd(); ++it)
        if (!lp.contains(*it))
            this->dump(*it, detailed, indent + 1);
}
