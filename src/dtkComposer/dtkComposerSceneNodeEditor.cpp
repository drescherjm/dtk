/* dtkComposerSceneNodeEditor.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 10:10:15 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar 20 14:34:01 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 754
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerGraph.h"
#include "dtkComposerScene.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerSceneNodeEditor.h"
#include "dtkComposerSceneNodeEditor_p.h"
#include "dtkComposerScenePort.h"
#include "dtkComposerStack.h"
#include "dtkComposerStackCommand.h"

#include "dtkComposerNodeControlIf.h"
#include "dtkComposerNodeControlFor.h"
#include "dtkComposerNodeControlForEach.h"

#include "dtkComposerTransmitterVariant.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeEditorList
// /////////////////////////////////////////////////////////////////

dtkComposerSceneNodeEditorList::dtkComposerSceneNodeEditorList(QWidget *parent) : QListWidget(parent)
{
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameShape(QFrame::NoFrame);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    connect(this, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(onItemClicked(QListWidgetItem *)));
    connect(this, SIGNAL(itemChanged(QListWidgetItem *)), this, SLOT(onItemChanged(QListWidgetItem *)));
}

dtkComposerSceneNodeEditorList::~dtkComposerSceneNodeEditorList(void)
{

}

QSize dtkComposerSceneNodeEditorList::sizeHint(void) const
{
    return QSize(300, 100);
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

void dtkComposerSceneNodeEditorList::onItemClicked(QListWidgetItem *item)
{
    if(dtkComposerSceneNodeEditorListItem *i = dynamic_cast<dtkComposerSceneNodeEditorListItem *>(item)) {

        if (i->checkState() == Qt::Checked)
            i->port()->show();
        
        if (i->checkState() == Qt::Unchecked)
            i->port()->hide();
   
        if(!(i->port()->node()->parent()))
            return;
     
        int loop = i->port()->loop();

        if (!loop)
            return;

        dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(i->port()->node()->parent());
    
        foreach(dtkComposerSceneNodeComposite *block, control->blocks()) {
        
            foreach(dtkComposerScenePort *port, block->inputPorts()) {
                if(port->loop() == loop) {
                    if (i->checkState() == Qt::Checked)
                        port->show();                    
                    if (i->checkState() == Qt::Unchecked)
                        port->hide();
                }
            }
            
            foreach(dtkComposerScenePort *port, block->outputPorts()) {
                if(port->loop() == loop) {
                    if (i->checkState() == Qt::Checked)
                        port->show();                    
                    if (i->checkState() == Qt::Unchecked)
                        port->hide();
                }
            }
        }        
    }
}

void dtkComposerSceneNodeEditorList::onItemChanged(QListWidgetItem *item)
{
    if(item->text().isEmpty())
        return;

    if(dtkComposerSceneNodeEditorListItem *i = dynamic_cast<dtkComposerSceneNodeEditorListItem *>(item)) {        
   
     i->port()->setLabel(item->text());
        i->port()->update();
   
    
        if(!(i->port()->node()->parent()))
            return;
    
        int loop = i->port()->loop();

        if (!loop)
            return;

        dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(i->port()->node()->parent());
    
        foreach(dtkComposerSceneNodeComposite *block, control->blocks()) {
            
            foreach(dtkComposerScenePort *port, block->inputPorts()) {
                if(port->loop() == loop) {
                    port->setLabel(item->text());
                    port->update();
                }
            }
            
            foreach(dtkComposerScenePort *port, block->outputPorts()) {
                if(port->loop() == loop) {
                    port->setLabel(item->text());                    
                    port->update();
                }
            }
        }
    }
}

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeEditorListItem
// /////////////////////////////////////////////////////////////////

dtkComposerSceneNodeEditorListItem::dtkComposerSceneNodeEditorListItem(dtkComposerScenePort *port, dtkComposerSceneNodeEditorList *parent) : QListWidgetItem(parent, QListWidgetItem::UserType+1)
{
    this->m_port = port;

    this->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
    this->setText(port->label());
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

    d->loop_ports = new dtkComposerSceneNodeEditorList(this);
    d->input_ports = new dtkComposerSceneNodeEditorList(this);
    d->output_ports = new dtkComposerSceneNodeEditorList(this);

    d->add_loop_port = new QPushButton("+", this);
    d->add_loop_port->setEnabled(false);

    d->rem_loop_port = new QPushButton("-", this);
    d->rem_loop_port->setEnabled(false);

    d->add_input_port = new QPushButton("+", this);
    d->add_input_port->setEnabled(false);

    d->rem_input_port = new QPushButton("-", this);
    d->rem_input_port->setEnabled(false);

    d->add_output_port = new QPushButton("+", this);
    d->add_output_port->setEnabled(false);

    d->rem_output_port = new QPushButton("-", this);
    d->rem_output_port->setEnabled(false);

    d->edit = new QLineEdit(this);
    d->edit->setEnabled(false);

    d->spin_d = new QSpinBox(this);
    d->spin_d->setMinimum(-999999);
    d->spin_d->setMaximum(+999999);
    d->spin_d->setSingleStep(1);
    d->spin_d->setEnabled(false);
    d->spin_d->setVisible(false);
    d->spin_d->blockSignals(true);

    d->spin_f = new QDoubleSpinBox(this);
    d->spin_f->setMinimum(-999999);
    d->spin_f->setMaximum(+999999);
    d->spin_f->setSingleStep(1.0);
    d->spin_f->setEnabled(false);
    d->spin_f->setVisible(false);
    d->spin_f->blockSignals(true);

    d->selector = new QComboBox(this);
    d->selector->setEnabled(false);
    d->selector->setVisible(false);
    d->selector->blockSignals(true);

    QHBoxLayout *l_layout = new QHBoxLayout;
    l_layout->addWidget(d->add_loop_port);
    l_layout->addWidget(d->rem_loop_port);

    QHBoxLayout *i_layout = new QHBoxLayout;
    i_layout->addWidget(d->add_input_port);
    i_layout->addWidget(d->rem_input_port);

    QHBoxLayout *t_layout = new QHBoxLayout;
    t_layout->addWidget(new QLabel("Node:", this));
    t_layout->addWidget(d->edit);

    QHBoxLayout *o_layout = new QHBoxLayout;
    o_layout->addWidget(d->add_output_port);
    o_layout->addWidget(d->rem_output_port);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addLayout(t_layout);
    layout->addWidget(d->loop_ports);
    layout->addLayout(l_layout);
    layout->addWidget(d->selector);
    layout->addWidget(d->input_ports);
    layout->addLayout(i_layout);
    layout->addWidget(d->output_ports);
    layout->addLayout(o_layout);
    layout->addWidget(d->spin_d);
    layout->addWidget(d->spin_f);

    connect(d->add_loop_port, SIGNAL(clicked()), this, SLOT(addLoopPort()));
    connect(d->rem_loop_port, SIGNAL(clicked()), this, SLOT(removeLoopPort()));

    connect(d->add_input_port, SIGNAL(clicked()), this, SLOT(addInputPort()));
    connect(d->rem_input_port, SIGNAL(clicked()), this, SLOT(removeInputPort()));

    connect(d->add_output_port, SIGNAL(clicked()), this, SLOT(addOutputPort()));
    connect(d->rem_output_port, SIGNAL(clicked()), this, SLOT(removeOutputPort()));

    connect(d->edit, SIGNAL(textChanged(const QString&)), this, SLOT(onTitleChanged(const QString&)));

    connect(d->selector, SIGNAL(currentIndexChanged(int)), this, SLOT(onBlockChanged(int)));

    connect(d->spin_d, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
    connect(d->spin_f, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));
}

dtkComposerSceneNodeEditor::~dtkComposerSceneNodeEditor(void)
{
    delete d;

    d = NULL;
}

#include "dtkComposerNodeInteger.h"
#include "dtkComposerNodeReal.h"

void dtkComposerSceneNodeEditor::setNode(dtkComposerSceneNode *node)
{
    d->node = node;

    if(dtkComposerSceneNodeComposite *c = dynamic_cast<dtkComposerSceneNodeComposite *>(node)) {

        d->loop_ports->clear();
        
        d->input_ports->clear();
        
        foreach(dtkComposerScenePort *port, node->inputPorts())
            d->input_ports->addInputPort(port);
        
        d->output_ports->clear();
        
        foreach(dtkComposerScenePort *port, node->outputPorts())
            d->output_ports->addOutputPort(port);

        d->add_loop_port->setEnabled(false);
        d->rem_loop_port->setEnabled(false);
        d->add_input_port->setEnabled(true);
        d->rem_input_port->setEnabled(true);
        d->add_output_port->setEnabled(true);
        d->rem_output_port->setEnabled(true);

        d->selector->blockSignals(true);
        d->selector->setVisible(false);
        d->selector->setEnabled(false);

    } else if(dtkComposerSceneNodeControl *c = dynamic_cast<dtkComposerSceneNodeControl *>(node)) {

        d->loop_ports->clear();

        QList<int> loop_ports;

        foreach(dtkComposerSceneNodeComposite *block, c->blocks()) {
        
            foreach(dtkComposerScenePort *port, block->inputPorts()) {
                if(port->loop() && !loop_ports.contains(port->loop())) {
                    d->loop_ports->addInputPort(port);
                    loop_ports << port->loop();
                }
            }
            
            foreach(dtkComposerScenePort *port, block->outputPorts()) {
                if(port->loop() && !loop_ports.contains(port->loop())) {
                    d->loop_ports->addOutputPort(port);
                    loop_ports << port->loop();
                }
            }
        }

        d->input_ports->clear();
        d->output_ports->clear();

        if(dtkComposerNodeControlIf *i_node = dynamic_cast<dtkComposerNodeControlIf *>(node->wrapee())) {
            d->add_loop_port->setEnabled(false);
            d->rem_loop_port->setEnabled(false);
        } else {
            d->add_loop_port->setEnabled(true);
            d->rem_loop_port->setEnabled(true);
        }

        d->add_input_port->setEnabled(true);
        d->rem_input_port->setEnabled(true);
        d->add_output_port->setEnabled(true);
        d->rem_output_port->setEnabled(true);

        d->selector->clear();

        foreach(dtkComposerSceneNodeComposite *block, c->blocks())
            d->selector->addItem(block->title());

        d->selector->blockSignals(false);
        d->selector->setVisible(true);
        d->selector->setEnabled(true);
        d->selector->setCurrentIndex(0);

    } else {

        d->loop_ports->clear();

        d->input_ports->clear();

        foreach(dtkComposerScenePort *port, node->inputPorts())
            d->input_ports->addInputPort(port);

        d->output_ports->clear();

        foreach(dtkComposerScenePort *port, node->outputPorts())
            d->output_ports->addOutputPort(port);

        d->add_loop_port->setEnabled(false);
        d->rem_loop_port->setEnabled(false);
        d->add_input_port->setEnabled(false);
        d->rem_input_port->setEnabled(false);
        d->add_output_port->setEnabled(false);
        d->rem_output_port->setEnabled(false);

        d->selector->blockSignals(true);
        d->selector->setVisible(false);
        d->selector->setEnabled(false);

        if(dtkComposerNodeInteger *i_node = dynamic_cast<dtkComposerNodeInteger *>(node->wrapee())) {

            d->spin_d->blockSignals(false);
            d->spin_d->setVisible(true);
            d->spin_d->setEnabled(true);
            d->spin_d->setValue(i_node->value());

            d->spin_f->blockSignals(true);
            d->spin_f->setVisible(false);
            d->spin_f->setEnabled(false);

        } else if(dtkComposerNodeReal *r_node = dynamic_cast<dtkComposerNodeReal *>(node->wrapee())) {

            d->spin_f->blockSignals(false);
            d->spin_f->setVisible(true);
            d->spin_f->setEnabled(true);
            d->spin_f->setValue(r_node->value());

            d->spin_d->blockSignals(true);
            d->spin_d->setVisible(false);
            d->spin_d->setEnabled(false);

        } else {

            d->spin_d->blockSignals(true);
            d->spin_d->setVisible(false);
            d->spin_d->setEnabled(false);

            d->spin_f->blockSignals(true);
            d->spin_f->setVisible(false);
            d->spin_f->setEnabled(false);
        }
    }

    d->edit->setText(d->node->title());
    d->edit->setEnabled(true);
}

void dtkComposerSceneNodeEditor::setScene(dtkComposerScene *scene)
{
    d->scene = scene;

    connect(d->scene, SIGNAL(selectedNode(dtkComposerSceneNode *)), this, SLOT(setNode(dtkComposerSceneNode *)));
    connect(d->scene, SIGNAL(selectionCleared()), this, SLOT(clear()));
}

void dtkComposerSceneNodeEditor::setStack(dtkComposerStack *stack)
{
    d->stack = stack;
}

void dtkComposerSceneNodeEditor::setGraph(dtkComposerGraph *graph)
{
    d->graph = graph;
}

void dtkComposerSceneNodeEditor::clear(void)
{
    d->node = NULL;

    d->loop_ports->clear();
    d->input_ports->clear();
    d->output_ports->clear();

    d->add_loop_port->setEnabled(false);
    d->rem_loop_port->setEnabled(false);

    d->add_input_port->setEnabled(false);
    d->rem_input_port->setEnabled(false);

    d->add_output_port->setEnabled(false);
    d->rem_output_port->setEnabled(false);

    d->edit->clear();
    d->edit->setEnabled(false);

    d->selector->clear();
    d->selector->setEnabled(false);
    d->selector->setVisible(false);

    d->spin_d->blockSignals(true);
    d->spin_d->setVisible(false);
    d->spin_d->setEnabled(false);
    
    d->spin_f->blockSignals(true);
    d->spin_f->setVisible(false);
    d->spin_f->setEnabled(false);
}

void dtkComposerSceneNodeEditor::addLoopPort(void)
{
    dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(d->node);

    if(!control)
        return;

    dtkComposerStackCommandCreatePort *command_cond_i;
    dtkComposerStackCommandCreatePort *command_body_i;
    dtkComposerStackCommandCreatePort *command_body_o;
    dtkComposerStackCommandCreatePort *command_incr_i;
    dtkComposerStackCommandCreatePort *command_incr_o;

    dtkComposerStackCommandCreateEdge *command_edge_bc;

    command_body_i = new dtkComposerStackCommandCreatePort;
    command_body_i->setScene(d->scene);
    command_body_i->setNode(control->block("Body"));
    command_body_i->setType(dtkComposerScenePort::Input);
    command_body_i->setKind(dtkComposerTransmitter::Variant);

    command_body_o = new dtkComposerStackCommandCreatePort;
    command_body_o->setScene(d->scene);
    command_body_o->setNode(control->block("Body"));
    command_body_o->setType(dtkComposerScenePort::Output);
    command_body_o->setKind(dtkComposerTransmitter::Variant);

    if(dtkComposerNodeControlForEach *f_node = dynamic_cast<dtkComposerNodeControlForEach *>(d->node->wrapee())) {
        command_cond_i = NULL;
    } else {
        command_cond_i = new dtkComposerStackCommandCreatePort;
        command_cond_i->setScene(d->scene);
        command_cond_i->setNode(control->block("Conditional"));
        command_cond_i->setType(dtkComposerScenePort::Input);
        command_cond_i->setKind(dtkComposerTransmitter::Proxy);
    }

    if(dtkComposerNodeControlFor *f_node = dynamic_cast<dtkComposerNodeControlFor *>(d->node->wrapee())) {
        command_incr_i = new dtkComposerStackCommandCreatePort;
        command_incr_i->setScene(d->scene);
        command_incr_i->setNode(control->block("Increment"));
        command_incr_i->setType(dtkComposerScenePort::Input);
        command_incr_i->setKind(dtkComposerTransmitter::Proxy);
        
        command_incr_o = new dtkComposerStackCommandCreatePort;
        command_incr_o->setScene(d->scene);
        command_incr_o->setNode(control->block("Increment"));
        command_incr_o->setType(dtkComposerScenePort::Output);
        command_incr_o->setKind(dtkComposerTransmitter::Variant);
    } else {
        command_incr_i = NULL;
        command_incr_o = NULL;
    }

// /////////////////////////////////////////////////////////////////
// Push to the stack
// /////////////////////////////////////////////////////////////////

    if(command_cond_i)
        d->stack->push(command_cond_i);

    d->stack->push(command_body_i);
    d->stack->push(command_body_o);

    if(command_incr_i)
        d->stack->push(command_incr_i);

    if(command_incr_o)
        d->stack->push(command_incr_o);

// /////////////////////////////////////////////////////////////////
// Loop them together
// /////////////////////////////////////////////////////////////////

    static QHash<dtkComposerSceneNodeControl *, int> loop_ids;

    if(!loop_ids.contains(control))
        loop_ids[control] = 0;

    loop_ids[control] = loop_ids[control]+1;

    if (command_cond_i)
        command_cond_i->port()->setLoop(loop_ids[control]); 

    command_body_i->port()->setLoop(loop_ids[control]);
    command_body_o->port()->setLoop(loop_ids[control]);

    if (command_incr_i)
        command_incr_i->port()->setLoop(loop_ids[control]);

    if (command_incr_o)
        command_incr_o->port()->setLoop(loop_ids[control]);

// /////////////////////////////////////////////////////////////////
// Connect proxy and variant transmitters
// /////////////////////////////////////////////////////////////////

    if (command_cond_i) {

        control->block("Body")->wrapee()->receivers().last()->appendNext(control->block("Conditional")->wrapee()->receivers().last());
        control->block("Conditional")->wrapee()->receivers().last()->appendPrevious(control->block("Body")->wrapee()->receivers().last());
    }
    
    if (command_incr_i) {

        control->block("Body")->wrapee()->emitters().last()->appendNext(control->block("Increment")->wrapee()->receivers().last());
        control->block("Increment")->wrapee()->receivers().last()->appendPrevious(control->block("Body")->wrapee()->emitters().last());

        dynamic_cast<dtkComposerTransmitterVariant *>(control->block("Increment")->wrapee()->emitters().last())->setTwin(dynamic_cast<dtkComposerTransmitterVariant *>(control->block("Body")->wrapee()->receivers().last()));

    } else {

        dynamic_cast<dtkComposerTransmitterVariant *>(control->block("Body")->wrapee()->emitters().last())->setTwin(dynamic_cast<dtkComposerTransmitterVariant *>(control->block("Body")->wrapee()->receivers().last()));
    }

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

    int index = -1;

    if(d->selector->isVisible())
        index = d->selector->currentIndex();

    this->setNode(d->node);

    if(index > 0)
        d->selector->setCurrentIndex(index);
}

void dtkComposerSceneNodeEditor::removeLoopPort(void)
{
    dtkComposerSceneNodeEditorListItem *item = dynamic_cast<dtkComposerSceneNodeEditorListItem *>(d->loop_ports->currentItem());

    if(!item)
        return;

    int loop = item->port()->loop();

    dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(d->node);

    foreach(dtkComposerSceneNodeComposite *block, control->blocks()) {

        foreach(dtkComposerScenePort *port, block->inputPorts()) {
            if(port->loop() == loop) {
                dtkComposerStackCommandDestroyPort *command = new dtkComposerStackCommandDestroyPort;
                command->setScene(d->scene);
                command->setGraph(d->graph);
                command->setNode(block);
                command->setPort(port);
                d->stack->push(command);
            }
        }

        foreach(dtkComposerScenePort *port, block->outputPorts()) {
            if(port->loop() == loop) {
                dtkComposerStackCommandDestroyPort *command = new dtkComposerStackCommandDestroyPort;
                command->setScene(d->scene);
                command->setGraph(d->graph);
                command->setNode(block);
                command->setPort(port);
                d->stack->push(command);
            }
        }
    }

    int index = -1;

    if(d->selector->isVisible())
        index = d->selector->currentIndex();

    this->setNode(d->node);

    if(index > 0)
        d->selector->setCurrentIndex(index);
}

void dtkComposerSceneNodeEditor::addInputPort(void)
{
    dtkComposerStackCommandCreatePort *command;

    if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(d->node)) {

        command = new dtkComposerStackCommandCreatePort;
        command->setScene(d->scene);
        command->setNode(dynamic_cast<dtkComposerSceneNodeComposite *>(control->blocks().at(d->selector->currentIndex())));
        command->setType(dtkComposerScenePort::Input);

    } else {

        command = new dtkComposerStackCommandCreatePort;
        command->setScene(d->scene);
        command->setNode(dynamic_cast<dtkComposerSceneNodeComposite *>(d->node));
        command->setType(dtkComposerScenePort::Input);

    }

    d->stack->push(command);

    int index = -1;

    if(d->selector->isVisible())
        index = d->selector->currentIndex();

    this->setNode(d->node);

    if(index > 0)
        d->selector->setCurrentIndex(index);
}

void dtkComposerSceneNodeEditor::removeInputPort(void)
{
    dtkComposerSceneNodeEditorListItem *item = dynamic_cast<dtkComposerSceneNodeEditorListItem *>(d->input_ports->currentItem());

    if(!item)
        return;

    dtkComposerStackCommandDestroyPort *command;

    if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(d->node)) {

        command = new dtkComposerStackCommandDestroyPort;
        command->setScene(d->scene);
        command->setGraph(d->graph);
        command->setNode(dynamic_cast<dtkComposerSceneNodeComposite *>(control->blocks().at(d->selector->currentIndex())));
        command->setPort(item->port());

    } else {

        command = new dtkComposerStackCommandDestroyPort;
        command->setScene(d->scene);
        command->setGraph(d->graph);
        command->setNode(dynamic_cast<dtkComposerSceneNodeComposite *>(d->node));
        command->setPort(item->port());
    }
    
    d->stack->push(command);

    int index = -1;

    if(d->selector->isVisible())
        index = d->selector->currentIndex();

    this->setNode(d->node);

    if(index > 0)
        d->selector->setCurrentIndex(index);
}

void dtkComposerSceneNodeEditor::addOutputPort(void)
{
    dtkComposerStackCommandCreatePort *command;

    if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(d->node)) {

        command = new dtkComposerStackCommandCreatePort;
        command->setScene(d->scene);
        command->setNode(dynamic_cast<dtkComposerSceneNodeComposite *>(control->blocks().at(d->selector->currentIndex())));
        command->setType(dtkComposerScenePort::Output);

    } else {

        command = new dtkComposerStackCommandCreatePort;
        command->setScene(d->scene);
        command->setNode(dynamic_cast<dtkComposerSceneNodeComposite *>(d->node));
        command->setType(dtkComposerScenePort::Output);

    }

    d->stack->push(command);

    int index = -1;

    if(d->selector->isVisible())
        index = d->selector->currentIndex();

    this->setNode(d->node);

    if(index > 0)
        d->selector->setCurrentIndex(index);
}

void dtkComposerSceneNodeEditor::removeOutputPort(void)
{
    dtkComposerSceneNodeEditorListItem *item = dynamic_cast<dtkComposerSceneNodeEditorListItem *>(d->output_ports->currentItem());

    if(!item)
        return;

    dtkComposerStackCommandDestroyPort *command;

    if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(d->node)) {

        command = new dtkComposerStackCommandDestroyPort;
        command->setScene(d->scene);
        command->setGraph(d->graph);
        command->setNode(dynamic_cast<dtkComposerSceneNodeComposite *>(control->blocks().at(d->selector->currentIndex())));
        command->setPort(item->port());

    } else {

        command = new dtkComposerStackCommandDestroyPort;
        command->setScene(d->scene);
        command->setGraph(d->graph);
        command->setNode(dynamic_cast<dtkComposerSceneNodeComposite *>(d->node));
        command->setPort(item->port());
    }

    d->stack->push(command);

    int index = -1;

    if(d->selector->isVisible())
        index = d->selector->currentIndex();

    this->setNode(d->node);

    if(index > 0)
        d->selector->setCurrentIndex(index);
}

void dtkComposerSceneNodeEditor::onBlockChanged(int index)
{
    if(index < 0)
        return;

    dtkComposerSceneNodeControl *c = dynamic_cast<dtkComposerSceneNodeControl *>(d->node);

    if(!c)
        return;

    d->input_ports->clear();

    foreach(dtkComposerScenePort *port, c->blocks().at(index)->inputPorts())
        if(!port->loop())
            d->input_ports->addInputPort(port);

    d->output_ports->clear();

    foreach(dtkComposerScenePort *port, c->blocks().at(index)->outputPorts())
        if(!port->loop())
            d->output_ports->addOutputPort(port);
}

void dtkComposerSceneNodeEditor::onTitleChanged(const QString& text)
{
    if (d->node) {
        d->node->setTitle(d->edit->text());
        d->node->update();
    }
}

void dtkComposerSceneNodeEditor::onValueChanged(int value)
{
    if(dtkComposerNodeInteger *i_node = dynamic_cast<dtkComposerNodeInteger *>(d->node->wrapee()))
        i_node->setValue(value);
}

void dtkComposerSceneNodeEditor::onValueChanged(double value)
{
    if(dtkComposerNodeReal *r_node = dynamic_cast<dtkComposerNodeReal *>(d->node->wrapee()))
        r_node->setValue(value);
}
