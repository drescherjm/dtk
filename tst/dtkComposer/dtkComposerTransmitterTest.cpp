/* dtkComposerTransmitterTest.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Mon Mar 25 11:36:34 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Mar 26 13:55:32 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 294
 */

/* Change Log:
 * 
 */

#include "dtkComposerTransmitterTest.h"

#include <dtkCore>
#include <dtkComposer>

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

class Data
{
public:
     Data(void) {;}
     Data(const int& id, const QString& name) : m_id(id), m_name(name) {;}
     Data(const Data& o) : m_id(o.m_id), m_name(o.m_name) {;}
    ~Data(void) {;}

public:
    Data& operator = (const Data& o) { m_id = o.m_id; m_name = o.m_name; }

public:
    void   setId(const int& id)       { m_id   = id; }
    void setName(const QString& name) { m_name = name; }

public:
    int       id(void) { return m_id; }
    QString name(void) { return m_name; }

private:
    int m_id;
    QString m_name;

private:
    friend QDebug operator<<(QDebug dbg, const Data &data);
    friend QDebug operator<<(QDebug dbg,       Data *data);
};

Q_DECLARE_METATYPE(Data);
Q_DECLARE_METATYPE(Data *);

QDebug operator<<(QDebug dbg, const Data &data)
{
    dbg.nospace() << "Data(" << data.m_id << ", " << data.m_name << ")";

    return dbg.space();
}

QDebug operator<<(QDebug dbg, Data *data)
{
    dbg.nospace() << "Data(" << data->m_id << ", " << data->m_name << ")";

    return dbg.space();
}

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

class ObjectData : public QObject
{
    Q_OBJECT

public:
     ObjectData(void) {;}
     ObjectData(const int& id, const QString& name) : m_id(id), m_name(name) {;}
     ObjectData(const ObjectData& o) : m_id(o.m_id), m_name(o.m_name) {;}
    ~ObjectData(void) {;}

public:
    ObjectData& operator = (const ObjectData& o) { m_id = o.m_id; m_name = o.m_name; }

public:
    void   setId(const int& id)       { m_id   = id; }
    void setName(const QString& name) { m_name = name; }

public:
    int       id(void) { return m_id; }
    QString name(void) { return m_name; }

private:
    int m_id;
    QString m_name;

private:
    friend QDebug operator<<(QDebug dbg, const ObjectData &data);
    friend QDebug operator<<(QDebug dbg,       ObjectData *data);
};

QDebug operator<<(QDebug dbg, const ObjectData &data)
{
    dbg.nospace() << "ObjectData(" << data.m_id << ", " << data.m_name << ")";

    return dbg.space();
}

QDebug operator<<(QDebug dbg, ObjectData *data)
{
    dbg.nospace() << "ObjectData(" << data->m_id << ", " << data->m_name << ")";

    return dbg.space();
}

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

class CoreData : public dtkCoreObject
{
    Q_OBJECT

public:
     CoreData(void) {;}
     CoreData(const int& id, const QString& name) : m_id(id), m_name(name) {;}
     CoreData(const CoreData& o) : m_id(o.m_id), m_name(o.m_name) {;}
    ~CoreData(void) {;}

public:
    CoreData& operator = (const CoreData& o) { m_id = o.m_id; m_name = o.m_name; }

public:
    CoreData *clone(void) const { return new CoreData(*this); }

public:
    void   setId(const int& id)       { m_id   = id; }
    void setName(const QString& name) { m_name = name; }

public:
    int       id(void) { return m_id; }
    QString name(void) { return m_name; }

private:
    int m_id;
    QString m_name;

private:
    friend QDebug operator<<(QDebug dbg, const CoreData &data);
    friend QDebug operator<<(QDebug dbg,       CoreData *data);
};

QDebug operator<<(QDebug dbg, const CoreData &data)
{
    dbg.nospace() << "CoreData(" << data.m_id << ", " << data.m_name << ")";

    return dbg.space();
}

QDebug operator<<(QDebug dbg, CoreData *data)
{
    dbg.nospace() << "CoreData(" << data->m_id << ", " << data->m_name << ")";

    return dbg.space();
}

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

void dtkComposerTransmitterTestCase::initTestCase(void)
{
    

}

void dtkComposerTransmitterTestCase::init(void)
{

}

void dtkComposerTransmitterTestCase::testTransmitter(void)
{
    // Template transmitters
    dtkComposerTransmitterEmitter<int>     e_int;
    dtkComposerTransmitterEmitter<QString> e_str;
    
    dtkComposerTransmitterReceiver<int>     r_int;
    dtkComposerTransmitterReceiver<QString> r_str;

    // -- Basic checks
    QVERIFY(QString("Emitter")  == e_int.kindName());
    QVERIFY(QString("Receiver") == r_int.kindName());

    // -- Check for connections

    QVERIFY(r_int.connect(&e_str));
    QVERIFY(r_str.connect(&e_int));
    QVERIFY(r_int.disconnect(&e_str));
    QVERIFY(r_str.disconnect(&e_int));
    QVERIFY(r_int.connect(&e_int));
    QVERIFY(r_str.connect(&e_str));
    QVERIFY(!r_str.connect(&r_int));

    // -- Check for emission/reception
    int i = 10;
    QString str = "Toto";
    e_int.setData(i);
    e_str.setData(str);
    QVERIFY(i == e_int.variant().value<int>());
    QVERIFY(str == e_str.variant().value<QString>());
    QVERIFY(i == r_int.data());
    QVERIFY(str == r_str.data());

    QVERIFY(r_int.disconnect(&e_int));
    QVERIFY(r_str.disconnect(&e_str));    

    // Variant transmitters
    dtkComposerTransmitterEmitterVariant  e_var;
    dtkComposerTransmitterReceiverVariant r_var;

    // -- Basics
    QVERIFY(QString("Emitter")  == e_var.kindName());
    QVERIFY(QString("Receiver") == r_var.kindName());
    QVERIFY(r_var.connect(&e_str));
    QVERIFY(r_var.connect(&e_int));
    QVERIFY(r_var.connect(&e_var));
    QVERIFY(r_int.connect(&e_var));
    QVERIFY(r_str.connect(&e_var));
    QVERIFY(!r_var.connect(&e_var));
    QVERIFY(r_var.disconnect(&e_str));
    QVERIFY(r_var.disconnect(&e_int));
    QVERIFY(r_var.disconnect(&e_var));
    QVERIFY(r_int.disconnect(&e_var));
    QVERIFY(r_str.disconnect(&e_var));

    // -- Check for multiple types
    r_var.setTypeList(dtkComposerTransmitter::TypeList() << QMetaType::LongLong << QMetaType::Double);
    QVERIFY(r_var.connect(&e_str));
    QVERIFY(r_var.connect(&e_int));
    QVERIFY(r_var.connect(&e_var));
    QVERIFY(r_var.disconnect(&e_str));
    QVERIFY(r_var.disconnect(&e_int));
    QVERIFY(r_var.disconnect(&e_var));

    // 
    double pi = 4. * atan(1.);
    e_var.setData(pi);
    r_var.connect(&e_var);
    QVERIFY(pi == r_var.data<double>()); qDebug() << pi;
    
}

void dtkComposerTransmitterTestCase::cleanupTestCase(void)
{

}

void dtkComposerTransmitterTestCase::cleanup(void)
{

}

DTKTEST_MAIN(dtkComposerTransmitterTest, dtkComposerTransmitterTestCase)

#include "dtkComposerTransmitterTest.moc"
