/* dtkDistributorController.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Mar 31 18:25:32 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Mar 31 20:56:01 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 12
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTORCONTROLLER_H
#define DTKDISTRIBUTORCONTROLLER_H

#include "dtkDistributedCpu.h"
#include "dtkDistributedGpu.h"
#include "dtkDistributedNode.h"

#include <QtCore/QObject>

class dtkDistributorControllerPrivate;

class dtkDistributorController : public QObject
{
    Q_OBJECT

public:
    Q_DECLARE_FLAGS(Networks,      dtkDistributedNode::Network);
    Q_DECLARE_FLAGS(States,        dtkDistributedNode::State);
    Q_DECLARE_FLAGS(Brands,        dtkDistributedNode::Brand);

    Q_DECLARE_FLAGS(Architectures, dtkDistributedCpu::Architecture);
    Q_DECLARE_FLAGS(Models,        dtkDistributedCpu::Model);
    Q_DECLARE_FLAGS(Cardinalities, dtkDistributedCpu::Cardinality);

    Networks networks(void);
    States states(void);
    Brands brands(void);

    Architectures architectures(void);
    Models models(void);
    Cardinalities cardinalities(void);

public:
    static dtkDistributorController *instance(void);

signals:
    void updated(void);

public slots:
    void toggle(int index, int flag, bool checked);

protected:
    static dtkDistributorController *s_instance;
    
private:
     dtkDistributorController(void);
    ~dtkDistributorController(void);

private:
    dtkDistributorControllerPrivate *d;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(dtkDistributorController::Networks);
Q_DECLARE_OPERATORS_FOR_FLAGS(dtkDistributorController::States);
Q_DECLARE_OPERATORS_FOR_FLAGS(dtkDistributorController::Brands);

Q_DECLARE_OPERATORS_FOR_FLAGS(dtkDistributorController::Architectures);
Q_DECLARE_OPERATORS_FOR_FLAGS(dtkDistributorController::Models);
Q_DECLARE_OPERATORS_FOR_FLAGS(dtkDistributorController::Cardinalities);

#endif
