/* tstInspectorDistributed.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 16:17:24 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri May 27 17:29:42 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 68
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstInspectorDistributed.h"

#include <dtkGui/dtkInspectorBox.h>

#include <QtGui>

class tstInspectorDistributedPrivate
{
public:
    dtkInspectorBox *box_connection;
    dtkInspectorBox *box_submission;

    QPushButton *box_connection_connect;
    QPushButton *box_submission_submit;

    QLineEdit *box_connection_address;

    QVBoxLayout *box_connection_layout;
    QVBoxLayout *box_submission_layout;
};

tstInspectorDistributed::tstInspectorDistributed(QWidget *parent) : QFrame(parent), d(new tstInspectorDistributedPrivate)
{
    d->box_connection = new dtkInspectorBox(this);
    d->box_submission = new dtkInspectorBox(this);

    d->box_connection_connect = new QPushButton("Connect", d->box_connection);
    d->box_submission_submit  = new QPushButton("Submit", d->box_submission);

    d->box_connection_layout = new QVBoxLayout(d->box_connection);
    d->box_submission_layout = new QVBoxLayout(d->box_submission);
    
    d->box_connection_address = new QLineEdit(d->box_connection);
    d->box_connection_address->setText("nef-devel.inria.fr:9999");

    d->box_connection_layout->addWidget(d->box_connection_address);
    d->box_connection_layout->addStretch(1);
    d->box_connection_layout->addWidget(d->box_connection_connect);

    d->box_submission_layout->addWidget(d->box_submission_submit);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->box_connection);
    layout->addWidget(d->box_submission);

    QObject::connect(d->box_connection_connect, SIGNAL(clicked()), this, SLOT(onConnect()));
}

tstInspectorDistributed::~tstInspectorDistributed(void)
{
    delete d;

    d = NULL;
}

void tstInspectorDistributed::onConnect(void)
{
    emit connect(QUrl(d->box_connection_address->text()));
}

void tstInspectorDistributed::onSubmit(void)
{
    emit submit();
}
