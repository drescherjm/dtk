/* main.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Sun May  6 18:46:00 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Sun May  6 19:23:16 2012 (+0200)
 *           By: tkloczko
 *     Update #: 29
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore/QObject>

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractContainer.h>
#include <dtkCore/dtkContainerList.h>
#include <dtkCore/dtkContainerVector.h>
#include <dtkCore/dtkGlobal.h>

#include <dtkLog/dtkLog.h>

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
Q_DECLARE_METATYPE(xyzData);
Q_DECLARE_METATYPE(xyzData *);



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

    dtkContainerVector<xyzData *> vector;
    vector.setVector(xyz_vector);

    dtkAbstractContainer *container = &vector;

    qDebug() << "Vector container:";
    foreach(const xyzData *data, vector.vector()) {
        qDebug() << data->name();
    }
    qDebug() << " ";

    // 

    qDebug() << "Abstract container:" ;
    for(int i = 0; i < container->count(); ++i) {
        qDebug() << qvariant_cast<xyzData *>(container->at(i))->name();
    }
    qDebug() << " "; 

    // As reference of initial vector is used, modifying composite
    // modify the initial vector.

    for(int i = 10; i < 20; i++) {
        xyz_data = new xyzData();
        xyz_data->setObjectName(QString("xyz data #%1").arg(i));
        container->append(qVariantFromValue(xyz_data));
    }

    qDebug() << "Abstract container extended:" ;
    for(int i = 0; i < container->count(); ++i) {
        qDebug() << qvariant_cast<xyzData *>(container->at(i))->name();
    }
    qDebug() << " ";

    //

    dtkContainerList<xyzData *> list;
    for(int i = container->count()-1; i >= 0; --i) {
        list.append(container->at(i));
    }

    qDebug() << "List container:";
    foreach(const xyzData *data, list.list()) {
        qDebug() << data->name();
    }
    qDebug() << " ";
    
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
