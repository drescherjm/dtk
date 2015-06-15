// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkComposerNode.h"
#include "dtkComposerNodeMetaData.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNode_p.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerScenePort.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeLeafPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodeLeafPrivate
{
public:
    void flagAs(Qt::GlobalColor color);

public:
    QRectF rect;

public:
    bool use_gui;

public:
    QGraphicsPixmapItem *flag;
         Qt::GlobalColor flag_color;

public:
    QLinearGradient gradiant;
               bool gradiant_defined;
};

void dtkComposerSceneNodeLeafPrivate::flagAs(Qt::GlobalColor color)
{
    switch(color) {
    case Qt::blue:
        this->flag->setPixmap(QPixmap(":dtkComposer/dtkComposerNodeFlag-blue.png"));
        break;
    case Qt::gray:
        this->flag->setPixmap(QPixmap(":dtkComposer/dtkComposerNodeFlag-gray.png"));
        break;
    case Qt::green:
        this->flag->setPixmap(QPixmap(":dtkComposer/dtkComposerNodeFlag-green.png"));
        break;
    case Qt::darkYellow:
        this->flag->setPixmap(QPixmap(":dtkComposer/dtkComposerNodeFlag-orange.png"));
        break;
    case Qt::red:
        this->flag->setPixmap(QPixmap(":dtkComposer/dtkComposerNodeFlag-red.png"));
        break;
    case Qt::magenta:
        this->flag->setPixmap(QPixmap(":dtkComposer/dtkComposerNodeFlag-pink.png"));
        break;
    case Qt::yellow:
        this->flag->setPixmap(QPixmap(":dtkComposer/dtkComposerNodeFlag-yellow.png"));
        break;
    default:
        break;
    };

    this->flag_color = color;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeLeaf implementation
// /////////////////////////////////////////////////////////////////

dtkComposerSceneNodeLeaf::dtkComposerSceneNodeLeaf(void) : dtkComposerSceneNode(), d(new dtkComposerSceneNodeLeafPrivate)
{
    d->rect = QRectF(0, 0, 150, 50);

    d->gradiant_defined = false;

    if (qApp && qobject_cast<QGuiApplication *>(qApp)) {
        d->use_gui = true;
        d->flag = new QGraphicsPixmapItem(this);
        d->flag->setVisible(false);
        d->flag_color = Qt::transparent;
    } else {
        d->use_gui = false;
        d->flag = NULL;
    }
}

dtkComposerSceneNodeLeaf::~dtkComposerSceneNodeLeaf(void)
{
    if (d->flag)
        delete d->flag;

    delete d;

    d = NULL;
}

void dtkComposerSceneNodeLeaf::wrap(dtkComposerNode *node)
{
    dtkComposerSceneNode::wrap(node);

    this->setToolTip(node->type());

    for(int i = 0; i < node->receivers().count(); ++i) {
        dtkComposerScenePort *port = new dtkComposerScenePort(dtkComposerScenePort::Input, this);
        port->setLabel(node->inputLabelHint(this->addInputPort(port)));
    }

    for(int i = 0; i < node->emitters().count(); ++i) {
        dtkComposerScenePort *port = new dtkComposerScenePort(dtkComposerScenePort::Output, this);
        this->addOutputPort(port);
        port->setLabel(node->outputLabelHint(this->outputPorts().indexOf(port)));
    }

    this->layout();
}

void dtkComposerSceneNodeLeaf::flag(Qt::GlobalColor color, bool on)
{
    if (d->flag) {
        d->flagAs(color);
        d->flag->setVisible(on);
    }
}

void dtkComposerSceneNodeLeaf::flag(QColor color)
{
    if (!d->use_gui)
        return;

    if(color == Qt::blue)
        this->flag(Qt::blue, true);
    else if(color == Qt::gray)
        this->flag(Qt::gray, true);
    else if(color == Qt::green)
        this->flag(Qt::green, true);
    else if(color == Qt::darkYellow)
        this->flag(Qt::darkYellow, true);
    else if(color == Qt::red)
        this->flag(Qt::red, true);
    else if(color == Qt::magenta)
        this->flag(Qt::magenta, true);
    else if(color == Qt::yellow)
        this->flag(Qt::yellow, true);
}

bool dtkComposerSceneNodeLeaf::flagged(Qt::GlobalColor color)
{
    if(!d->flag)
        return false;

    if(!d->flag->isVisible())
        return false;
    else
        return d->flag_color == color;
}

bool dtkComposerSceneNodeLeaf::flagged(void)
{
    if(!d->flag)
        return false;

    return d->flag->isVisible();
}

QString dtkComposerSceneNodeLeaf::flagColorName(void)
{
    if(!d->flag || !d->flag->isVisible())
        return QString();

    QColor color(d->flag_color);

    return color.name();
}

Qt::GlobalColor dtkComposerSceneNodeLeaf::flagColor(void)
{
    return d->flag_color;
}

#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"

void dtkComposerSceneNodeLeaf::layout(void)
{
    if (!d->use_gui)
        return;

    int header = this->embedded() ? 0 : 15;

    int port_margin_top = 10;
    int port_margin_bottom = 10;
    int port_margin_left = 10;
    int port_spacing = 10;

// /////////////////////////////////////////////////////////////////
// Setting up port position
// /////////////////////////////////////////////////////////////////

    for(int i = 0; i < this->inputPorts().count(); i++)
        this->inputPorts().at(i)->setPos(QPointF(port_margin_left, i*this->inputPorts().at(i)->boundingRect().height() + i*port_spacing + port_margin_top + header));

    for(int i = 0; i < this->outputPorts().count(); i++)
        this->outputPorts().at(i)->setPos(QPointF(d->rect.right() - port_margin_left - this->outputPorts().at(i)->boundingRect().width(), i*this->outputPorts().at(i)->boundingRect().height() + i*port_spacing + port_margin_top + header));

// /////////////////////////////////////////////////////////////////
// Height calculation
// /////////////////////////////////////////////////////////////////

    if(this->inputPorts().count() || this->outputPorts().count())
        if(this->inputPorts().count() >= this->outputPorts().count())
            d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), this->inputPorts().count() * this->inputPorts().at(0)->boundingRect().height() + port_margin_top + port_margin_bottom + (this->inputPorts().count()-1) * port_spacing + header));
        else
            d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), this->outputPorts().count() * this->outputPorts().at(0)->boundingRect().height() + port_margin_top + port_margin_bottom + (this->outputPorts().count()-1) * port_spacing + header));

    else if(this->embedded())
        d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), port_margin_top + port_margin_bottom + 10));

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

// /////////////////////////////////////////////////////////////////
// Update edges geometry
// /////////////////////////////////////////////////////////////////

    QRectF updateRect;

    foreach(dtkComposerSceneEdge *edge, this->inputEdges()) {
        edge->adjust();
        updateRect |= edge->boundingRect();
    }

    foreach(dtkComposerSceneEdge *edge, this->outputEdges()) {
        edge->adjust();
        updateRect |= edge->boundingRect();
    }

    this->update(updateRect);

// /////////////////////////////////////////////////////////////////
// Beautifying nodes
// /////////////////////////////////////////////////////////////////

    if (!d->gradiant_defined) {

        d->gradiant = QLinearGradient(d->rect.left(), d->rect.top(), d->rect.left(), d->rect.bottom());

        qreal stripe = 10. / d->rect.height();

        if (this->wrapee()->nodeMetaData()->kind() == dtkComposerNode::Process) {
            d->gradiant.setColorAt(0.0, QColor(Qt::red).lighter());
            d->gradiant.setColorAt(stripe, QColor(Qt::darkRed));
            d->gradiant.setColorAt(1.0, QColor(Qt::darkRed).darker());
        } else if (this->wrapee()->nodeMetaData()->kind() == dtkComposerNode::Data) {
            d->gradiant.setColorAt(0.0, QColor(Qt::blue).lighter());
            d->gradiant.setColorAt(stripe, QColor(Qt::darkBlue));
            d->gradiant.setColorAt(1.0, QColor(Qt::darkBlue).darker());
        } else if (this->wrapee()->nodeMetaData()->kind() == dtkComposerNode::View) {
            d->gradiant.setColorAt(0.0, QColor(Qt::green).lighter());
            d->gradiant.setColorAt(stripe, QColor(Qt::darkGreen));
            d->gradiant.setColorAt(1.0, QColor(Qt::darkGreen).darker());
        } else if (this->wrapee()->nodeMetaData()->kind() == dtkComposerNode::Actor) {
            d->gradiant.setColorAt(0.0, QColor(255, 175, 0).lighter());
            d->gradiant.setColorAt(stripe, QColor(155, 75, 0));
            d->gradiant.setColorAt(1.0, QColor(155, 75, 0).darker());
        } else {
            QColor color = QColor(this->wrapee()->nodeMetaData()->color());
            d->gradiant.setColorAt(0.0, color.lighter());
            d->gradiant.setColorAt(stripe, color);
            d->gradiant.setColorAt(1.0, color.darker());
        }

        d->gradiant_defined = true;

    }

// /////////////////////////////////////////////////////////////////
// Placing flag
// /////////////////////////////////////////////////////////////////

    d->flag->setPos(d->rect.right() - 20, d->rect.top() - 20);
}

void dtkComposerSceneNodeLeaf::resize(qreal width, qreal height)
{
    d->rect = QRectF(d->rect.topLeft(), QSizeF(width, height));
}

QRectF dtkComposerSceneNodeLeaf::boundingRect(void) const
{
    return d->rect.adjusted(-2, -2, 2, 2);
}

void dtkComposerSceneNodeLeaf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal radius = this->embedded() ? 0.0 : 5.0;

    if (this->isSelected()) {
        painter->setPen(QPen(Qt::magenta, 3, Qt::SolidLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRoundedRect(d->rect.adjusted(-1, -1, 1, 1), radius, radius);
    }

    if (this->embedded())
        painter->setPen(Qt::NoPen);
    else
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));

    painter->setBrush(d->gradiant);
    painter->drawRoundedRect(d->rect, radius, radius);

    // Drawing node's title

    qreal margin = 5.0;

    QFont font = painter->font();
    QFontMetricsF metrics(font);
    QString title_text = metrics.elidedText(this->title(), Qt::ElideMiddle, this->boundingRect().width()-2-4*margin);

    QPointF title_pos;

    if(!this->embedded())
        title_pos = QPointF(2*margin, 2*margin + metrics.xHeight());
    else
        title_pos = QPointF(d->rect.right() - 2*margin - metrics.width(title_text), 2*margin + metrics.xHeight());

    painter->setPen(QPen(QColor(Qt::gray).darker().darker()));
    painter->drawText(title_pos + QPointF(0, -1), title_text);
    painter->setPen(QPen(QColor(Qt::gray).darker()));
    painter->drawText(title_pos + QPointF(0, 1), title_text);
    painter->setPen(QPen(QColor(Qt::white)));
    painter->drawText(title_pos, title_text);
}

//
// dtkComposerSceneNodeLeaf.cpp ends here
