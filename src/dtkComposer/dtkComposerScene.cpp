/* dtkComposerScene.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:13:25
 * Version: $Id$
 * Last-Updated: Thu Feb  2 19:32:24 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 998
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerMachine.h"
#include "dtkComposerMachineState.h"
#include "dtkComposerScene.h"
#include "dtkComposerScene_p.h"
#include "dtkComposerStack.h"
#include "dtkComposerStackCommand.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerScenePort
// /////////////////////////////////////////////////////////////////

class dtkComposerScenePortPrivate
{
public:
    unsigned int id;

public:
    QGraphicsEllipseItem *ellipse;
};

dtkComposerScenePort::dtkComposerScenePort(unsigned int id, QGraphicsItem *parent) : QGraphicsItem(parent), d(new dtkComposerScenePortPrivate)
{
    d->id = id;

    d->ellipse = new QGraphicsEllipseItem(this);
    d->ellipse->setPen(QPen(Qt::darkGray, 1));
    d->ellipse->setBrush(Qt::lightGray);
    d->ellipse->setRect(0, 0, 10, 10);
    
    this->setFlags(QGraphicsItem::ItemIsSelectable);
    this->setZValue(1);
}

dtkComposerScenePort::~dtkComposerScenePort(void)
{
    delete d;

    d = NULL;
}

unsigned int dtkComposerScenePort::id(void) const
{
    return d->id;
}

QRectF dtkComposerScenePort::boundingRect(void) const
{
    return QRectF(0, 0, 10, 10);
}

void dtkComposerScenePort::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneEdge
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneEdgePrivate
{
public:
    dtkComposerScenePort *source;
    dtkComposerScenePort *destination;

public:
    QPainterPath path;
};

dtkComposerSceneEdge::dtkComposerSceneEdge(void) : QGraphicsItem(), d(new dtkComposerSceneEdgePrivate)
{
    d->source = NULL;
    d->destination = NULL;

    this->setZValue(-1);
}

dtkComposerSceneEdge::~dtkComposerSceneEdge(void)
{
    delete d;

    d = NULL;
}

QRectF dtkComposerSceneEdge::boundingRect(void) const
{
    return d->path.boundingRect();
}

void dtkComposerSceneEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(Qt::gray);

    painter->drawPath(d->path);

    painter->restore();
}

dtkComposerScenePort *dtkComposerSceneEdge::source(void)
{
    return d->source;
}

dtkComposerScenePort *dtkComposerSceneEdge::destination(void)
{
    return d->destination;
}

void dtkComposerSceneEdge::setSource(dtkComposerScenePort *port)
{
    d->source = port;

    this->adjust();
}

void dtkComposerSceneEdge::setDestination(dtkComposerScenePort *port)
{
    d->destination = port;

    this->adjust();
}

void dtkComposerSceneEdge::adjust(void)
{
    if (!d->source || !d->destination)
        return;

    if (!this->isVisible())
        return;

    QRectF rect;
    rect = d->source->boundingRect();
    QPointF start = d->source->mapToScene(rect.center());
    rect = d->destination->boundingRect();
    QPointF end = d->destination->mapToScene(rect.center());

    this->adjust(start, end);
}

void dtkComposerSceneEdge::adjust(const QPointF& start, const QPointF& end)
{
    this->prepareGeometryChange();
    
    QPointF midPoint = (start + end) / 2;

    qreal halfMid = (midPoint.x() - start.x())/2;

    QPainterPath path;
    path.moveTo(start);
    path.cubicTo(QPointF(end.x() - halfMid, start.y()), QPointF(start.x() + halfMid, end.y()), end);

    QPainterPathStroker stroker;
    stroker.setWidth(3);
    stroker.setCapStyle(Qt::RoundCap);
    d->path = stroker.createStroke(path);

    this->update();
}

bool dtkComposerSceneEdge::link(bool anyway)
{
    Q_UNUSED(anyway);
    
    if(!d->source || !d->destination)
        return false;

    dynamic_cast<dtkComposerSceneNode *>(d->source->parentItem())->addOutputEdge(this);
    dynamic_cast<dtkComposerSceneNode *>(d->destination->parentItem())->addInputEdge(this);

    return true;
}

bool dtkComposerSceneEdge::unlink(void)
{
    if(!d->source || !d->destination)
        return false;

    dynamic_cast<dtkComposerSceneNode *>(d->source->parentItem())->removeOutputEdge(this);
    dynamic_cast<dtkComposerSceneNode *>(d->destination->parentItem())->removeInputEdge(this);

    return true;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNode
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodePrivate
{
public:
    QList<dtkComposerScenePort *>  input_ports;
    QList<dtkComposerScenePort *> output_ports;

    QList<dtkComposerSceneEdge *>  input_edges;
    QList<dtkComposerSceneEdge *> output_edges;
};

dtkComposerSceneNode::dtkComposerSceneNode(void) : QGraphicsItem(), d(new dtkComposerSceneNodePrivate)
{
    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

dtkComposerSceneNode::~dtkComposerSceneNode(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneNode::addInputEdge(dtkComposerSceneEdge *edge)
{
    d->input_edges << edge;
}

void dtkComposerSceneNode::addOutputEdge(dtkComposerSceneEdge *edge)
{
    d->output_edges << edge;
}

void dtkComposerSceneNode::removeInputEdge(dtkComposerSceneEdge *edge)
{
    d->input_edges.removeAll(edge);
}

void dtkComposerSceneNode::removeOutputEdge(dtkComposerSceneEdge *edge)
{
    d->output_edges.removeAll(edge);
}

QList<dtkComposerSceneEdge *> dtkComposerSceneNode::inputEdges(void)
{
    return d->input_edges;
}

QList<dtkComposerSceneEdge *> dtkComposerSceneNode::outputEdges(void)
{
    return d->output_edges;
}

dtkComposerScenePort *dtkComposerSceneNode::port(unsigned int id)
{
    dtkComposerScenePort *p = NULL;

    foreach(dtkComposerScenePort *port, d->input_ports)
        if (port->id() == id)
            p = port;

    foreach(dtkComposerScenePort *port, d->output_ports)
        if (port->id() == id)
            p = port;

    return p;
}

QList<dtkComposerScenePort *> dtkComposerSceneNode::inputPorts(void)
{
    return d->input_ports;
}

QList<dtkComposerScenePort *> dtkComposerSceneNode::outputPorts(void)
{
    return d->output_ports;
}

// QVariant dtkComposerSceneNode::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
// {
//     if(change == QGraphicsItem::ItemSelectedHasChanged) {

//         if(value.toBool()) {
//             ; // TO SELECTED STATE
//         } else {
//             ; // TO UNUSELECTED STATE
//         }
//     }

//     return QGraphicsItem::itemChange(change, value);
// }

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeComposite
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodeCompositePrivate
{
public:
    dtkComposerSceneNodeList children;

public:
    QRectF rect;

public:
    bool entered;
};

dtkComposerSceneNodeComposite::dtkComposerSceneNodeComposite(void) : dtkComposerSceneNode(), d(new dtkComposerSceneNodeCompositePrivate)
{
    d->rect = QRectF(0, 0, 150, 50);

    d->entered = false;
}

dtkComposerSceneNodeComposite::~dtkComposerSceneNodeComposite(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneNodeComposite::addNode(dtkComposerSceneNode *node)
{
    d->children << node;
}

void dtkComposerSceneNodeComposite::removeNode(dtkComposerSceneNode *node)
{
    d->children.removeAll(node);
}

dtkComposerSceneNodeList dtkComposerSceneNodeComposite::children(void)
{
    return d->children;
}

bool dtkComposerSceneNodeComposite::entered(void)
{
    return d->entered;
}

void dtkComposerSceneNodeComposite::enter(void)
{
    d->entered = true;

    this->layout();
}

void dtkComposerSceneNodeComposite::leave(void)
{
    d->entered = false;

    this->layout();
}

void dtkComposerSceneNodeComposite::layout(void)
{
    if(!d->entered)
        d->rect = QRectF(0, 0, 150, 50);
    else {
        QRectF rect;
        
        foreach(dtkComposerSceneNode *node, d->children)
            rect |= node->mapRectToScene(node->boundingRect());

        d->rect = QRectF(-rect.width()/2, -rect.height()/2, rect.width(), rect.height());
        d->rect = d->rect.adjusted(-10, -10, 10, 10);

        foreach(dtkComposerSceneNode *node, d->children)
            node->setPos(node->pos() + d->rect.topLeft() - rect.topLeft() + QPointF(10, 10));
    }

    this->update();
}

QRectF dtkComposerSceneNodeComposite::boundingRect(void) const
{
    return d->rect.adjusted(-2, -2, 2, 2);
}

void dtkComposerSceneNodeComposite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    static qreal radius = 5.0;

    if (this->isSelected()) {
        painter->setPen(QPen(Qt::magenta, 2, Qt::SolidLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRoundedRect(d->rect.adjusted(-2, -2, 2, 2), radius, radius);
    }

    if(d->entered) {
        painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
    } else {
        QLinearGradient gradiant(d->rect.left(), d->rect.top(), d->rect.left(), d->rect.bottom());
        gradiant.setColorAt(0.0, QColor(Qt::darkGray));
        gradiant.setColorAt(0.3, QColor(Qt::darkGray).darker().darker());
        gradiant.setColorAt(1.0, QColor(Qt::darkGray).darker().darker().darker());

        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
        painter->setBrush(gradiant);
    }

    painter->drawRoundedRect(d->rect, radius, radius);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeLeaf
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodeLeafPrivate
{
public:
    QRectF rect;
};

dtkComposerSceneNodeLeaf::dtkComposerSceneNodeLeaf(void) : dtkComposerSceneNode(), d(new dtkComposerSceneNodeLeafPrivate)
{
    dtkComposerSceneNode::d->input_ports << new dtkComposerScenePort(0, this);
    dtkComposerSceneNode::d->input_ports << new dtkComposerScenePort(1, this);

    dtkComposerSceneNode::d->output_ports << new dtkComposerScenePort(2, this);

    d->rect = QRectF(0, 0, 150, 50);

    this->layout();
}

dtkComposerSceneNodeLeaf::~dtkComposerSceneNodeLeaf(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneNodeLeaf::layout(void)
{
    int port_margin_top = 10;
    int port_margin_bottom = 10;
    int port_margin_left = 10;
    int port_spacing = 10;

    int node_width = d->rect.width();

    for(int i = 0; i < dtkComposerSceneNode::d->input_ports.count(); i++)
        dtkComposerSceneNode::d->input_ports.at(i)->setPos(QPointF(port_margin_left, i*dtkComposerSceneNode::d->input_ports.at(i)->boundingRect().height() + i*port_spacing + port_margin_top));

    for(int i = 0; i < dtkComposerSceneNode::d->output_ports.count(); i++)
        dtkComposerSceneNode::d->output_ports.at(i)->setPos(QPointF(node_width - port_margin_left - dtkComposerSceneNode::d->output_ports.at(i)->boundingRect().width(), i*dtkComposerSceneNode::d->output_ports.at(i)->boundingRect().height() + i*port_spacing + port_margin_top));

    if(dtkComposerSceneNode::d->input_ports.count() || dtkComposerSceneNode::d->output_ports.count())
        if(dtkComposerSceneNode::d->input_ports.count() >= dtkComposerSceneNode::d->output_ports.count())
            d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), dtkComposerSceneNode::d->input_ports.count() * dtkComposerSceneNode::d->input_ports.at(0)->boundingRect().height() + port_margin_top + port_margin_bottom + (dtkComposerSceneNode::d->input_ports.count()-1) * port_spacing));
        else
            d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), dtkComposerSceneNode::d->output_ports.count() * dtkComposerSceneNode::d->output_ports.at(0)->boundingRect().height() + port_margin_top + port_margin_bottom + (dtkComposerSceneNode::d->output_ports.count()-1) * port_spacing));
}

QRectF dtkComposerSceneNodeLeaf::boundingRect(void) const
{
    return d->rect.adjusted(-2, -2, 2, 2);
}

void dtkComposerSceneNodeLeaf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    static qreal radius = 5.0;

    QLinearGradient gradiant(d->rect.left(), d->rect.top(), d->rect.left(), d->rect.bottom());
    gradiant.setColorAt(0.0, QColor(Qt::white));
    gradiant.setColorAt(0.3, QColor(Qt::gray));
    gradiant.setColorAt(1.0, QColor(Qt::gray).darker());

    if (this->isSelected()) {
        painter->setPen(QPen(Qt::magenta, 2, Qt::SolidLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRoundedRect(d->rect.adjusted(-2, -2, 2, 2), radius, radius);
    }

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter->setBrush(gradiant);
    painter->drawRoundedRect(d->rect, radius, radius);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNote
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNotePrivate
{
public:
    QPointF drag_point;

public:
    QRectF bounding_rect;

public:
    QGraphicsTextItem *text;
};

dtkComposerSceneNote::dtkComposerSceneNote(dtkComposerSceneNode *parent) : QGraphicsItem(parent), d(new dtkComposerSceneNotePrivate)
{
    d->bounding_rect = QRectF(-100, -100, 200, 200);

    d->text = new QGraphicsTextItem("Note", this);
    d->text->setPos(-100, -100);
    d->text->setTextInteractionFlags(Qt::TextEditorInteraction);
    d->text->setTextWidth(200);

    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    this->setZValue(-4000);
}

dtkComposerSceneNote::~dtkComposerSceneNote(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerSceneNote::text(void) const
{
    return d->text->toPlainText();
}

void dtkComposerSceneNote::setSize(const QSizeF& size)
{
    d->bounding_rect.setHeight(size.height());
    d->bounding_rect.setWidth(size.width());

    d->text->setTextWidth(size.width());
}

void dtkComposerSceneNote::setText(const QString& text)
{
    d->text->setPlainText(text);
}

QRectF dtkComposerSceneNote::boundingRect(void) const
{
    return d->bounding_rect;
}

void dtkComposerSceneNote::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(option->rect, QColor(Qt::yellow).darker());

    painter->fillRect(this->mapRectFromItem(d->text, d->text->boundingRect()), QColor(Qt::yellow));

    // Drawing size grip

    QPainterPath path;
    path.moveTo(d->bounding_rect.bottomRight());
    path.lineTo(d->bounding_rect.bottomRight() + QPointF(-12, 0));
    path.lineTo(d->bounding_rect.bottomRight() + QPointF(0, -12));
    path.lineTo(d->bounding_rect.bottomRight());

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#ffff88"));
    painter->drawPath(path);

    if(this->isSelected()) {
        QPen pen;
        pen.setColor(Qt::magenta);
        pen.setWidth(2);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(option->rect);
    }
}

void dtkComposerSceneNote::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && !d->drag_point.isNull()) {
        
        QPointF delta = QPointF(event->scenePos() - d->drag_point);

        d->bounding_rect.setBottomRight(d->bounding_rect.bottomRight() + delta);
        d->text->setTextWidth(d->bounding_rect.width());

        d->drag_point = event->scenePos();

        event->accept();

        this->update();

    } else {

        QGraphicsItem::mouseMoveEvent(event);
    }
}

void dtkComposerSceneNote::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF br = d->bounding_rect.bottomRight();

    QRectF corner(br.x() - 16, br.y() - 16, 16, 16);

    if (event->button() & Qt::LeftButton && corner.contains(event->pos())) {
        d->drag_point = event->scenePos();
        event->accept();
    }

    QGraphicsItem::mousePressEvent(event);
}

void dtkComposerSceneNote::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() & Qt::LeftButton && !d->drag_point.isNull()) {
        d->drag_point = QPointF(0, 0);
        event->accept();
    }

    QGraphicsItem::mouseReleaseEvent(event);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerScene
// /////////////////////////////////////////////////////////////////

dtkComposerScene::dtkComposerScene(QObject *parent) : QGraphicsScene(parent), d(new dtkComposerScenePrivate)
{
    d->factory = NULL;
    d->machine = NULL;
    d->stack = NULL;

    d->current_edge = NULL;
    d->current_node = NULL;
}

dtkComposerScene::~dtkComposerScene(void)
{
    delete d;

    d = NULL;
}

void dtkComposerScene::setFactory(dtkComposerFactory *factory)
{
    d->factory = factory;
}

void dtkComposerScene::setMachine(dtkComposerMachine *machine)
{
    d->machine = machine;
}

void dtkComposerScene::setStack(dtkComposerStack *stack)
{
    d->stack = stack;
}

void dtkComposerScene::addNode(dtkComposerSceneNode *node)
{
    d->nodes << node;

    this->addItem(node);

    emit modified(true);
}

void dtkComposerScene::removeNode(dtkComposerSceneNode *node)
{
    if (d->nodes.contains(node))
        d->nodes.removeAll(node);

    this->removeItem(node);

    emit modified(true);
}

void dtkComposerScene::addEdge(dtkComposerSceneEdge *edge)
{
    d->edges << edge;

    this->addItem(edge);

    emit modified(true);
}

void dtkComposerScene::removeEdge(dtkComposerSceneEdge *edge)
{
    if (d->edges.contains(edge))
        d->edges.removeAll(edge);

    this->removeItem(edge);

    emit modified(true);
}

void dtkComposerScene::addNote(dtkComposerSceneNote *note)
{
    d->notes << note;

    this->addItem(note);

    emit modified(true);
}

void dtkComposerScene::removeNote(dtkComposerSceneNote *note)
{
    if (d->notes.contains(note))
        d->notes.removeAll(note);

    this->removeItem(note);

    emit modified(true);
}

void dtkComposerScene::clear(void)
{
    foreach(dtkComposerSceneNode *node, d->nodes)
        this->removeNode(node);

    foreach(dtkComposerSceneNote *note, d->notes)
        this->removeNote(note);

    d->nodes.clear();
    d->notes.clear();
}

bool dtkComposerScene::contains(dtkComposerSceneEdge *edge)
{
    return d->edges.contains(edge);
}

bool dtkComposerScene::contains(dtkComposerSceneNode *node)
{
    return d->nodes.contains(node);
}

bool dtkComposerScene::contains(dtkComposerSceneNote *note)
{
    return d->notes.contains(note);
}

bool dtkComposerScene::displays(dtkComposerSceneEdge *edge)
{
    return this->items().contains(edge);
}

bool dtkComposerScene::displays(dtkComposerSceneNode *node)
{
    return this->items().contains(node);
}

bool dtkComposerScene::displays(dtkComposerSceneNote *note)
{
    return this->items().contains(note);
}

QList<dtkComposerSceneEdge *> dtkComposerScene::edges(void)
{
    return d->edges;
}

QList<dtkComposerSceneNode *> dtkComposerScene::nodes(void)
{
    return d->nodes;
}

QList<dtkComposerSceneNote *> dtkComposerScene::notes(void)
{
    return d->notes;
}

//! Receives drag enter events.
/*! 
 *  
 */
void dtkComposerScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        event->ignore();
}

//! Receives drag leave events.
/*! 
 *  
 */
void dtkComposerScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->accept();
}

//! Receives drag move events.
/*! 
 *  
 */
void dtkComposerScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        event->ignore();
}

//! Receives drop events.
/*! 
 *  
 */
void dtkComposerScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QString name = event->mimeData()->text();
    QUrl url = event->mimeData()->urls().first();

    if (url.scheme() == "note") {

        dtkComposerStackCommandCreateNote *command = new dtkComposerStackCommandCreateNote;
        command->setScene(this);
        command->setPosition(event->scenePos());
        
        d->stack->push(command);

        event->acceptProposedAction();

        return;
    }

    if (url.scheme() == "node") {

        dtkComposerStackCommandCreateNode *command = new dtkComposerStackCommandCreateNode;
        command->setFactory(d->factory);
        command->setScene(this);
        command->setPosition(event->scenePos());
        command->setType(url.path());
        command->setName(name);
        
        d->stack->push(command);
        
        event->acceptProposedAction();

        return;
    }

    event->ignore();
}

void dtkComposerScene::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete) && (event->modifiers() & Qt::ControlModifier)) {

        QList<dtkComposerSceneNode *> selected_nodes;
        QList<dtkComposerSceneNote *> selected_notes;

        // retrieve items to be deleted

        foreach(QGraphicsItem *item, this->selectedItems()) {
            if (dtkComposerSceneNode *snode = dynamic_cast<dtkComposerSceneNode *>(item))
                selected_nodes << snode;
            if (dtkComposerSceneNote *snote = dynamic_cast<dtkComposerSceneNote *>(item))
                selected_notes << snote;
        }

        // multiple node deletion
        
        if(selected_nodes.count() > 1) {

            dtkComposerStackCommand *group = new dtkComposerStackCommand;
            group->setText("Destroy a set of nodes");
            
            foreach(dtkComposerSceneNode *node, selected_nodes) {

                dtkComposerStackCommandDestroyNode *command = new dtkComposerStackCommandDestroyNode(group);
                command->setScene(this);
                command->setNode(node);
            }

            d->stack->push(group);

        // single node deletion

        } else if(selected_nodes.count() == 1) {

            dtkComposerStackCommandDestroyNode *command = new dtkComposerStackCommandDestroyNode;
            command->setScene(this);
            command->setNode(selected_nodes.first());

            d->stack->push(command);
        }

        // multiple note deletion

        if(selected_notes.count() > 1) {

            dtkComposerStackCommand *group = new dtkComposerStackCommand;
            group->setText("Destroy a set of notes");
            
            foreach(dtkComposerSceneNote *note, selected_notes) {

                dtkComposerStackCommandDestroyNote *command = new dtkComposerStackCommandDestroyNote(group);
                command->setScene(this);
                command->setNote(note);
            }

            d->stack->push(group);

        // single note deletion

        } else if(selected_notes.count() == 1) {

            dtkComposerStackCommandDestroyNote *command = new dtkComposerStackCommandDestroyNote;
            command->setScene(this);
            command->setNote(selected_notes.first());

            d->stack->push(command);
        }

    } else if ((event->key() == Qt::Key_G) && (event->modifiers() & Qt::ControlModifier)) {

        dtkComposerSceneNodeList selected_nodes;

        foreach(QGraphicsItem *item, this->selectedItems()) {
            if (dtkComposerSceneNode *snode = dynamic_cast<dtkComposerSceneNode *>(item))
                selected_nodes << snode;
        }

        if(selected_nodes.count()) {

            dtkComposerStackCommandCreateGroup *command = new dtkComposerStackCommandCreateGroup;
            command->setScene(this);
            command->setNodes(selected_nodes);
            
            d->stack->push(command);
        }

    } else if ((event->key() == Qt::Key_U) && (event->modifiers() & Qt::ControlModifier) && (this->selectedItems().count() == 1)) {

        if(dtkComposerSceneNodeComposite *group = dynamic_cast<dtkComposerSceneNodeComposite *>(this->selectedItems().first())) {

            dtkComposerStackCommandExplodeGroup *command = new dtkComposerStackCommandExplodeGroup;
            command->setScene(this);
            command->setNode(group);
        
            d->stack->push(command);
        }

    } else {
        QGraphicsScene::keyPressEvent(event);
    }
}

void dtkComposerScene::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsScene::keyReleaseEvent(event);
}

void dtkComposerScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

    // Managnig grabbing of selected nodes

    foreach(QGraphicsItem *item, this->selectedItems()) {

        if(dtkComposerSceneNode *node = dynamic_cast<dtkComposerSceneNode *>(item)) {

            QRectF updateRect;

            foreach(dtkComposerSceneEdge *edge, node->inputEdges()) {
                edge->adjust();
                updateRect |= edge->boundingRect();
            }
            
            foreach(dtkComposerSceneEdge *edge, node->outputEdges()) {
                edge->adjust();
                updateRect |= edge->boundingRect();
            }
            
            this->update(updateRect);
        }
    }

    // Managing grabbing of current edge

    if (d->current_edge)
        d->current_edge->adjust(d->current_edge->source()->mapToScene(d->current_edge->source()->boundingRect().center()), event->scenePos());

    if (d->current_edge)
        this->update(d->current_edge->boundingRect());

    if (d->current_edge)
        event->accept();
}

void dtkComposerScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

    dtkComposerScenePort *source = this->portAt(event->scenePos());

    if(!source)
        return;

    if(d->current_edge)
        return;

    d->current_edge = new dtkComposerSceneEdge;
    d->current_edge->setSource(source);

    this->addItem(d->current_edge);
}

void dtkComposerScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);

    if(!d->current_edge)
        return;

    if(dtkComposerScenePort *destination = this->portAt(event->scenePos()))
        d->current_edge->setDestination(destination);

    if(d->current_edge->link()) {

        dtkComposerStackCommandCreateEdge *command = new dtkComposerStackCommandCreateEdge;
        command->setScene(this);
        command->setSource(d->current_edge->source());
        command->setDestination(d->current_edge->destination());

        d->stack->push(command);
    }

    d->current_edge->unlink();

    this->removeItem(d->current_edge);

    delete d->current_edge;
    
    d->current_edge = NULL;
}

void dtkComposerScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseDoubleClickEvent(event);

    dtkComposerSceneNode *node = this->nodeAt(event->scenePos());

    if(!node)
        return;

    dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node);

    if(!composite)
        return;

    foreach(QGraphicsItem *item, this->items())
        this->removeItem(item);

    if(!composite->entered()) {

        composite->enter();

        this->addItem(composite);
        
        foreach(dtkComposerSceneNode *node, composite->children()) {
            this->addItem(node);
            node->setParentItem(composite);
        }
        
        foreach(dtkComposerSceneEdge *edge, d->edges) {
            
            dtkComposerSceneNode *s_node = dynamic_cast<dtkComposerSceneNode *>(edge->source()->parentItem());
            dtkComposerSceneNode *d_node = dynamic_cast<dtkComposerSceneNode *>(edge->destination()->parentItem());
            
            if(s_node && d_node && this->displays(s_node) && this->displays(d_node)) {
                this->addItem(edge);
            }
        }
        
        foreach(dtkComposerSceneNote *note, d->notes) {
            
            if (note->parentItem() == composite)
                this->addItem(note);
        }

        d->current_node = composite;

    } else { // DEPTH MAX IS 1 SO FAR
        
        composite->leave();
        
        this->addItem(composite);
        
        foreach(dtkComposerSceneNode *node, d->nodes)
            this->addItem(node);
        
        foreach(dtkComposerSceneEdge *edge, d->edges) {
            
            dtkComposerSceneNode *s_node = dynamic_cast<dtkComposerSceneNode *>(edge->source()->parentItem());
            dtkComposerSceneNode *d_node = dynamic_cast<dtkComposerSceneNode *>(edge->destination()->parentItem());
            
            if(s_node && d_node && this->displays(s_node) && this->displays(d_node)) {
                this->addItem(edge);
            }
        }
        
        foreach(dtkComposerSceneNote *note, d->notes) {
            
            if (!note->parentItem())
                this->addItem(note);
        }

        d->current_node = NULL;
    }

    this->clearSelection();
}

dtkComposerSceneNode *dtkComposerScene::nodeAt(const QPointF& point) const
{
    QList<QGraphicsItem *> items = this->items(point.x(), point.y(), 1, 1, Qt::IntersectsItemBoundingRect);

    foreach(QGraphicsItem *item, items)
        if (dtkComposerSceneNode *node = dynamic_cast<dtkComposerSceneNode *>(item))
            return node;

    return NULL;
}

dtkComposerScenePort *dtkComposerScene::portAt(const QPointF& point) const
{
    QList<QGraphicsItem *> items = this->items(point.x(), point.y(), 1, 1, Qt::IntersectsItemBoundingRect);

    foreach(QGraphicsItem *item, items)
        if (dtkComposerScenePort *port = dynamic_cast<dtkComposerScenePort *>(item))
            return port;

    return NULL;
}
