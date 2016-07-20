// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:



#include "dtkComposerTransmitterTest.h"

#include <dtkCore>
#include <dtkComposer>

// ///////////////////////////////////////////////////////////////////
// No Copyable Data concrete class
// ///////////////////////////////////////////////////////////////////

#if !defined(Q_CC_MSVC) || _MSC_FULL_VER > 190023025
class NoCopyableData
{
public:
    NoCopyableData(void) {
        ;
    }
    NoCopyableData(const int& id, const QString& name) : m_id(id), m_name(name) {
        ;
    }
    virtual ~NoCopyableData(void) {
        ;
    }

public:
    bool operator == (const NoCopyableData& o) const {
        if (m_id != o.m_id || m_name != o.m_name) return false;

        return true;
    }

public:
    void   setId(const int& id)       {
        m_id   = id;
    }
    void setName(const QString& name) {
        m_name = name;
    }

public:
    int       id(void) const {
        return m_id;
    }
    QString name(void) const {
        return m_name;
    }

private:
    int m_id;
    QString m_name;

    NoCopyableData(const NoCopyableData&) {}
    NoCopyableData& operator=(const NoCopyableData&) {
        return *this;
    }
};

Q_DECLARE_METATYPE(NoCopyableData *);

QDebug operator << (QDebug dbg, NoCopyableData *data)
{
    dbg.nospace() << "NoCopyableData(" << data->id() << ", " << data->name() << ")"; return dbg.space();
}

class DeriveNoCopyableData : public NoCopyableData
{
public:
    DeriveNoCopyableData(void) : NoCopyableData(), m_value(0) {
        ;
    }
    DeriveNoCopyableData(const int& id, const QString& name, double value = 0) : NoCopyableData(id, name), m_value(value) {
        ;
    }

private:
    DeriveNoCopyableData(const DeriveNoCopyableData& o) {};
    DeriveNoCopyableData& operator=(const DeriveNoCopyableData&) {
        return *this;
    }

public:
    bool operator == (const DeriveNoCopyableData& o) const {
        if (m_value != o.m_value) return false;

        return (static_cast<const NoCopyableData&>(*this) == static_cast<const NoCopyableData&>(o));
    }

public:
    void setValue(double value) {
        m_value = value;
    }

public:
    double value(void) const {
        return m_value;
    }

private:
    double m_value;
};

Q_DECLARE_METATYPE(DeriveNoCopyableData *);
#endif

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

class Data
{
public:
    Data(void) {
        ;
    }
    Data(const int& id, const QString& name) : m_id(id), m_name(name) {
        ;
    }
    Data(const Data& o) : m_id(o.m_id), m_name(o.m_name) {
        ;
    }
    virtual ~Data(void) {
        ;
    }

public:
    Data& operator = (const Data& o) {
        m_id = o.m_id;
        m_name = o.m_name;
        return (*this);
    }

public:
    bool operator == (const Data& o) const {
        if (m_id != o.m_id || m_name != o.m_name) return false;

        return true;
    }

public:
    void   setId(const int& id)       {
        m_id   = id;
    }
    void setName(const QString& name) {
        m_name = name;
    }

public:
    int       id(void) {
        return m_id;
    }
    QString name(void) {
        return m_name;
    }

private:
    int m_id;
    QString m_name;

private:
    friend QDebug operator << (QDebug dbg, const Data& data);
    friend QDebug operator << (QDebug dbg,       Data *data);
};

Q_DECLARE_METATYPE(Data);
Q_DECLARE_METATYPE(Data *);

QDebug operator << (QDebug dbg, const Data& data)
{
    dbg.nospace() << "Data(" << data.m_id << ", " << data.m_name << ")";

    return dbg.space();
}

QDebug operator << (QDebug dbg, Data *data)
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
    ObjectData(void) : QObject(), m_id(-1), m_name("noname") {
        ;
    }
    ObjectData(const int& id, const QString& name) : m_id(id), m_name(name) {
        ;
    }
    ObjectData(const ObjectData& o) : m_id(o.m_id), m_name(o.m_name) {
        ;
    }
    virtual ~ObjectData(void) {
        ;
    }

public:
    ObjectData& operator = (const ObjectData& o) {
        m_id = o.m_id;
        m_name = o.m_name;
        return (*this);
    }

public:
    bool operator == (const ObjectData& o) const {
        if (m_id != o.m_id || m_name != o.m_name) return false;

        return true;
    }

public:
    void   setId(const int& id)       {
        m_id   = id;
    }
    void setName(const QString& name) {
        m_name = name;
    }

public:
    int       id(void) {
        return m_id;
    }
    QString name(void) {
        return m_name;
    }

private:
    int m_id;
    QString m_name;

private:
    friend QDebug operator << (QDebug dbg, const ObjectData& data);
    friend QDebug operator << (QDebug dbg,       ObjectData *data);
};

Q_DECLARE_METATYPE(ObjectData);
Q_DECLARE_METATYPE(ObjectData *);

QDebug operator << (QDebug dbg, const ObjectData& data)
{
    dbg.nospace() << "ObjectData(" << data.m_id << ", " << data.m_name << ")";

    return dbg.space();
}

QDebug operator << (QDebug dbg, ObjectData *data)
{
    dbg.nospace() << "ObjectData(" << data->m_id << ", " << data->m_name << ")";

    return dbg.space();
}

class DeriveObjectData : public ObjectData
{
    Q_OBJECT

public:
    DeriveObjectData() : ObjectData() {
        ;
    }
};

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

class VirtualObject : public QObject
{
    Q_OBJECT

public:
    VirtualObject(void) {
        ;
    }
    virtual ~VirtualObject(void) {
        ;
    }

public:
    VirtualObject& operator = (const VirtualObject& o) {
        setId(o.id());
        setName(o.name());
        return (*this);
    }

public:
    bool operator == (const VirtualObject& o) const {
        if (id() != o.id() || name() != o.name()) return false;

        return true;
    }

public:
    virtual void   setId(const int& id) = 0;
    virtual void setName(const QString& name) = 0;

public:
    virtual int       id(void) const = 0;
    virtual QString name(void) const = 0;

private:
    friend QDebug operator << (QDebug dbg, const VirtualObject& o);
    friend QDebug operator << (QDebug dbg,       VirtualObject *o);
};

QDebug operator << (QDebug dbg, const VirtualObject& o)
{
    dbg.nospace() << "VirtualObject(" << o.id() << ", " << o.name() << ")";

    return dbg.space();
}

QDebug operator << (QDebug dbg, VirtualObject *o)
{
    dbg.nospace() << "VirtualObject(" << o->id() << ", " << o->name() << ")";

    return dbg.space();
}

Q_DECLARE_METATYPE(VirtualObject *);

// ///////////////////////////////////////////////////////////////////

class DeriveVirtualObject : public VirtualObject
{
    Q_OBJECT

public:
    DeriveVirtualObject(void) : VirtualObject(), m_id(-1), m_name(QString()) {
        ;
    }
    DeriveVirtualObject(const DeriveVirtualObject& other) : VirtualObject(), m_id(other.m_id), m_name(other.m_name) {
        ;
    }
    ~DeriveVirtualObject(void) {
        ;
    }

public:
    void setId(const int& id) {
        m_id = id;
    }
    void setName(const QString& name) {
        m_name = name;
    }

public:
    int       id(void) const {
        return m_id;
    }
    QString name(void) const {
        return m_name;
    }

private:
    int m_id;
    QString m_name;
};

Q_DECLARE_METATYPE(DeriveVirtualObject);
Q_DECLARE_METATYPE(DeriveVirtualObject *);

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

void dtkComposerTransmitterTestCase::initTestCase(void)
{


}

void dtkComposerTransmitterTestCase::init(void)
{

}

void dtkComposerTransmitterTestCase::testAtomicType(void)
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

void dtkComposerTransmitterTestCase::testComplexType(void)
{
    int count = 0;

    // No copyable Data pointer
#if !defined(Q_CC_MSVC) || _MSC_FULL_VER > 190023025
    {
        dtkComposerTransmitterEmitter<NoCopyableData *>  e_data;
        dtkComposerTransmitterReceiver<NoCopyableData *> r_data;
        QVERIFY(r_data.connect(&e_data));

        NoCopyableData *data_e = new NoCopyableData(count++, "PNoCopyableData");

        e_data.setData(data_e);
        QCOMPARE(*data_e, *(r_data.constData()));
        QCOMPARE(*data_e, *(r_data.data()));
        QVERIFY(r_data.disconnect(&e_data));

        dtkComposerTransmitterReceiverVariant r_var;
        QVERIFY(r_var.connect(&e_data));

        QCOMPARE(*data_e, *(r_var.constData<NoCopyableData *>()));
        QCOMPARE(*data_e, *(r_var.data<NoCopyableData *>()));
        QVERIFY(r_var.disconnect(&e_data));

        // -- Derived NoCopyableData pointer
        dtkComposerTransmitterEmitter<DeriveNoCopyableData *> e_ddata;
        QVERIFY(!r_data.connect(&e_ddata)); // Connection refused !!

        delete data_e;
    }
#endif

    // Non QObject Data
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

        QCOMPARE(*data_e, *(r_var.constData<Data *>()));
        QCOMPARE(*data_e, *(r_var.data<Data *>()));
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

        QCOMPARE(*data_e, *(r_var.constData<ObjectData *>()));
        QCOMPARE(*data_e, *(r_var.data<ObjectData *>()));
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

        QCOMPARE(*data_ed, *(r_var.constData<DeriveObjectData *>()));
        QCOMPARE(*data_ed, *(r_var.data<DeriveObjectData *>()));
        QVERIFY(r_var.disconnect(&e_ddata));

        delete data_ed;
    }

    // VirtualObject data pointer
    {
        dtkComposerTransmitterEmitter<VirtualObject *>  e_data;
        dtkComposerTransmitterReceiver<VirtualObject *> r_data;
        QVERIFY(r_data.connect(&e_data));
        QVERIFY(r_data.disconnect(&e_data));

        dtkComposerTransmitterReceiverVariant r_var;
        QVERIFY(r_var.connect(&e_data));
        QVERIFY(r_var.disconnect(&e_data));

        // -- Derived Virtual Object pointer
        dtkComposerTransmitterEmitter<DeriveVirtualObject *> e_ddata;
        QVERIFY(r_data.connect(&e_ddata)); // Connection enabled : Derive into Base

        dtkComposerTransmitterReceiver<DeriveVirtualObject *> r_ddata;
        QVERIFY(!r_ddata.connect(&e_data)); // Connection disabled : Base into Derive


        DeriveVirtualObject *data_ed = new DeriveVirtualObject;
        data_ed->setName("Derived Virtual Object");
        data_ed->setId(count++);

        e_ddata.setData(data_ed);
        QCOMPARE(*qobject_cast<VirtualObject *>(data_ed), *(r_data.constData()));
        QCOMPARE(*qobject_cast<VirtualObject *>(data_ed), *(r_data.data()));
        QVERIFY(r_data.disconnect(&e_ddata));

        QVERIFY(r_var.connect(&e_ddata));

        QCOMPARE(*data_ed, *(r_var.constData<DeriveVirtualObject *>()));
        QCOMPARE(*data_ed, *(r_var.data<DeriveVirtualObject *>()));

        dtkComposerTransmitterReceiver<VirtualObject *> r_copy;
        QVERIFY(r_copy.connect(&e_ddata));

        QCOMPARE(*qobject_cast<VirtualObject *>(data_ed), *(r_copy.constData()));

        // As e_ddata is connected to two receivers, a copy is
        // performed when data() method is called. However, as
        // DeriveVirtualObject class has never been registered to
        // qMetaType at runtime, the transmitter fails to return a
        // copy. Null pointer is returned.
        QVERIFY(!r_copy.data());

        // As soon as the DeriveVirtualObject class is registered, the
        // copy can be done at the lowest level of the class
        // hierarchy.
        qMetaTypeId<DeriveVirtualObject>();
        QCOMPARE(*qobject_cast<VirtualObject *>(data_ed), *(r_copy.data()));

        QVERIFY(r_var.disconnect(&e_ddata));
        QVERIFY(r_copy.disconnect(&e_ddata));

        delete data_ed;
    }
}

void dtkComposerTransmitterTestCase::testLinks(void)
{
    dtkComposerTransmitterEmitter<ObjectData *>  e_0;
    dtkComposerTransmitterProxy p0;
    dtkComposerTransmitterReceiver<ObjectData *> r_0;
    dtkComposerTransmitterReceiver<ObjectData *> r_1;

    dtkComposerTransmitterLinkList   valid_list;
    dtkComposerTransmitterLinkList invalid_list;

    dtkComposerTransmitter::onTransmittersConnected(&e_0, &p0, valid_list, invalid_list);
    QVERIFY(valid_list.isEmpty() && invalid_list.isEmpty()); valid_list.clear();
    dtkComposerTransmitter::onTransmittersConnected(&p0, &r_0, valid_list, invalid_list);
    QVERIFY(!valid_list.isEmpty() && invalid_list.isEmpty()); valid_list.clear();
    dtkComposerTransmitter::onTransmittersConnected(&p0, &r_1, valid_list, invalid_list);
    QVERIFY(!valid_list.isEmpty() && invalid_list.isEmpty()); valid_list.clear();

    QVERIFY(!r_0.isEmpty());
    QVERIFY(!r_1.isEmpty());

    dtkComposerTransmitterProxy p1, p2;
    dtkComposerTransmitterReceiverVariant r_var1, r_var2;

    dtkComposerTransmitter::onTransmittersConnected(&p0, &p1, valid_list, invalid_list);
    QVERIFY(valid_list.isEmpty() && invalid_list.isEmpty()); valid_list.clear();
    dtkComposerTransmitter::onTransmittersConnected(&p1, &r_var1, valid_list, invalid_list);
    QVERIFY(!valid_list.isEmpty() && invalid_list.isEmpty()); valid_list.clear();
    dtkComposerTransmitter::onTransmittersConnected(&p2, &r_var2, valid_list, invalid_list);
    QVERIFY(valid_list.isEmpty() && invalid_list.isEmpty()); valid_list.clear();
    dtkComposerTransmitter::onTransmittersConnected(&p1, &p2, valid_list, invalid_list);
    QVERIFY(!valid_list.isEmpty() && invalid_list.isEmpty()); valid_list.clear();

    QVERIFY(!r_var1.isEmpty());
    QVERIFY(!r_var2.isEmpty());

    ObjectData *data = new ObjectData(0, "Hello");
    e_0.setData(data);

    QVERIFY(e_0.variant().value<ObjectData *>());
    QCOMPARE(*data, *r_0.data());
    QCOMPARE(*data, *r_1.data());
    QCOMPARE(*data, *r_var1.data<ObjectData *>());
    QCOMPARE(*data, *r_var2.data<ObjectData *>());

    dtkComposerTransmitterReceiver<VirtualObject *> r_obj;
    dtkComposerTransmitter::onTransmittersConnected(&p2, &r_obj, valid_list, invalid_list);
    QVERIFY(valid_list.isEmpty() && !invalid_list.isEmpty());
}

void dtkComposerTransmitterTestCase::testProxyLoop(void)
{
    dtkComposerTransmitterEmitter<qlonglong>  e_0;
    dtkComposerTransmitterProxyLoop           p_0;
    dtkComposerTransmitterReceiver<qlonglong> r_0;
    dtkComposerTransmitterProxyLoop           p_1;
    dtkComposerTransmitterEmitter<qlonglong>  e_1;
    dtkComposerTransmitterReceiver<qlonglong> r_1;

    QVERIFY(p_0.connect(&e_0));
    QVERIFY(r_0.connect(&p_0));
    QVERIFY(p_1.connect(&e_1));
    QVERIFY(r_1.connect(&p_1));

    p_0.setTwin(&p_1);

    qlonglong i = 0;
    e_0.setData(i);

    p_0.disableLoopMode();

    while (i < 10012) {
        qlonglong value = r_0.data();
        value += 1;
        e_1.setData(value);

        if (i == 0)
            p_0.enableLoopMode();

        p_0.setVariant(p_1.variant());
        ++i;
    }

    QCOMPARE(i, r_1.data());
}

void dtkComposerTransmitterTestCase::testProxyVariant(void)
{
    dtkComposerTransmitterEmitter<qlonglong>  e_0;
    dtkComposerTransmitterProxyVariant        p_0;
    dtkComposerTransmitterReceiver<qlonglong> r_0;
    dtkComposerTransmitterProxyVariant        p_1;
    dtkComposerTransmitterEmitter<qlonglong>  e_1;
    dtkComposerTransmitterReceiver<qlonglong> r_1;

    QVERIFY(p_0.connect(&e_0));
    QVERIFY(r_0.connect(&p_0));

    qlonglong i = 359;
    e_0.setData(i);

    // By default proxy variant enables receiver mode.
    p_0.enableReceiver();
    QCOMPARE(i, p_0.data<qlonglong>());

    // We simulate that the data comes from a remote node
    // The proxy switch to emitter mode and one should set the data.
    p_0.enableEmitter();
    p_0.setData(i);
    QCOMPARE(i, r_0.data());
}

void dtkComposerTransmitterTestCase::testSwapPointer(void)
{
    // VirtualObject data pointer
    {
        dtkComposerTransmitterEmitter<VirtualObject *>  e_data;
        dtkComposerTransmitterReceiver<VirtualObject *> r_0;
        dtkComposerTransmitterReceiver<VirtualObject *> r_1;
        QVERIFY(r_0.connect(&e_data));
        QVERIFY(r_1.connect(&e_data));

        DeriveVirtualObject *data_ed = new DeriveVirtualObject;
        data_ed->setName("Derived Virtual Object");
        data_ed->setId(1);

        // Register DeriveVirtualObject class to perform cloning operation.
        qMetaTypeId<DeriveVirtualObject>();
        e_data.setData(data_ed);

        VirtualObject *res_0 = r_0.data();
        VirtualObject *res_1 = r_1.constData();

        QVERIFY(res_0);
        QVERIFY(res_1);

        QCOMPARE(*res_0, *(static_cast<VirtualObject *>(data_ed)));
        QCOMPARE(*res_1, *(static_cast<VirtualObject *>(data_ed)));

        // Enforce swaping in receiver r_0;
        e_data.setData(res_0);
        VirtualObject *res_2 = r_0.data();
        QVERIFY(res_2);
        QVERIFY(res_2 != res_0);

        // Check that the second swaping returns the first pointer
        e_data.setData(res_2);
        VirtualObject *res_3 = r_0.data();
        QVERIFY(res_3);
        QVERIFY(res_3 == res_0);

        QVERIFY(r_0.disconnect(&e_data));
        QVERIFY(r_1.disconnect(&e_data));

        delete data_ed;
    }
}

void dtkComposerTransmitterTestCase::cleanupTestCase(void)
{

}

void dtkComposerTransmitterTestCase::cleanup(void)
{
}

DTKTEST_MAIN_NOGUI(dtkComposerTransmitterTest, dtkComposerTransmitterTestCase)

#include "dtkComposerTransmitterTest.moc"

//
// dtkComposerTransmitterTest.cpp ends here
