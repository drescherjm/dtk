/* main.cpp --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: 2012 Fri Oct 26 11:17:26 (+0200)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore/QObject>

#include <dtkCore/dtkAbstractObject>
#include <dtkCore/dtkAbstractData>
#include <dtkCore/dtkGlobal>
#include <dtkCore/dtkVariant.h>

#include <dtkLog/dtkLog.h>

#include <dtkMath/dtkMatrixSquared>

#include <dtkContainer/dtkContainerVectorWrapper.h>
#include <dtkContainer/dtkContainerVector.h>

// /////////////////////////////////////////////////////////////////
// Dummy concrete dtkAbstractData
// /////////////////////////////////////////////////////////////////

class dummyData : public dtkAbstractData
{
    Q_OBJECT

public:
     dummyData(void) : dtkAbstractData() {;}
     dummyData(const dummyData& other) : dtkAbstractData(other) {;}
    ~dummyData(void) {;}

public:
    bool operator == (const dummyData& other) const { return false;}
        
public:
    QString identifier(void) const {return QString("dummyData");}
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

void run(void)
{
    dtkVariant var;

    // dtkAbstractObject into dtkVariant

    dtkAbstractObject *object = new dtkAbstractObject;
    object->setObjectName("dtkAbstractObject"); 

    var.setValue(object);

    qDebug() << "---------------";
    qDebug() << "CASE 0: dtkAbstractObject into dtkVariant";
    qDebug() << var;
    qDebug() << "Object name: " << var.value<dtkAbstractObject*>()->objectName();
    qDebug() << "";

    // dtkMatrixSquare<double> into dtkVariant

    dtkMatrixSquared<double> *mat = new dtkMatrixSquared<double>(2);
    (*mat)[0][0] = 1.;
    (*mat)[0][1] = 0.;
    (*mat)[1][0] = 0.;
    (*mat)[1][1] = 1.;

    var.setValue(mat);

    qDebug() << "---------------";
    qDebug() << "CASE 1: dtkMatrixSquare<double> into dtkVariant";
    qDebug() << var;
    qDebug() << "Matrix: " << var.value<dtkMatrixSquared<double>*>()->description();
    qDebug() << "";

    // dtkContainerVector<double> into dtkVariant

    dtkContainerVector<double> *vec = new dtkContainerVector<double>(5, 3.14159);
    dtkAbstractContainerWrapper *wv = new dtkContainerVectorWrapper<double>(vec);
    var.setValue(wv);

    qDebug() << "---------------";
    qDebug() << "CASE 3: dtkAbstractContainer into dtkVariant";
    qDebug() << var;
    qDebug() << "Container first value: " << var.value<dtkAbstractContainerWrapper*>()->at(0).value<double>();
    qDebug() << "";


    // dummyData into dtkVariant

    dummyData *data = new dummyData();

    var.setValue(data);

    qDebug() << "---------------";
    qDebug() << "CASE 4: dummyData WHICH IS NOT REGISTERED TO QMETATYPE SYSTEM into dtkVariant";
    qDebug() << var;
    qDebug() << "Extraction as dtkAbstractObject: " << var.value<dtkAbstractObject*>()->identifier();
    qDebug() << "Extraction as dtkAbstractData:   " << var.value<dtkAbstractData*>()->identifier();
    qDebug() << "Extraction as dummyData:         " << var.value<dummyData*>()->identifier();
    qDebug() << "";
}

// /////////////////////////////////////////////////////////////////
// main
// /////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    int status = 1;

    run();

    return status;
}

#include "main.moc"
