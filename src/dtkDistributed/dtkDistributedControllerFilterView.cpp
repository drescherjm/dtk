/* dtkDistributedControllerFilterView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr 10 10:12:41 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 10 15:39:52 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 174
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedControllerFilterView.h"

class dtkDistributedControllerFilterViewPrivate
{
public:
};

dtkDistributedControllerFilterView::dtkDistributedControllerFilterView(QWidget *parent) : QTreeWidget(parent), d(new dtkDistributedControllerFilterViewPrivate)
{
    QGroupBox *network_box = new QGroupBox(this);
    QGroupBox *state_box = new QGroupBox(this);
    QGroupBox *brand_box = new QGroupBox(this);
    QGroupBox *arch_box = new QGroupBox(this);
    QGroupBox *model_box = new QGroupBox(this);

    QRadioButton *network_1 = new QRadioButton("Ethernet1G", network_box);
    QRadioButton *network_2 = new QRadioButton("Ethernet10G", network_box);
    QRadioButton *network_3 = new QRadioButton("Myrinet2G", network_box);
    QRadioButton *network_4 = new QRadioButton("Myrinet10G", network_box);
    QRadioButton *network_5 = new QRadioButton("Infiniband10G", network_box);
    QRadioButton *network_6 = new QRadioButton("Infiniband20G", network_box);
    QRadioButton *network_7 = new QRadioButton("Infiniband40G", network_box);

    QRadioButton *state_1 = new QRadioButton("Free", state_box);
    QRadioButton *state_2 = new QRadioButton("Busy", state_box);
    QRadioButton *state_3 = new QRadioButton("Down", state_box);

    QRadioButton *brand_1 = new QRadioButton("Hp", brand_box);
    QRadioButton *brand_2 = new QRadioButton("Ibm", brand_box);
    QRadioButton *brand_3 = new QRadioButton("Dell", brand_box);
    QRadioButton *brand_4 = new QRadioButton("Carri", brand_box);

    QRadioButton *arch_1 = new QRadioButton("x86", arch_box);
    QRadioButton *arch_2 = new QRadioButton("x86_64", arch_box);

    QRadioButton *model_1 = new QRadioButton("Xeon", model_box);
    QRadioButton *model_2 = new QRadioButton("Opteron", model_box);

    QButtonGroup *network_group = new QButtonGroup(this);
    network_group->setExclusive(false);
    network_group->addButton(network_1);
    network_group->addButton(network_2);
    network_group->addButton(network_3);
    network_group->addButton(network_4);
    network_group->addButton(network_5);
    network_group->addButton(network_6);
    network_group->addButton(network_7);

    QButtonGroup *state_group = new QButtonGroup(this);
    state_group->setExclusive(false);
    state_group->addButton(state_1);
    state_group->addButton(state_2);
    state_group->addButton(state_3);

    QButtonGroup *brand_group = new QButtonGroup(this);
    brand_group->setExclusive(false);
    brand_group->addButton(brand_1);
    brand_group->addButton(brand_2);
    brand_group->addButton(brand_3);
    brand_group->addButton(brand_4);

    QButtonGroup *arch_group = new QButtonGroup(this);
    arch_group->setExclusive(false);
    arch_group->addButton(arch_1);
    arch_group->addButton(arch_2);

    QButtonGroup *model_group = new QButtonGroup(this);
    model_group->setExclusive(false);
    model_group->addButton(model_1);
    model_group->addButton(model_2);

    QVBoxLayout *network_layout = new QVBoxLayout;
    network_layout->setContentsMargins(0, 0, 0, 0);
    network_layout->addWidget(network_1);
    network_layout->addWidget(network_2);
    network_layout->addWidget(network_3);
    network_layout->addWidget(network_4);
    network_layout->addWidget(network_5);
    network_layout->addWidget(network_6);
    network_layout->addWidget(network_7);

    QVBoxLayout *state_layout = new QVBoxLayout;
    state_layout->setContentsMargins(0, 0, 0, 0);
    state_layout->addWidget(state_1);
    state_layout->addWidget(state_2);
    state_layout->addWidget(state_3);

    QVBoxLayout *brand_layout = new QVBoxLayout;
    brand_layout->setContentsMargins(0, 0, 0, 0);
    brand_layout->addWidget(brand_1);
    brand_layout->addWidget(brand_2);
    brand_layout->addWidget(brand_3);
    brand_layout->addWidget(brand_4);

    QVBoxLayout *arch_layout = new QVBoxLayout;
    arch_layout->setContentsMargins(0, 0, 0, 0);
    arch_layout->addWidget(arch_1);
    arch_layout->addWidget(arch_2);

    QVBoxLayout *model_layout = new QVBoxLayout;
    model_layout->setContentsMargins(0, 0, 0, 0);
    model_layout->addWidget(model_1);
    model_layout->addWidget(model_2);

    network_box->setLayout(network_layout);
    state_box->setLayout(state_layout);
    brand_box->setLayout(brand_layout);
    arch_box->setLayout(arch_layout);
    model_box->setLayout(model_layout);

    QTreeWidgetItem *network_item = new QTreeWidgetItem(this, QStringList() << "Network");
    QTreeWidgetItem *state_item = new QTreeWidgetItem(this, QStringList() << "State");
    QTreeWidgetItem *brand_item = new QTreeWidgetItem(this, QStringList() << "Brand");
    QTreeWidgetItem *arch_item = new QTreeWidgetItem(this, QStringList() << "Architecture");
    QTreeWidgetItem *model_item = new QTreeWidgetItem(this, QStringList() << "Model");

    this->addTopLevelItem(network_item);
    this->addTopLevelItem(state_item);
    this->addTopLevelItem(brand_item);
    this->addTopLevelItem(arch_item);
    this->addTopLevelItem(model_item);

    network_item = new QTreeWidgetItem(network_item);
    state_item = new QTreeWidgetItem(state_item);
    brand_item = new QTreeWidgetItem(brand_item);
    arch_item = new QTreeWidgetItem(arch_item);
    model_item = new QTreeWidgetItem(model_item);

    this->setItemWidget(network_item, 0, network_box);
    this->setItemWidget(state_item, 0, state_box);
    this->setItemWidget(brand_item, 0, brand_box);
    this->setItemWidget(arch_item, 0, arch_box);
    this->setItemWidget(model_item, 0, model_box);

    this->setHeaderLabel("Filters");
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameStyle(QFrame::NoFrame);
}

dtkDistributedControllerFilterView::~dtkDistributedControllerFilterView(void)
{
    delete d;

    d = NULL;
}
