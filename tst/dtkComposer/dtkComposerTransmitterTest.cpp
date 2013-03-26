/* dtkComposerTransmitterTest.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Mon Mar 25 11:36:34 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Mar 26 15:53:08 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 547
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
    virtual ~Data(void) {;}

public:
    Data& operator = (const Data& o) { m_id = o.m_id; m_name = o.m_name; return (*this); }

public:
    bool operator == (const Data& o) const { if (m_id != o.m_id || m_name != o.m_name) return false; return true; }

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

class DeriveData : public Data {};

Q_DECLARE_METATYPE(DeriveData);
Q_DECLARE_METATYPE(DeriveData *);

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
    virtual ~ObjectData(void) {;}

public:
    ObjectData& operator = (const ObjectData& o) { m_id = o.m_id; m_name = o.m_name; return (*this); }

public:
    bool operator == (const ObjectData& o) const { if (m_id != o.m_id || m_name != o.m_name) return false; return true; }

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

class DeriveObjectData : public ObjectData {
    Q_OBJECT
};

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
    CoreData& operator = (const CoreData& o) { m_id = o.m_id; m_name = o.m_name; return (*this); }

public:
    bool operator == (const CoreData& o) const { if (m_id != o.m_id || m_name != o.m_name) return false; return true; }

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

class DeriveCoreData : public CoreData 
{
    Q_OBJECT

public:
    DeriveCoreData(void) : CoreData() {}
    DeriveCoreData(const DeriveCoreData& o) : CoreData(o) {}

public:
    DeriveCoreData *clone(void) const { return new DeriveCoreData(*this); }
};

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

void dtkComposerTransmitterTestCase::initTestCase(void)
{
    

}

void dtkComposerTransmitterTestCase::init(void)
{

}

void dtkComposerTransmitterTestCase::testTransmitterAtomicType(void)
{
    // Template transmitters
    dtkComposerTransmitterEmitter<int>     e_int;
    dtkComposerTransmitterEmitter<QString> e_str;
    
    dtkComposerTransmitterReceiver<int>     r_int;
    dtkComposerTransmitterReceiver<QString> r_str;

    // -- Basic checks
    QCOMPARE(QString("Emitter"), e_int.kindName());
    QCOMPARE(QString("Receiver"), r_int.kindName());

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
    QCOMPARE(i, e_int.variant().value<int>());
    QCOMPARE(str, e_str.variant().value<QString>());
    QCOMPARE(i, r_int.data());
    QCOMPARE(str, r_str.data());

    QVERIFY(r_int.disconnect(&e_int));
    QVERIFY(r_str.disconnect(&e_str));    

    // Variant transmitters
    dtkComposerTransmitterEmitterVariant  e_var;
    dtkComposerTransmitterReceiverVariant r_var;

    // -- Basics
    QCOMPARE(QString("Emitter"), e_var.kindName());
    QCOMPARE(QString("Receiver"), r_var.kindName());
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
    r_var.setTypeList(dtkComposerTransmitter::TypeList() 
		      << QMetaType::LongLong 
		      << QMetaType::Double);
    QVERIFY(r_var.connect(&e_str));
    QVERIFY(r_var.connect(&e_int));
    QVERIFY(r_var.connect(&e_var));
    QVERIFY(r_var.disconnect(&e_str));
    QVERIFY(r_var.disconnect(&e_int));
    QVERIFY(r_var.disconnect(&e_var));

    // -- Emission/Reception
    double pi = 4. * qAtan(1.);
    e_var.setData(pi);
    r_var.connect(&e_var);
    QCOMPARE(pi, r_var.data<double>());
    QCOMPARE(static_cast<qlonglong>(qFloor(pi)), r_var.data<qlonglong>());
    r_var.disconnect(&e_var);

    r_var.connect(&e_int);
    QCOMPARE(static_cast<qlonglong>(i), r_var.data<qlonglong>());
    r_var.disconnect(&e_int);

    r_var.connect(&e_str);
    QCOMPARE(static_cast<qlonglong>(0), r_var.data<qlonglong>());
    r_var.disconnect(&e_str);

    r_var.setTypeList(dtkComposerTransmitter::TypeList() 
		      << QMetaType::QString);
    r_var.connect(&e_str);
    QCOMPARE(str, r_var.data<QString>());
    r_var.disconnect(&e_str);    
}

void dtkComposerTransmitterTestCase::testTransmitterComplexType(void)
{
    int count = 0;

    // Non QObject nor CoreObject Data
    {
	dtkComposerTransmitterEmitter<Data>  e_data;
	dtkComposerTransmitterReceiver<Data> r_data;
	QVERIFY(r_data.connect(&e_data));

	Data data_e;
	data_e.setName("Data");
	data_e.setId(count++);
	
	e_data.setData(data_e);
	
	QCOMPARE(data_e, r_data.data());
	QVERIFY(r_data.disconnect(&e_data));

	dtkComposerTransmitterReceiverVariant r_var;
	QVERIFY(r_var.connect(&e_data));

	QCOMPARE(data_e, r_var.data<Data>());
	QVERIFY(r_var.disconnect(&e_data));	
    }

    // Data pointer
    {
	dtkComposerTransmitterEmitter<Data *>  e_data;
	dtkComposerTransmitterReceiver<Data *> r_data;
	QVERIFY(r_data.connect(&e_data));

	Data *data_e = new Data(count++, "PData");
    
	e_data.setData(data_e);
	QCOMPARE(*data_e, *(r_data.constData()));
	QCOMPARE(*data_e, *(r_data.data()));
	QVERIFY(r_data.disconnect(&e_data));

	dtkComposerTransmitterReceiverVariant r_var;
	QVERIFY(r_var.connect(&e_data));

	QCOMPARE(*data_e, *(r_var.constData<Data*>()));
	QCOMPARE(*data_e, *(r_var.data<Data*>()));
	QVERIFY(r_var.disconnect(&e_data));
    
	// -- Derived Data pointer
	dtkComposerTransmitterEmitter<DeriveData *> e_ddata;
	QVERIFY(!r_data.connect(&e_ddata)); // Connection refused !!
	
	delete data_e;
    }

    // QObject data pointer
    {
	dtkComposerTransmitterEmitter<ObjectData *>  e_data;
	dtkComposerTransmitterReceiver<ObjectData *> r_data;
	QVERIFY(r_data.connect(&e_data));
	
	ObjectData *data_e = new ObjectData(count++, "OPData");
    
	e_data.setData(data_e);
	QCOMPARE(*data_e, *(r_data.constData()));
	QCOMPARE(*data_e, *(r_data.data()));
	QVERIFY(r_data.disconnect(&e_data));

	dtkComposerTransmitterReceiverVariant r_var;
	QVERIFY(r_var.connect(&e_data));

	QCOMPARE(*data_e, *(r_var.constData<ObjectData*>()));
	QCOMPARE(*data_e, *(r_var.data<ObjectData*>()));
	QVERIFY(r_var.disconnect(&e_data));
	
	delete data_e;

	// -- Derived QObject Data pointer
	dtkComposerTransmitterEmitter<DeriveObjectData *> e_ddata;
	QVERIFY(r_data.connect(&e_ddata)); // Connection enabled !!

	DeriveObjectData *data_ed = new DeriveObjectData;
	data_ed->setName("Derived Object Data");
	data_ed->setId(count++);

	e_ddata.setData(data_ed);
	QCOMPARE(*qobject_cast<ObjectData *>(data_ed), *(r_data.constData()));
	QCOMPARE(*qobject_cast<ObjectData *>(data_ed), *(r_data.data()));
	QVERIFY(r_data.disconnect(&e_ddata));

	QVERIFY(r_var.connect(&e_ddata));

	QCOMPARE(*data_ed, *(r_var.constData<DeriveObjectData*>()));
	QCOMPARE(*data_ed, *(r_var.data<DeriveObjectData*>()));
	QVERIFY(r_var.disconnect(&e_ddata));
	
	delete data_ed;
    }

    // dtkCoreObject data pointer
    {
	dtkComposerTransmitterEmitter<CoreData *>  e_data;
	dtkComposerTransmitterReceiver<CoreData *> r_data;
	QVERIFY(r_data.connect(&e_data));
	
	CoreData *data_e = new CoreData(count++, "OPData");
    
	e_data.setData(data_e);
	QCOMPARE(*data_e, *(r_data.constData()));
	QCOMPARE(*data_e, *(r_data.data()));
	QVERIFY(r_data.disconnect(&e_data));

	dtkComposerTransmitterReceiverVariant r_var;
	QVERIFY(r_var.connect(&e_data));

	QCOMPARE(*data_e, *(r_var.constData<CoreData*>()));
	QCOMPARE(*data_e, *(r_var.data<CoreData*>()));
	QVERIFY(r_var.disconnect(&e_data));

	
	QVERIFY(r_data.connect(&e_data));
	QVERIFY(r_var.connect(&e_data));

	QCOMPARE(static_cast<void *>(data_e), static_cast<void *>(r_var.constData<CoreData*>()));
	QVERIFY(static_cast<void *>(data_e) != static_cast<void *>(r_var.data<CoreData*>()));
	
	delete data_e;

	// -- Derived Core Data pointer
	dtkComposerTransmitterEmitter<DeriveCoreData *> e_ddata;
	QVERIFY(r_data.connect(&e_ddata)); // Connection enabled !!

	DeriveCoreData *data_ed = new DeriveCoreData;
	data_ed->setName("Derived Core Data");
	data_ed->setId(count++);

	e_ddata.setData(data_ed);
	QCOMPARE(*qobject_cast<CoreData *>(data_ed), *(r_data.constData()));
	QCOMPARE(*qobject_cast<CoreData *>(data_ed), *(r_data.data()));
	QVERIFY(r_data.disconnect(&e_ddata));

	QVERIFY(r_var.connect(&e_ddata));

	QCOMPARE(*data_ed, *(r_var.constData<DeriveCoreData*>()));
	QCOMPARE(*data_ed, *(r_var.data<DeriveCoreData*>()));
	QVERIFY(r_var.disconnect(&e_ddata));
	
	delete data_ed;
    }
}

void dtkComposerTransmitterTestCase::cleanupTestCase(void)
{

}

void dtkComposerTransmitterTestCase::cleanup(void)
{

}

DTKTEST_MAIN(dtkComposerTransmitterTest, dtkComposerTransmitterTestCase)

#include "dtkComposerTransmitterTest.moc"
