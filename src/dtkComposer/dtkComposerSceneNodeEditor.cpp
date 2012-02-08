/* dtkComposerSceneNodeEditor.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 10:10:15 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  8 11:29:46 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 147
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerScene.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeEditor.h"
#include "dtkComposerSceneNodeEditor_p.h"
#include "dtkComposerScenePort.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeEditorList
// /////////////////////////////////////////////////////////////////

dtkComposerSceneNodeEditorList::dtkComposerSceneNodeEditorList(QWidget *parent) : QListWidget(parent)
{
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameShape(QFrame::NoFrame);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    connect(this, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(onItemChanged(QListWidgetItem *)));
}

dtkComposerSceneNodeEditorList::~dtkComposerSceneNodeEditorList(void)
{

}

void dtkComposerSceneNodeEditorList::addInputPort(dtkComposerScenePort *port)
{
    dtkComposerSceneNodeEditorListItem *item = new dtkComposerSceneNodeEditorListItem(port, this);
    port->isVisible() ? item->setCheckState(Qt::Checked) : item->setCheckState(Qt::Unchecked);

    this->addItem(item);
}

void dtkComposerSceneNodeEditorList::addOutputPort(dtkComposerScenePort *port)
{
    dtkComposerSceneNodeEditorListItem *item = new dtkComposerSceneNodeEditorListItem(port, this);
    port->isVisible() ? item->setCheckState(Qt::Checked) : item->setCheckState(Qt::Unchecked);

    this->addItem(item);
}

void dtkComposerSceneNodeEditorList::onItemChanged(QListWidgetItem *item)
{
    if(dtkComposerSceneNodeEditorListItem *i = dynamic_cast<dtkComposerSceneNodeEditorListItem *>(item)) {        
        if (i->checkState() == Qt::Checked)
            i->port()->show();

        if (i->checkState() == Qt::Unchecked)
            i->port()->hide();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeEditorListItem
// /////////////////////////////////////////////////////////////////

dtkComposerSceneNodeEditorListItem::dtkComposerSceneNodeEditorListItem(dtkComposerScenePort *port, dtkComposerSceneNodeEditorList *parent) : QListWidgetItem(parent, QListWidgetItem::UserType+1)
{
    this->m_port = port;

    this->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
    this->setText(QString::number(port->id()));
}

dtkComposerSceneNodeEditorListItem::~dtkComposerSceneNodeEditorListItem(void)
{

}

int dtkComposerSceneNodeEditorListItem::type(void) const
{
    return QListWidgetItem::UserType+1;
}

dtkComposerScenePort *dtkComposerSceneNodeEditorListItem::port(void)
{
    return m_port;
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkComposerSceneNodeEditor::dtkComposerSceneNodeEditor(QWidget *parent) : QWidget(parent), d(new dtkComposerSceneNodeEditorPrivate)
{
    d->node = NULL;
    d->scene = NULL;

    d->input_ports = new dtkComposerSceneNodeEditorList(this);
    d->output_ports = new dtkComposerSceneNodeEditorList(this);

    d->add_input_port = new QPushButton("+", this);
    d->add_input_port->setEnabled(false);

    d->rem_input_port = new QPushButton("-", this);
    d->rem_input_port->setEnabled(false);

    QHBoxLayout *i_layout = new QHBoxLayout;
    i_layout->addWidget(d->add_input_port);
    i_layout->addWidget(d->rem_input_port);

    d->add_output_port = new QPushButton("+", this);
    d->add_output_port->setEnabled(false);

    d->rem_output_port = new QPushButton("-", this);
    d->rem_output_port->setEnabled(false);

    QHBoxLayout *o_layout = new QHBoxLayout;
    o_layout->addWidget(d->add_output_port);
    o_layout->addWidget(d->rem_output_port);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->input_ports);
    layout->addLayout(i_layout);
    layout->addWidget(d->output_ports);
    layout->addLayout(o_layout);

    connect(d->add_input_port, SIGNAL(clicked()), this, SLOT(addInputPort()));
    connect(d->rem_input_port, SIGNAL(clicked()), this, SLOT(removeInputPort()));

    connect(d->add_output_port, SIGNAL(clicked()), this, SLOT(addOutputPort()));
    connect(d->rem_output_port, SIGNAL(clicked()), this, SLOT(removeOutputPort()));
}

dtkComposerSceneNodeEditor::~dtkComposerSceneNodeEditor(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneNodeEditor::setNode(dtkComposerSceneNode *node)
{
    d->node = node;

    d->input_ports->clear();
    
    foreach(dtkComposerScenePort *port, node->inputPorts())
        d->input_ports->addInputPort(port);

    d->output_ports->clear();

    foreach(dtkComposerScenePort *port, node->outputPorts())
        d->output_ports->addOutputPort(port);

    if(dtkComposerSceneNodeComposite *c = dynamic_cast<dtkComposerSceneNodeComposite *>(node)) {
        d->add_input_port->setEnabled(true);
        d->rem_input_port->setEnabled(true);
        d->add_output_port->setEnabled(true);
        d->rem_output_port->setEnabled(true);
    } else {
        d->add_input_port->setEnabled(false);
        d->rem_input_port->setEnabled(false);
        d->add_output_port->setEnabled(false);
        d->rem_output_port->setEnabled(false);
    }
}

void dtkComposerSceneNodeEditor::setScene(dtkComposerScene *scene)
{
    d->scene = scene;

    connect(d->scene, SIGNAL(selectedNode(dtkComposerSceneNode *)), this, SLOT(setNode(dtkComposerSceneNode *)));
    connect(d->scene, SIGNAL(selectionCleared()), this, SLOT(clear()));
}

void dtkComposerSceneNodeEditor::clear(void)
{
    d->node = NULL;

    d->input_ports->clear();
    d->output_ports->clear();

    d->add_input_port->setEnabled(false);
    d->rem_input_port->setEnabled(false);

    d->add_output_port->setEnabled(false);
    d->rem_output_port->setEnabled(false);
}

void dtkComposerSceneNodeEditor::addInputPort(void)
{
    qDebug() << __func__;
}

void dtkComposerSceneNodeEditor::removeInputPort(void)
{
    qDebug() << __func__;
}

void dtkComposerSceneNodeEditor::addOutputPort(void)
{
    qDebug() << __func__;
}

void dtkComposerSceneNodeEditor::removeOutputPort(void)
{
    qDebug() << __func__;
}
