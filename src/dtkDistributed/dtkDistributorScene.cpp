/* dtkDistributorScene.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Mar 21 18:30:50 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr  1 12:12:58 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 345
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedNode.h"
#include "dtkDistributorController.h"
#include "dtkDistributorScene.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributorLabel
// /////////////////////////////////////////////////////////////////

class dtkDistributorLabelPrivate
{
public:
    QGraphicsPixmapItem *pixmap;
    QGraphicsTextItem *text;
};

dtkDistributorLabel::dtkDistributorLabel(QGraphicsItem *parent) : QGraphicsItemGroup(parent), d(new dtkDistributorLabelPrivate)
{
    d->pixmap = NULL;
    d->text = NULL;
}

dtkDistributorLabel::~dtkDistributorLabel(void)
{
    delete d;
    
    d = NULL;
}

void dtkDistributorLabel::setLabel(const QString& label)
{
    if (d->text) {
        this->removeFromGroup(d->text);
        delete d->text;
        d->text = NULL;
    }

    d->text = new QGraphicsTextItem(label, this);
    d->text->setDefaultTextColor(Qt::white);

    this->addToGroup(d->text);
    this->layout();
}

void dtkDistributorLabel::setPixmap(const QPixmap& pixmap)
{
    d->pixmap = new QGraphicsPixmapItem(pixmap, this);
    d->pixmap->setOffset(-pixmap.width()/2, -pixmap.height()/2);

    this->addToGroup(d->pixmap);
    this->layout();
}

void dtkDistributorLabel::layout(void)
{
    if(!d->text)
        return;

    if(!d->pixmap)
        return;

    QFontMetrics metrics(d->text->font());

    d->text->setPos(-(d->pixmap->pixmap().width()-metrics.width(d->text->toPlainText()))/2 - 5, d->pixmap->pixmap().height()/2);
}

// /////////////////////////////////////////////////////////////////
// dtkDistributorButton
// /////////////////////////////////////////////////////////////////

dtkDistributorButton::dtkDistributorButton(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{

}

dtkDistributorButton::~dtkDistributorButton(void)
{

}

void dtkDistributorButton::setPixmapNormal(const QPixmap& pixmap)
{
    this->pixmap_normal = pixmap;

    this->setPixmap(pixmap_normal);
    this->setOffset(-pixmap_normal.width()/2, -pixmap_normal.height()/2);
}

void dtkDistributorButton::setPixmapPressed(const QPixmap& pixmap)
{
    this->pixmap_pressed = pixmap;
}

void dtkDistributorButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPixmap(this->pixmap_pressed);
    this->setOffset(-pixmap_pressed.width()/2, -pixmap_pressed.height()/2);
}

void dtkDistributorButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPixmap(this->pixmap_normal);
    this->setOffset(-pixmap_normal.width()/2, -pixmap_normal.height()/2);

    emit clicked();
}

// /////////////////////////////////////////////////////////////////
// dtkDistributorCombo
// /////////////////////////////////////////////////////////////////

class dtkDistributorComboPrivate
{
public:
    QComboBox *combo;
};

dtkDistributorCombo::dtkDistributorCombo(QGraphicsItem *parent) : QGraphicsProxyWidget(parent), d(new dtkDistributorComboPrivate)
{
    d->combo = new QComboBox;
    d->combo->setAttribute(Qt::WA_TranslucentBackground);
    d->combo->setEditable(true);
    d->combo->addItem("nef.inria.fr");
    d->combo->setFixedWidth(128);

    this->setWidget(d->combo);
}

dtkDistributorCombo::~dtkDistributorCombo(void)
{
    delete d->combo;
    delete d;

    d = NULL;
}

QString dtkDistributorCombo::text(void) const
{
    return d->combo->currentText();
}

// /////////////////////////////////////////////////////////////////
// dtkDistributorNode
// /////////////////////////////////////////////////////////////////

class dtkDistributorNodePrivate
{
public:
    dtkDistributedNode *node;

    QGraphicsPixmapItem *information;
    QGraphicsPixmapItem *pixmap;
    QGraphicsTextItem *text;

    QGraphicsPixmapItem *panel;

    qreal orientation;
};

dtkDistributorNode::dtkDistributorNode(dtkDistributedNode *node, QGraphicsItem *parent) : QGraphicsItemGroup(parent), d(new dtkDistributorNodePrivate)
{
    d->orientation = 0;

    d->node = node;

    d->information = NULL;
    d->pixmap = NULL;
    d->text = NULL;

    d->panel = new QGraphicsPixmapItem(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-node-information-panel.png"), this);
    d->panel->setPos(-d->panel->pixmap().width()/2, -d->panel->pixmap().height()/2);
    d->panel->hide();

    this->setAcceptHoverEvents(true);

    this->layout();
}

dtkDistributorNode::~dtkDistributorNode(void)
{
    delete d;

    d = NULL;
}

bool dtkDistributorNode::filter(void)
{
    if(dtkDistributorController::instance()->states().testFlag(d->node->state()))
        return false;

    if(dtkDistributorController::instance()->brands().testFlag(d->node->brand()))
        return false;

    if(dtkDistributorController::instance()->networks().testFlag(d->node->network()))
        return false;

    foreach(dtkDistributedCpu *cpu, d->node->cpus())
        if(dtkDistributorController::instance()->architectures().testFlag(cpu->architecture()))
            return false;
    
    foreach(dtkDistributedCpu *cpu, d->node->cpus())
        if(dtkDistributorController::instance()->models().testFlag(cpu->model()))
            return false;
    
    foreach(dtkDistributedCpu *cpu, d->node->cpus())
        if(dtkDistributorController::instance()->cardinalities().testFlag(cpu->cardinality()))
            return false;
    
    return true;
}

qreal dtkDistributorNode::orientation(void)
{
    return d->orientation;
}

void dtkDistributorNode::setOrientation(qreal orientation)
{
    d->orientation = orientation;

    if(orientation >= 90) {
        d->pixmap->hide();
        d->text->hide();
        d->panel->show();
    } else {
        d->pixmap->show();
        d->text->show();
        d->panel->hide();
    }

    QTransform transform;
    transform.rotate(d->orientation, Qt::YAxis);

    this->setTransform(transform);
}

void dtkDistributorNode::layout(void)
{
    if(!d->pixmap)
        d->pixmap = new QGraphicsPixmapItem(this);

    if(d->node->state() == dtkDistributedNode::Free)
        d->pixmap->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-node-free.png"));

    if(d->node->state() == dtkDistributedNode::JobExclusive)
        d->pixmap->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-node-jobexclusive.png"));

    if(d->node->state() == dtkDistributedNode::Down)
        d->pixmap->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-node-down.png"));

    if(d->node->state() == dtkDistributedNode::Offline)
        d->pixmap->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-node-offline.png"));

    d->pixmap->setAcceptHoverEvents(true);
    d->pixmap->setOffset(-d->pixmap->pixmap().width()/2, -d->pixmap->pixmap().height()/2);

    if(!d->text)
        d->text = new QGraphicsTextItem(this);

    d->text->setPlainText(d->node->name());

    QFontMetrics metrics(d->text->font());

    d->text->setDefaultTextColor(Qt::white);
    d->text->setPos(
        -d->pixmap->pixmap().width()/2 + ((d->pixmap->pixmap().width() - metrics.width(d->text->toPlainText()))/2),
         d->pixmap->pixmap().height()/2-15);

    d->information = new QGraphicsPixmapItem(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-node-information.png"), d->pixmap);
    d->information->setPos(-5, -15);
    d->information->setZValue(d->pixmap->zValue()+1);
    d->information->hide();
}

void dtkDistributorNode::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    d->information->show();
}

void dtkDistributorNode::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    d->information->hide();
}

void dtkDistributorNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QRectF informationRect = QRectF(-5, -10, 16, 16);

    if (d->information->isVisible() && informationRect.contains(event->pos())) {
        d->information->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-node-information-pressed.png"));
        d->information->setOffset(-10, -10);
    }

    QRectF okRect = QRectF(-150 + 10, 200 - 30 - 40, 300 - 20, 50);

    if (d->panel->isVisible() && okRect.contains(event->pos())) {
        d->panel->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-node-information-panel-pressed.png"));
    }
}

void dtkDistributorNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QRectF informationRect = QRectF(-5, -10, 16, 16);

    if (d->information->isVisible() && informationRect.contains(event->pos())) {
        d->information->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-node-information.png"));
        d->information->setOffset(0, 0);

        // if(this->orientation())
        //     emit hideInformation(this);
        // else
            emit showInformation(this);
    }

    QRectF okRect = QRectF(-150 + 10, 200 - 30 - 40, 300 - 20, 50);

    if (d->panel->isVisible() && okRect.contains(event->pos())) {
        d->panel->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-node-information-panel.png"));
        emit hideInformation(this);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkDistributorScene
// /////////////////////////////////////////////////////////////////

class dtkDistributorScenePrivate
{
public:
    bool connected;
};

dtkDistributorScene::dtkDistributorScene(void) : QGraphicsScene(), d(new dtkDistributorScenePrivate)
{
    d->connected = false;

    this->setBackgroundBrush(QColor(0xae, 0xae, 0xae));
}

dtkDistributorScene::~dtkDistributorScene(void)
{
    delete d;

    d = NULL;
}

bool dtkDistributorScene::connected(void)
{
    return d->connected;
}

void dtkDistributorScene::setConnected(bool connected)
{
    d->connected = connected;
}

void dtkDistributorScene::drawBackground(QPainter *painter, const QRectF& rect)
{
    painter->save();
    painter->fillRect(rect, this->backgroundBrush());
    if(d->connected) {
        painter->setPen(Qt::darkGray);
        painter->setBrush(Qt::gray);
        painter->drawRect(QRectF(rect.topLeft(), rect.bottomLeft() + QPointF(150, 0)).adjusted(-1, -1, 0, 0));
    }
    painter->restore();
}
