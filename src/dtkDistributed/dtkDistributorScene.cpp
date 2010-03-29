/* dtkDistributorScene.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Mar 21 18:30:50 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 29 09:52:09 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 189
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedNode.h"
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

    QGraphicsPixmapItem *pixmap;
    QGraphicsTextItem *text;
};

dtkDistributorNode::dtkDistributorNode(dtkDistributedNode *node, QGraphicsItem *parent) : QGraphicsItemGroup(parent), d(new dtkDistributorNodePrivate)
{
    d->node = node;

    d->pixmap = NULL;
    d->text = NULL;

    this->layout();
}

dtkDistributorNode::~dtkDistributorNode(void)
{
    delete d;

    d = NULL;
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

    d->pixmap->setOffset(-d->pixmap->pixmap().width()/2, -d->pixmap->pixmap().height()/2);

    if(!d->text)
        d->text = new QGraphicsTextItem(this);

    d->text->setPlainText(d->node->name());

    QFontMetrics metrics(d->text->font());

    d->text->setDefaultTextColor(Qt::white);
    d->text->setPos(
        -d->pixmap->pixmap().width()/2 + ((d->pixmap->pixmap().width() - metrics.width(d->text->toPlainText()))/2),
         d->pixmap->pixmap().height()/2-15);
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
