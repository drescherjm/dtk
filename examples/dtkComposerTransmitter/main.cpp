/* main.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Nov  2 10:48:42 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr  4 14:19:13 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 141
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore/QObject>

#include <dtkComposer/dtkComposerTransmitter.h>
#include <dtkComposer/dtkComposerTransmitterEmitter.h>

#include <dtkCore/dtkAbstractData>
#include <dtkCore/dtkAbstractProcess>
#include <dtkCore/dtkGlobal>

#include <dtkLog/dtkLog.h>

#include <dtkMath/dtkMatrixSquared>

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
    int id(void) const {return m_id;}

    void setId(int id) {m_id = id;};

private:
    int m_id;
};
Q_DECLARE_METATYPE(dummyData);
Q_DECLARE_METATYPE(dummyData *);

// /////////////////////////////////////////////////////////////////
// other data
// /////////////////////////////////////////////////////////////////

class otherData
{
public:
     otherData(void) {;}
    ~otherData(void) {;}
        
public:
    double value(void) const {return m_value;}
    void setValue(double value) {m_value = value;};

private:
    double m_value;
};
Q_DECLARE_METATYPE(otherData);
Q_DECLARE_METATYPE(otherData *);

// /////////////////////////////////////////////////////////////////
// dummyGenerator
// /////////////////////////////////////////////////////////////////

class dummyGenerator : public dtkAbstractProcess
{
    Q_OBJECT

public:
     dummyGenerator(void) : dtkAbstractProcess() {;}
    ~dummyGenerator(void) {;}
        
public:
    dummyData *dummy(void) {return m_dummyData;}
    otherData *other(void) {return m_otherData;}

    double value(void) {return m_value;}

    dtkMatrixSquared<int>& matrix(void) {return m_matrix;}

public slots:   
    int update(void);

private:
    double m_value;
    dummyData *m_dummyData;
    otherData *m_otherData;
    dtkMatrixSquared<int> m_matrix;
};

int dummyGenerator::update(void)
{
    m_value = 11.58;

    m_dummyData = new dummyData();
    m_dummyData->setId(101);

    m_otherData = new otherData();
    m_otherData->setValue(1./3.);
    
    m_matrix = dtkMatrixSquared<int>(2);
    m_matrix[0][0] = 1;
    m_matrix[0][1] = 5;
    m_matrix[1][0] = 7;
    m_matrix[1][1] = 2;    

    return DTK_SUCCEED;
}

// /////////////////////////////////////////////////////////////////
// dummyModifier
// /////////////////////////////////////////////////////////////////

class dummyModifier : public dtkAbstractProcess
{
    Q_OBJECT

public:
    dummyModifier(void) : dtkAbstractProcess() {m_dummyData = NULL; m_otherData = NULL; m_matrix = NULL;}
    ~dummyModifier(void) {;}

public:
    void modify(bool val, bool dum, bool oth, bool mat) {m_val = val; m_dum = dum; m_oth = oth; m_mat = mat;}

public:
    void setDummyData(dummyData *dummy) {m_dummyData = dummy;}
    void setOtherData(otherData *other) {m_otherData = other;}

    void setValue(double value) {m_value = value;}
        
    void setMatrix(dtkMatrixSquared<int> *mat) {m_matrix = mat;}

public:
    dummyData *dummy(void) {return m_dummyData;}
    otherData *other(void) {return m_otherData;}

    double value(void) {return m_value;}

    dtkMatrixSquared<int> *matrix(void) {return m_matrix;}

public slots:   
    int update(void);

private:
    double m_value;
    dummyData *m_dummyData;
    otherData *m_otherData;
    dtkMatrixSquared<int> *m_matrix;

    bool m_val, m_dum, m_oth, m_mat;
};

int dummyModifier::update(void)
{
    if (m_val)
        m_value += 22;

    if (m_dum)
        m_dummyData->setId(102);

    if (m_oth)
        m_otherData->setValue(1./4.);
    
    if (m_mat) {
        (*m_matrix)[0][0] = 1;
        (*m_matrix)[0][1] = 0;
        (*m_matrix)[1][0] = 0;
        (*m_matrix)[1][1] = 1; 
    }

    return DTK_SUCCEED;
}

// /////////////////////////////////////////////////////////////////

typedef dtkComposerTransmitterEmitter<dummyData *> dummyDataTransmitter;
typedef dtkComposerTransmitterEmitter<otherData *> otherDataTransmitter;
typedef dtkComposerTransmitterEmitter<double> doubleTransmitter;
typedef dtkComposerTransmitterEmitter<dtkMatrixSquared<int> *> matrixTransmitter;

Q_DECLARE_METATYPE(dtkMatrixSquared<int> *);

void run(void)
{
    // generation of dummy datas
    
    dummyGenerator *gen = new dummyGenerator();
    gen->update();
    qDebug() << gen->value() << gen->dummy()->id() << gen->other()->value() << gen->matrix();
    
    // tranmitter
    
    qRegisterMetaType<dummyData *>();
    dummyDataTransmitter ddt;
    ddt.setData(gen->dummy());

    qRegisterMetaType<otherData *>();
    otherDataTransmitter odt;
    odt.setData(gen->other());

    doubleTransmitter dbt;
    dbt.setData(gen->value());
    
    qRegisterMetaType<dtkMatrixSquared<int> *>();
    matrixTransmitter mxt;
    mxt.setData(&(gen->matrix()));

    // modifier
    
    dummyModifier *mod = new dummyModifier();

    // mod->setValue(gen->value());
    // mod->setDummyData(gen->dummy());
    // mod->setOtherData(gen->other());
    // mod->setMatrix(&(gen->matrix()));

    mod->setValue(dbt.data());
    mod->setDummyData(ddt.data());
    mod->setOtherData(odt.data());
    mod->setMatrix(mxt.data());

    mod->modify(true, true, true, true);
    mod->modify(false, false, false, false);

    mod->update();
    qDebug() << mod->value() << mod->dummy()->id() << mod->other()->value() << *mod->matrix();
    
}

// /////////////////////////////////////////////////////////////////
// main
// /////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    // QApplication application(argc, argv);

    // int status = application.exec();

    int status = 1;

    run();

    return status;
}

#include "main.moc"
