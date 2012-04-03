/* main.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Sep 26 09:28:44 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr  3 16:04:07 2012 (+0200)
 *           By: tkloczko
 *     Update #: 151
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore/QObject>

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataComposite.h>
#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>

#include <dtkGui/dtkAboutBox.h>

// /////////////////////////////////////////////////////////////////
// Dummy concrete dtkAbstractData
// /////////////////////////////////////////////////////////////////

class xyzData : public dtkAbstractData
{
    Q_OBJECT

public:
     xyzData(void) : dtkAbstractData() {;}
    ~xyzData(void) {;}
        
public:
    void setData(void *data) {DTK_UNUSED(data);}
};

// /////////////////////////////////////////////////////////////////

void run(void)
{
    // /////////////////////////////////////////////////////////////////
    // Handling a composite created from a vector of xyzData
    // /////////////////////////////////////////////////////////////////

    // Creation of a vector of xyzData*

    QVector<xyzData *> xyz_vector;
    xyzData *xyz_data = NULL;
    for(int i = 0; i < 10; i++) {
        xyz_data = new xyzData();
        xyz_data->setObjectName(QString("xyz data #%1").arg(i));
        xyz_vector << xyz_data;
    }

    // Construction of the composite and checking contained items

    dtkAbstractDataComposite *composite = new dtkAbstractDataComposite(dtkUpCastIntoDataVector(xyz_vector));
    foreach(dtkAbstractData *data, composite->vector()) {
        qDebug() << data->name();
    }
    qDebug() << " ";

    // As reference of initial vector is used, modifying composite
    // modify the initial vector.

    for(int i = 10; i < 20; i++) {
        xyz_data = new xyzData();
        xyz_data->setObjectName(QString("xyz data #%1").arg(i));
        composite->append(xyz_data);
    }

    foreach(xyzData *xyz, xyz_vector) {
        qDebug() << xyz->name();
    }
    qDebug() << " ";

    // Conversely, modifying initial vector leads to a modified
    // composite.

    xyz_vector.remove(10, 10);

    foreach(dtkAbstractData *data, composite->vector()) {
        qDebug() << data->name();
    }
    qDebug() << " ";

    // Creation of a copy of initial vector through the composite

    QVector<xyzData *> xyz_vector_bis = dtkDownCastFromDataVector<xyzData *>(composite->vector());
    foreach(xyzData *xyz, xyz_vector_bis) {
        qDebug() << xyz->name();
    }
    qDebug() << " ";

    // Deleting composite does not affect initial vector.
    // WARNING: deleting initial vector makes the composite derefenced.

    delete composite;
    composite = NULL;

    foreach(xyzData *xyz, xyz_vector) {
        qDebug() << xyz->name();
    }
    qDebug() << " ";

    // /////////////////////////////////////////////////////////////////
    // Handling a composite created from a copy of vector of xyzData
    // /////////////////////////////////////////////////////////////////

    // Creation of composite from function dtkAbstractDataCompositeFromVectorCopy

    composite = dtkAbstractDataCompositeFromVectorCopy(xyz_vector);
    foreach(dtkAbstractData *data, composite->vector()) {
        qDebug() << data->name();
    }
    qDebug() << " ";

    // Modifying composite does not affect initial vector since it
    // works on a copy.

    for(int i = 10; i < 20; i++) {
        xyz_data = new xyzData();
        xyz_data->setObjectName(QString("composite data #%1").arg(i-10));
        composite->append(xyz_data);
    }
    foreach(dtkAbstractData *data, composite->vector()) {
        qDebug() << data->name();
    }
    qDebug() << " ";

    foreach(xyzData *xyz, xyz_vector) {
        qDebug() << xyz->name();
    }
    qDebug() << " ";

    // Deleting composite is harmless.

    delete composite;
    composite = NULL;

    foreach(xyzData *xyz, xyz_vector) {
        qDebug() << xyz->name();
    }
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
        "This example aims at showing how creating and handling composite "
        "of dtkAbstractData or derivative classes. A dtkAbstractDataComposite "
        "enables to carry vector or list of datas as a dtkAbstractData. ");
    about->setDefaultButton(QMessageBox::Ok);
    about->open();

    int status = application.exec();

    run();

    return status;
}

#include "main.moc"
