/* dtkComposerSceneNodeComposite.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 14:01:41 2012 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. sept. 13 15:56:37 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 914
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeComposite.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerSceneNote.h"
#include "dtkComposerScenePort.h"
#include "dtkComposerWriter.h"
#include "dtkComposerNodeRemote.h"

#include <dtkLog/dtkLog.h>

#include <dtkConfig.h>

#include <dtkDistributed/dtkDistributedController.h>
#include <dtkDistributed/dtkDistributedMimeData.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeComposite
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodeCompositePrivate
{
public:
    dtkComposerSceneNodeComposite *former;

public:
    dtkComposerSceneNoteList notes;
    dtkComposerSceneNodeList nodes;
    dtkComposerSceneEdgeList edges;

public:
    QPointF offset;
    QPointF unreveal_pos;

public:
    QRectF rect;
    QRectF unreveal_rect;

public:
    bool root;

public:
    dtkComposerWriter writer;

public:
    bool flattened;
    bool entered;
    bool revealed;
    bool obfuscated;
};

dtkComposerSceneNodeComposite::dtkComposerSceneNodeComposite(void) : dtkComposerSceneNode(), d(new dtkComposerSceneNodeCompositePrivate)
{
    d->former = NULL;

    d->rect = QRectF(0, 0, 150, 50);
    d->unreveal_rect = QRectF(0, 0, 150, 50);

    d->offset = QPointF(50, 50);

    d->root = false;

    d->flattened = false;
    d->entered = false;
    d->revealed = false;
    d->obfuscated = false;

    this->setAcceptDrops(true);
    this->layout();
    this->setTitle("Composite");
}

dtkComposerSceneNodeComposite::~dtkComposerSceneNodeComposite(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneNodeComposite::wrap(dtkComposerNode *wrapee)
{
    dtkComposerNodeComposite *composite = dynamic_cast<dtkComposerNodeComposite *>(wrapee);

    if(!composite)
        return;

    for(int i = 0; i < composite->receivers().count(); ++i) {
        
        dtkComposerScenePort *port = new dtkComposerScenePort(dtkComposerScenePort::Input, this);
        this->addInputPort(port);
        port->setLabel(composite->inputLabelHint(this->inputPorts().indexOf(port)));
        
    }

    for(int i = 0; i < composite->emitters().count(); ++i) {

        dtkComposerScenePort *port = new dtkComposerScenePort(dtkComposerScenePort::Output, this);
        this->addOutputPort(port);
        port->setLabel(composite->outputLabelHint(this->outputPorts().indexOf(port)));

    }

    dtkComposerSceneNode::wrap(wrapee);
}

void dtkComposerSceneNodeComposite::setFormer(dtkComposerSceneNodeComposite *former)
{
    d->former = former;
}

dtkComposerSceneNodeComposite *dtkComposerSceneNodeComposite::former(void)
{
    return d->former;
}

void dtkComposerSceneNodeComposite::addNote(dtkComposerSceneNote *note)
{
    d->notes << note;
}

void dtkComposerSceneNodeComposite::removeNote(dtkComposerSceneNote *note)
{
    d->notes.removeAll(note);
}

void dtkComposerSceneNodeComposite::addNode(dtkComposerSceneNode *node)
{
    d->nodes << node;
}

void dtkComposerSceneNodeComposite::removeNode(dtkComposerSceneNode *node)
{
    d->nodes.removeAll(node);
}

void dtkComposerSceneNodeComposite::addEdge(dtkComposerSceneEdge *edge)
{
    d->edges << edge;
}

void dtkComposerSceneNodeComposite::removeEdge(dtkComposerSceneEdge *edge)
{
    d->edges.removeAll(edge);
}

dtkComposerSceneNoteList dtkComposerSceneNodeComposite::notes(void)
{
    return d->notes;
}

dtkComposerSceneNodeList dtkComposerSceneNodeComposite::nodes(void)
{
    return d->nodes;
}

dtkComposerSceneEdgeList dtkComposerSceneNodeComposite::edges(void)
{
    return d->edges;
}

int dtkComposerSceneNodeComposite::inputDegree(dtkComposerScenePort *port)
{
    int degree = 0;

    foreach(dtkComposerSceneEdge *edge, d->edges)
        if(edge->destination() == port)
            degree++;

    return degree;
}

int dtkComposerSceneNodeComposite::outputDegree(dtkComposerScenePort *port)
{
    int degree = 0;

    foreach(dtkComposerSceneEdge *edge, d->edges)
        if(edge->source() == port)
            degree++;

    return degree;
}

bool dtkComposerSceneNodeComposite::entered(void)
{
    return d->entered;
}

bool dtkComposerSceneNodeComposite::flattened(void)
{
    return d->flattened || d->root;
}

// return true if node is visible, ie, it is flatenned and all it's parent are ( or entered )
bool dtkComposerSceneNodeComposite::visible(void)
{

    if (d->root)
        return true;

    if (dynamic_cast<dtkComposerSceneNodeControl *>(this->parent()))
        return dynamic_cast<dtkComposerSceneNodeComposite *>(this->parent()->parent())->visible();

    return (d->entered || ( d->flattened &&  (dynamic_cast<dtkComposerSceneNodeComposite *>(this->parent()))->visible())) ;
}

void dtkComposerSceneNodeComposite::enter(void)
{
    d->entered = true;

    this->reveal();
}

void dtkComposerSceneNodeComposite::leave(void)
{
    d->entered = false;

    this->unreveal();
}

void dtkComposerSceneNodeComposite::flatten(void)
{
    d->flattened = true;

    this->reveal();
}

void dtkComposerSceneNodeComposite::unflatten(void)
{
    d->flattened = false;

    this->unreveal();
}

void dtkComposerSceneNodeComposite::reveal(void)
{
    d->revealed = true;

    if (this->embedded()) {

        this->obfuscate();

    } else {

        this->resetPos(d->unreveal_pos, d->unreveal_rect);        
   
    }

    if (!this->embedded() && !d->entered && d->flattened) {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    } else {
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        this->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }

}

void dtkComposerSceneNodeComposite::unreveal(void)
{
    if(!d->flattened && !d->entered)
        d->revealed = false;

    if (this->embedded()) {
        foreach(dtkComposerSceneNode *node, d->nodes)
            node->setPos(d->unreveal_pos + (node->scenePos() - this->scenePos() - d->offset));
        
        foreach(dtkComposerSceneNote *note, d->notes)
            note->setPos(d->unreveal_pos + (note->scenePos() - this->scenePos() - d->offset));

        this->obfuscate();
    }

    if(!d->flattened && !this->embedded() && !d->entered) {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    } else {
        this->setFlag(QGraphicsItem::ItemIsMovable, false);
        this->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
}

void dtkComposerSceneNodeComposite::resetPos(const QPointF& pos, const QRectF& rect)
{
    QPointF center(0,0);
    QRectF box(0,0,0,0);

    if (!pos.isNull()) {
        center = pos + QPointF(0.5 * rect.width(), 0.5 * rect.height());
        foreach(dtkComposerSceneNode *node, d->nodes)
            box |= node->sceneBoundingRect();
    }
     
    foreach(dtkComposerSceneNode *node, d->nodes) {
        node->setPos(node->scenePos() + (center - box.center()));
        if (dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node))
            foreach(dtkComposerSceneNodeComposite *block, control->blocks()) {
                block->resetPos(block->scenePos(), block->sceneBoundingRect());
            }        
    }
        
    foreach(dtkComposerSceneNote *note, d->notes)
        note->setPos(note->scenePos() + (center - box.center())); 
}

void dtkComposerSceneNodeComposite::setUnrevealPos(const QPointF& pos)
{
    d->unreveal_pos = pos;
}

void dtkComposerSceneNodeComposite::setUnrevealRect(const QRectF& rect)
{
    d->unreveal_rect = rect;
}

QPointF dtkComposerSceneNodeComposite::unrevealPos(void) const
{
    return d->unreveal_pos;
}

QRectF dtkComposerSceneNodeComposite::unrevealRect(void) const
{
    return d->unreveal_rect;
}

bool dtkComposerSceneNodeComposite::root(void)
{
    return d->root;
}

void dtkComposerSceneNodeComposite::setRoot(bool root)
{
    d->root = root;
}

#include <float.h>

void dtkComposerSceneNodeComposite::layout(void)
{
    if (this->embedded() && !d->entered)
        goto port_location;
    
// /////////////////////////////////////////////////////////////////
// Rect calculation
// /////////////////////////////////////////////////////////////////

    if(!d->revealed) {

        d->rect = QRectF(0, 0, 150, 50);

    } else {

        qreal xmin, xmax;
        qreal ymin, ymax;

        this->boundingBox(xmin, xmax, ymin, ymax);

        qreal w = xmax-xmin;
        qreal h = ymax-ymin;

        w = qMax(w, 200.0) + 100;
        h = qMax(h, 100.0) + 100;

        d->rect = QRectF(QPointF(0, 0), QSizeF(w, h));

        this->setPos(xmin - 50, ymin - 50);

    }
    
// /////////////////////////////////////////////////////////////////
// Port location
// /////////////////////////////////////////////////////////////////

port_location:

    int header = 15;

    int port_margin_top = 10;
    int port_margin_bottom = 10;
    int port_margin_left = 10;
    int port_spacing = 10;

    for(int i = 0; i < this->inputPorts().count(); i++)
        this->inputPorts().at(i)->setPos(QPointF(port_margin_left, i*this->inputPorts().at(i)->boundingRect().height() + i*port_spacing + port_margin_top + header));
    
    for(int i = 0; i < this->outputPorts().count(); i++)
        this->outputPorts().at(i)->setPos(QPointF(d->rect.right() - port_margin_left - this->outputPorts().at(i)->boundingRect().width(), i*this->outputPorts().at(i)->boundingRect().height() + i*port_spacing + port_margin_top + header));

// /////////////////////////////////////////////////////////////////
// Redraw parent
// /////////////////////////////////////////////////////////////////

    if (dtkComposerSceneNodeComposite *parent = dynamic_cast<dtkComposerSceneNodeComposite *>(this->parent())) {
        if(!parent->root()) {
            if (parent->entered() || (parent->flattened() && !parent->embedded())) {
                parent->layout();
            }
        }
    }

    if(this->embedded())
        goto update;
   
// /////////////////////////////////////////////////////////////////
// Height calculation
// /////////////////////////////////////////////////////////////////

    if(!d->revealed) {

        if(this->inputPorts().count() || this->outputPorts().count()) {
            if(this->inputPorts().count() >= this->outputPorts().count())
                d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), this->inputPorts().count() * this->inputPorts().at(0)->boundingRect().height() + port_margin_top + port_margin_bottom + (this->inputPorts().count()-1) * port_spacing + header));
            else
                d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), this->outputPorts().count() * this->outputPorts().at(0)->boundingRect().height() + port_margin_top + port_margin_bottom + (this->outputPorts().count()-1) * port_spacing + header));        
        }
    }

update:
// /////////////////////////////////////////////////////////////////
// Update edges geometry
// /////////////////////////////////////////////////////////////////
    
    QRectF updateRect;

    foreach(dtkComposerSceneEdge *edge, this->inputEdges()) {
        edge->adjust();
        updateRect |= edge->boundingRect();
    }

    foreach(dtkComposerSceneEdge *edge, d->edges) {
        edge->adjust();
        updateRect |= edge->boundingRect();
    }
    
    foreach(dtkComposerSceneEdge *edge, this->outputEdges()) {
        edge->adjust();
        updateRect |= edge->boundingRect();
    }

    this->update(updateRect);
}

void dtkComposerSceneNodeComposite::resize(qreal width, qreal height)
{
    d->rect = QRectF(d->rect.topLeft(), QSizeF(width, height));
}

void dtkComposerSceneNodeComposite::obfuscate(void)
{
    QRectF rect = this->sceneBoundingRect();

    d->obfuscated = false;

    if (!d->entered) {

        foreach(dtkComposerSceneNode *node, d->nodes)
            if (!rect.contains(node->sceneBoundingRect()))
                d->obfuscated = true;
        
        foreach(dtkComposerSceneNote *note, d->notes)
            if (!rect.contains(note->sceneBoundingRect()))
                d->obfuscated = true;
        
    }

    foreach(dtkComposerSceneNode *node, d->nodes) {

        node->setVisible(!d->obfuscated && this->isVisible() && d->flattened);

        if (dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node)) {

            if (composite->flattened())
                composite->obfuscate();

        } else if (dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node)) {

            foreach(dtkComposerSceneNodeComposite *block, control->blocks())
                block->obfuscate();

        }
    }

    foreach(dtkComposerSceneNote *note, d->notes)
        note->setVisible(!d->obfuscated && this->isVisible() && d->flattened);

    foreach(dtkComposerSceneEdge *edge, d->edges)
        edge->setVisible(!d->obfuscated && this->isVisible() && d->flattened);

    this->update();
}

void dtkComposerSceneNodeComposite::boundingBox(qreal& x_min, qreal& x_max, qreal& y_min, qreal& y_max)
{
    qreal xmin = d->unreveal_pos.x();
    qreal xmax = d->unreveal_pos.x() + d->unreveal_rect.width();
    
    qreal ymin = d->unreveal_pos.y();
    qreal ymax = d->unreveal_pos.y() + d->unreveal_rect.height();
    
    foreach(dtkComposerSceneNode *node, d->nodes) {
        xmin = qMin(xmin, node->scenePos().x());
        xmax = qMax(xmax, node->scenePos().x() + node->boundingRect().width());
        ymin = qMin(ymin, node->scenePos().y());
        ymax = qMax(ymax, node->scenePos().y() + node->boundingRect().height());
    }
    
    x_min = xmin;
    x_max = xmax;
    y_min = ymin;
    y_max = ymax;
}

QRectF dtkComposerSceneNodeComposite::boundingRect(void) const
{
    return d->rect.adjusted(-2, -2, 2, 2);
}

void dtkComposerSceneNodeComposite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal radius = this->embedded() ? 0.0 : 5.0;

    if (this->isSelected()) {
        painter->setPen(QPen(Qt::magenta, 3, Qt::SolidLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRoundedRect(d->rect.adjusted(-1, -1, 1, 1), radius, radius);
    }

    if(d->revealed) {
        painter->setPen(QPen(Qt::darkGray, 1, Qt::DashLine));
        painter->setBrush(QColor(10, 10, 10, 120));
    } else {
        QLinearGradient gradiant(d->rect.left(), d->rect.top(), d->rect.left(), d->rect.bottom());
        gradiant.setColorAt(0.0, QColor(Qt::darkGray));
        gradiant.setColorAt(10 / d->rect.height(), QColor(Qt::darkGray).darker().darker());
        gradiant.setColorAt(1.0, QColor(Qt::darkGray).darker().darker().darker());

        painter->setPen(QPen(QColor(Qt::darkGray).darker().darker(), 1, Qt::SolidLine));
        painter->setBrush(gradiant);
    }

    if(this->embedded() && !d->entered) {
        painter->setPen(Qt::NoPen);
        if(d->obfuscated)
            painter->setBrush(QColor(0, 0, 0, 127));
    }

    painter->drawRoundedRect(d->rect, radius, radius);

    // Drawing node's title

    qreal margin = 5.0;

    QFont font = painter->font();
    QFontMetricsF metrics(font);

    QString title_text = metrics.elidedText(this->title(), Qt::ElideMiddle, this->boundingRect().width()-2-4*margin);
    QPointF title_pos;

    if(!this->embedded() && !d->entered)
        title_pos = QPointF(2*margin, 2*margin + metrics.xHeight());
    else
        title_pos = QPointF(d->rect.width()/2.0 - metrics.width(title_text)/2.0, d->rect.height()/2.0 + metrics.xHeight()/2.0);

    if((this->embedded() && !d->entered) || (!this->embedded() && d->revealed))
        painter->setPen(QPen(QColor(Qt::darkGray)));
    else
        painter->setPen(QPen(QColor(Qt::white)));

    painter->drawText(title_pos, title_text);

    if (d->obfuscated) {

        QFont oFont = QFont(font);
        oFont.setPointSizeF(font.pointSizeF()-2);

        QString title = QString("Obfuscated content. (%1 notes, %2 nodes, %3 edges)")
            .arg(d->notes.count())
            .arg(d->nodes.count())
            .arg(d->edges.count());

        title_text = metrics.elidedText(title, Qt::ElideRight, this->boundingRect().width()-2-4*margin);
        title_pos = QPointF(d->rect.width()/2.0 - metrics.width(title_text)/2.0, d->rect.height()/2.0 + metrics.xHeight()/2.0 + metrics.height() * 1.5);

        painter->setPen(QPen(QColor(Qt::darkGray)));
        painter->setFont(oFont);
        painter->drawText(title_pos, title_text);
    }
}

void dtkComposerSceneNodeComposite::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    dtkComposerNodeRemote *remote = dynamic_cast<dtkComposerNodeRemote *>(this->wrapee());

    if(!remote) {
        event->ignore();
        return;
    }

    if (event->mimeData()->hasText())
        event->acceptProposedAction();
    else
        event->ignore();
}

void dtkComposerSceneNodeComposite::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->accept();
}

void dtkComposerSceneNodeComposite::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    dtkComposerNodeRemote *remote = dynamic_cast<dtkComposerNodeRemote *>(this->wrapee());

    if(!remote) {
        event->ignore();
        return;
    }

    if (event->mimeData()->hasText())
        event->acceptProposedAction();
    else
        event->ignore();
}

void dtkComposerSceneNodeComposite::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    dtkComposerNodeRemote *remote = dynamic_cast<dtkComposerNodeRemote *>(this->wrapee());

    if(!remote) {
        event->ignore();
        return;
    }

    const dtkDistributedMimeData *data = qobject_cast<const dtkDistributedMimeData *>(event->mimeData());

    if(!data) {
        dtkDebug() << "Unable to retrieve distributed mime data";
    }

    QString job = data->text();

    dtkDistributedController *controller = const_cast<dtkDistributedMimeData *>(data)->controller();

    remote->setJob(job);
    remote->setController(controller);
    this->setTitle("Remote on "+ job);

    event->acceptProposedAction();
    this->update();
}
