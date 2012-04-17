/* main.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Nov  2 10:48:42 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 10:38:17 2012 (+0100)
 *           By: tkloczko
 *     Update #: 38
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore/QObject>

#include <dtkComposerOld/dtkComposerNodeTransmitter.h>

#include <dtkCore/dtkAbstractData>
#include <dtkCore/dtkGlobal>
#include <dtkCore/dtkLog>

#include <dtkGui/dtkAboutBox>

// /////////////////////////////////////////////////////////////////
// Dummy concrete dtkAbstractData
// /////////////////////////////////////////////////////////////////

class dummyData : public dtkAbstractData
{
    Q_OBJECT

public:
     dummyData(void) : dtkAbstractData() {;}
    ~dummyData(void) {;}
        
public:
    QString identifier(void) const {return QString("Dummy data");}
};

// /////////////////////////////////////////////////////////////////

typedef dtkComposerNodeTransmitter<dummyData *> dummyDataTransmitter;
typedef dtkComposerNodeTransmitter<int> intTransmitter;

void run(void)
{
    // /////////////////////////////////////////////////////////////////
    // Transmitter basic use
    // /////////////////////////////////////////////////////////////////

    qDebug() << "Transmitter basic use";

    dummyData *data = new dummyData;

    dummyDataTransmitter transmitter;
    transmitter.setData(data);
    qDebug() << transmitter << transmitter.data();

    transmitter.clear();

    qDebug() << "";

    // /////////////////////////////////////////////////////////////////
    // Transmitter with QList
    // /////////////////////////////////////////////////////////////////

    qDebug() << "Transmitter with QList";

    QList<dummyData *> dummy_list;
    for (int i = 0; i < 10; i++)
        dummy_list << new dummyData;

    transmitter.setList(&dummy_list);

    qDebug() << transmitter << *(transmitter.list());

    transmitter.clear();

    // /////////////////////////////////////////////////////////////////
    // Transmitter with QVector
    // /////////////////////////////////////////////////////////////////

    qDebug() << "Transmitter with QVector";

    QVector<dummyData *> dummy_vector;
    for (int i = 0; i < 10; i++)
        dummy_vector << new dummyData;

    transmitter.setVector(&dummy_vector);

    qDebug() << transmitter << *(transmitter.vector());

    transmitter.clear();

    qDebug() << "";

    // /////////////////////////////////////////////////////////////////
    // Transmitter with atomic type
    // /////////////////////////////////////////////////////////////////

    qDebug() << "Transmitter with atomic type";

    intTransmitter *itransmitter = new intTransmitter;
    itransmitter->setData(501);

    qDebug() << itransmitter << itransmitter->data();

    itransmitter->clear();

    qDebug() << "";

    // /////////////////////////////////////////////////////////////////
    // Transmitter with QList of atomic type
    // /////////////////////////////////////////////////////////////////

    qDebug() << "Transmitter with QList of atomic type";

    QList<int> int_list;
    for (int i = 0; i < 10; i++)
        int_list << i;

    itransmitter->setList(&int_list);
    itransmitter->setCurrentData(7);

    qDebug() << itransmitter << *(itransmitter->list()) << itransmitter->data();

    itransmitter->clear();

    qDebug() << "";

    // /////////////////////////////////////////////////////////////////
    // Transmitter with QVector of atomic type
    // /////////////////////////////////////////////////////////////////

    qDebug() << "Transmitter with QVector of atomic type";

    QVector<int> int_vector;
    for (int i = 0; i < 10; i++)
        int_vector << i;

    itransmitter->setVector(&int_vector);
    itransmitter->setCurrentData(7);

    qDebug() << itransmitter << *(itransmitter->vector()) << itransmitter->data();

    qDebug() << "";


    // /////////////////////////////////////////////////////////////////
    // Transmitter through its abstraction
    // /////////////////////////////////////////////////////////////////

    qDebug() << "Transmitter through its abstraction";

    dtkComposerNodeAbstractTransmitter *atransmitter = itransmitter;
    atransmitter->setCurrentData(5);
    qDebug() << atransmitter << itransmitter->data();

    itransmitter->setList(&int_list);

    qDebug() << "";

}

// /////////////////////////////////////////////////////////////////
// main
// /////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    dtkAboutBox *about = new dtkAboutBox();
    about->setText("dtkComposerNodeTransmitter Example");
    about->setInformativeText(
        "dtkComposerNodeTransmitter enables to transmit data between two "
        "dtkComposerNodes without requiring any casting operation. It is not "
        "restricted to dtkAbstractData objects since it allows the transmission of "
        "atomic types and Qt containers (list and vector) of any type.");
    about->setDefaultButton(QMessageBox::Ok);
    about->open();

    int status = application.exec();

    run();

    return status;
}

#include "main.moc"
