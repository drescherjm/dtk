/* main.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Sun May  6 18:46:00 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jul 16 09:58:02 2012 (+0200)
 *           By: tkloczko
 *     Update #: 180
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore/QObject>

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkGlobal.h>

#include <dtkComposer/dtkComposerTransmitterEmitter.h>
#include <dtkComposer/dtkComposerTransmitterReceiver.h>
#include <dtkComposer/dtkComposerTransmitterVariant.h>

#include <dtkContainer>

#include <dtkLog/dtkLog.h>

#include <dtkGui/dtkAboutBox.h>

// /////////////////////////////////////////////////////////////////

void run(void)
{
    // --- Definition of a vector of vector of real

    dtkContainerVector< dtkContainerVector<qreal> > meta_vector_0;

    // --- Initialize vectors of real

    dtkContainerVector<qreal> vector_0;
    dtkContainerVector<qreal> vector_1;
    dtkContainerVector<qreal> vector_2;

    int size = 11;

    for (int i = 0; i < size; ++i) {
        vector_0 << i * 3.14159;
        vector_1 << i * 1. << i * 1.1;
        vector_2 << i * 0.45;
    }

    // --- Puts first vector in the meta vector

    meta_vector_0 << vector_0;

    // --- Copy of the meta vector and fill the copy with the second vector

    dtkContainerVector< dtkContainerVector<qreal> > meta_vector_1;
    meta_vector_1 = meta_vector_0;

    meta_vector_1 << vector_1;

    // --- Same as previously

    dtkContainerVector< dtkContainerVector<qreal> > meta_vector_2;
    meta_vector_2 = meta_vector_1;

    meta_vector_2 << vector_2;

    // --- Check the size of the vectors and meta vectors

    qDebug() << "Size of meta vectors:";
    qDebug() << "- meta_vector_0:" << meta_vector_0.count();
    qDebug() << "- meta_vector_1:" << meta_vector_1.count();
    qDebug() << "- meta_vector_2:" << meta_vector_2.count();
    
    qDebug() << "";
    
    qDebug() << "Size of vectors contained by meta_vector_2:";
    qDebug() << "- vector_0:" << meta_vector_2.at(0).count(); 
    qDebug() << "- vector_1:" << meta_vector_2.at(1).count(); 
    qDebug() << "- vector_2:" << meta_vector_2.at(2).count(); 

    qDebug() << "";

    // --- Simulation of transmission using emitter, variant and receiver transmitters    

    dtkAbstractContainerWrapper wrapper_0 = dtkContainerVectorWrapper<dtkContainerVector<qreal> >(meta_vector_0);

    dtkComposerTransmitterVariant emitter_0;
    emitter_0.setData(wrapper_0);

    dtkAbstractContainerWrapper& wrapper_1 = emitter_0.container();
    wrapper_1.append(qVariantFromValue(vector_1));

    dtkComposerTransmitterVariant emitter_1;
    emitter_1.setData(wrapper_1);

    dtkComposerTransmitterReceiverVector<dtkContainerVector<qreal> > receiver_0;
    receiver_0.connect(&emitter_1);

    dtkContainerVector< dtkContainerVector<qreal> > meta_vector_end = receiver_0.data();

    qDebug() << "Size of transmitted meta vector:";
    qDebug() << "- meta_vector_end:" << meta_vector_end.count();
    
    qDebug() << "";
    
    qDebug() << "Size of vectors contained by meta_vector_end:";
    qDebug() << "- vector_0:" << meta_vector_end.at(0).count(); 
    qDebug() << "- vector_1:" << meta_vector_end.at(1).count(); 
    
    qDebug() << "";
}

// /////////////////////////////////////////////////////////////////
// main
// /////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    dtkAboutBox *about = new dtkAboutBox();
    about->setText("dtkAbstractDataComposite Example");
    about->setInformativeText(
        "This example shows how to manipulate a vector of vector of real "
        "numbers.");
    about->setDefaultButton(QMessageBox::Ok);
    about->open();

    int status = application.exec();

    run();

    return status;
}

// #include "main.moc"
