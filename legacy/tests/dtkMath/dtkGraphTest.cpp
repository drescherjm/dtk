/* dtkGraphTest.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkGraphTest.h"

#include <dtkMath/dtkGraph.h>
#include <dtkMath/dtkGraphEdge.h>


// /////////////////////////////////////////////////////////////////
// dtkGraphTestObjectPrivate
// /////////////////////////////////////////////////////////////////

class dtkGraphTestObjectPrivate
{
public:
    dtkGraph *graph;

public:
    QObject *o1;
    QObject *o2;
    QObject *o3;
    QObject *o4;
    QObject *o5;

};

// /////////////////////////////////////////////////////////////////
// dtkGraphTestObject
// /////////////////////////////////////////////////////////////////

dtkGraphTestObject::dtkGraphTestObject(void) : d(new dtkGraphTestObjectPrivate)
{
}

dtkGraphTestObject::~dtkGraphTestObject(void)
{

}

void dtkGraphTestObject::initTestCase(void)
{
    d->graph = new dtkGraph;

    d->o1 = new QObject;
    d->o2 = new QObject;
    d->o3 = new QObject;
    d->o4 = new QObject;
    d->o5 = new QObject;

    d->o1->setObjectName("1");
    d->o2->setObjectName("2");
    d->o3->setObjectName("3");
    d->o4->setObjectName("4");
    d->o5->setObjectName("5");

    d->graph->addNode(d->o1);
    d->graph->addNode(d->o2);
    d->graph->addNode(d->o3);
    d->graph->addNode(d->o4);
    d->graph->addNode(d->o5);

    dtkGraphEdge e1;
    dtkGraphEdge e2;
    dtkGraphEdge e3;
    dtkGraphEdge e4;

    e1.setSource(d->o1);
    e1.setDestination(d->o2);
    e2.setSource(d->o1);
    e2.setDestination(d->o3);
    e3.setSource(d->o3);
    e3.setDestination(d->o4);
    e4.setSource(d->o5);
    e4.setDestination(d->o4);

    d->graph->addEdge(e1);
    d->graph->addEdge(e2);
    d->graph->addEdge(e3);
    d->graph->addEdge(e4);

}

void dtkGraphTestObject::init(void)
{

}

void dtkGraphTestObject::cleanup(void)
{

}

void dtkGraphTestObject::cleanupTestCase(void)
{

}

void dtkGraphTestObject::testSubGraph(void)
{
    dtkGraph sg = d->graph->subgraph(d->o1, d->o4);

    QList<QObject *> l = sg.nodes();

    // qDebug() << "subgraph:";
    // foreach (QObject *o, l ) {
    //     qDebug() << o;
    // }

    QVERIFY(l.count() == 4);
    QVERIFY(l.at(0) == d->o1);
    QVERIFY(l.at(1) == d->o3);
    QVERIFY(l.at(2) == d->o2);
    QVERIFY(l.at(3) == d->o4);


}

void dtkGraphTestObject::testSort(void)
{
    QList<QObject *> l = d->graph->rootNodes();

    // qDebug() << "root nodes:";
    // foreach (QObject *o, l ) {
    //     qDebug() << o;
    // }

    l = d->graph->topologicalSort();

    // qDebug() << "sorted nodes:";
    // foreach (QObject *o, l ) {
    //     qDebug() << o;
    // }

    QVERIFY(l.count() == 5);
    QVERIFY(l.at(0) == d->o1);
    QVERIFY(l.at(1) == d->o5);
    QVERIFY(l.at(2) == d->o3);
    QVERIFY(l.at(3) == d->o2);
    QVERIFY(l.at(4) == d->o4);

    QVERIFY(d->graph->nodes().count() == 5);
    QVERIFY(d->graph->edges().count() == 4);

    dtkGraphEdge e;

    e.setSource(d->o4);
    e.setDestination(d->o1);
    d->graph->addEdge(e);

    qDebug() << "Sort graph with a cycle";
    l = d->graph->topologicalSort();
    QVERIFY(l.count() == 0);

    d->graph->deleteEdge(e);

}


DTKTEST_NOGUI_MAIN(dtkGraphTest, dtkGraphTestObject)

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

