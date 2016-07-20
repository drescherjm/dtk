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

#include "dtkMetaTypeTest.h"

#include <dtkMeta/dtkMeta>

#include <QtCore>

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
// Data concrete class
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

Q_DECLARE_METATYPE(Data);
Q_DECLARE_METATYPE(Data *);

QDebug operator << (QDebug dbg, const Data& data)
{
    dbg.nospace() << "Data(" << data.id() << ", " << data.name() << ")"; return dbg.space();
}

QDebug operator << (QDebug dbg, Data *data)
{
    dbg.nospace() << "Data(" << data->id() << ", " << data->name() << ")"; return dbg.space();
}

class DeriveData : public Data
{
public:
    DeriveData(void) : Data(), m_value(0) {
        ;
    }
    DeriveData(const int& id, const QString& name, double value = 0) : Data(id, name), m_value(value) {
        ;
    }
    DeriveData(const DeriveData& o) : Data(o), m_value(o.m_value) {
        ;
    }

public:
    bool operator == (const DeriveData& o) const {
        if (m_value != o.m_value) return false;

        return (static_cast<const Data&>(*this) == static_cast<const Data&>(o));
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

Q_DECLARE_METATYPE(DeriveData);
Q_DECLARE_METATYPE(DeriveData *);

// ///////////////////////////////////////////////////////////////////
// Abstract class
// ///////////////////////////////////////////////////////////////////

class MyAbstract
{
public:
    MyAbstract(void) {
        ;
    }
    virtual ~MyAbstract(void) {
        ;
    }

public:
    MyAbstract& operator = (const MyAbstract& o) {
        setId(o.id());
        setName(o.name());
        return (*this);
    }

public:
    bool operator == (const MyAbstract& o) const {
        if (id() != o.id() || name() != o.name()) return false;

        return true;
    }

public:
    virtual void   setId(const int& id) = 0;
    virtual void setName(const QString& name) = 0;

public:
    virtual int       id(void) const = 0;
    virtual QString name(void) const = 0;
};

QDebug operator << (QDebug dbg, MyAbstract *o)
{
    dbg.nospace() << "MyAbstract(" << o->id() << ", " << o->name() << ")"; return dbg.space();
}

Q_DECLARE_METATYPE(MyAbstract *);

// ///////////////////////////////////////////////////////////////////

class DeriveMyAbstract : public MyAbstract
{
public:
    DeriveMyAbstract(void) : MyAbstract(), m_id(-1), m_name(QString()) {
        ;
    }
    DeriveMyAbstract(const DeriveMyAbstract& other) : MyAbstract(), m_id(other.m_id), m_name(other.m_name) {
        ;
    }
    ~DeriveMyAbstract(void) {
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

Q_DECLARE_METATYPE(DeriveMyAbstract);
Q_DECLARE_METATYPE(DeriveMyAbstract *);

// ///////////////////////////////////////////////////////////////////
// Abstract QObject class
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
};

QDebug operator << (QDebug dbg, VirtualObject *o)
{
    dbg.nospace() << "VirtualObject(" << o->id() << ", " << o->name() << ")"; return dbg.space();
}

Q_DECLARE_METATYPE(VirtualObject *);

// ///////////////////////////////////////////////////////////////////

class VirtualObject2 : public VirtualObject
{
    Q_OBJECT

public:
    VirtualObject2(void) {
        ;
    }
    virtual ~VirtualObject2(void) {
        ;
    }

public:
    virtual QString identifier(void) {
        return "VirtualObject2";
    }
};

Q_DECLARE_METATYPE(VirtualObject2 *);

// ///////////////////////////////////////////////////////////////////

class DeriveVirtualObject : public VirtualObject2
{
    Q_OBJECT

public:
    DeriveVirtualObject(void) : VirtualObject2(), m_id(-1), m_name(QString()) {
        ;
    }
    DeriveVirtualObject(const DeriveVirtualObject& other) : VirtualObject2(), m_id(other.m_id), m_name(other.m_name) {
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

VirtualObject *toto(VirtualObject2 *from)
{
    qDebug() << Q_FUNC_INFO;
    return from;
}

// ///////////////////////////////////////////////////////////////////
// dtkMetaTypeTestCasePrivate
// ///////////////////////////////////////////////////////////////////

class dtkMetaTypeTestCasePrivate
{
public:
    dtkMetaTypeTestCasePrivate(void) : count(0), data(0), derive_data(0), abstract(0), virtual_object(0), virtual_object2(0) {
        ;
    }
    ~dtkMetaTypeTestCasePrivate(void) {
        ;
    }

public:
    int count;

#if !defined(Q_CC_MSVC) || _MSC_FULL_VER > 190023025
    NoCopyableData *no_copyable_data;
    DeriveNoCopyableData *derive_no_copyable_data;
#endif
    Data *data;
    DeriveData *derive_data;
    MyAbstract *abstract;
    VirtualObject *virtual_object;
    VirtualObject2 *virtual_object2;
};

// ///////////////////////////////////////////////////////////////////
// dtkMetaTypeTestCase implementation
// ///////////////////////////////////////////////////////////////////

dtkMetaTypeTestCase::dtkMetaTypeTestCase(void) : QObject(), d(new dtkMetaTypeTestCasePrivate)
{
    // Register debug operators
#if !defined(Q_CC_MSVC) || _MSC_FULL_VER > 190023025
    QMetaType::registerDebugStreamOperator<NoCopyableData *>();
#endif
    QMetaType::registerDebugStreamOperator<Data>();
    QMetaType::registerDebugStreamOperator<Data *>();
    QMetaType::registerDebugStreamOperator<MyAbstract *>();
    QMetaType::registerDebugStreamOperator<VirtualObject *>();

    // Register converters
    //QMetaType::registerConverter<DeriveData*, Data*>();
    //QMetaType::registerConverter<DeriveMyAbstract*, MyAbstract*>();
}

dtkMetaTypeTestCase::~dtkMetaTypeTestCase(void)
{

}

void dtkMetaTypeTestCase::initTestCase(void)
{

}

void dtkMetaTypeTestCase::init(void)
{
    d->count = 0;

#if !defined(Q_CC_MSVC) || _MSC_FULL_VER > 190023025
    d->no_copyable_data = new NoCopyableData(d->count ++, "PNoCopyableData");

    d->derive_no_copyable_data = new DeriveNoCopyableData(d->count++, "PDeriveNoCopyableData", 5573.);
#endif

    d->data = new Data(d->count ++, "PData");

    d->derive_data = new DeriveData(d->count++, "PDeriveData", 0.879);

    d->abstract = new DeriveMyAbstract();
    d->abstract->setName("PDeriveMyAbstract");
    d->abstract->setId(d->count++);

    d->virtual_object = new DeriveVirtualObject();
    d->virtual_object->setName("PDeriveVirtualObject");
    d->virtual_object->setId(d->count++);

    d->virtual_object2 = new DeriveVirtualObject();
    d->virtual_object2->setName("PDeriveVirtualObject2");
    d->virtual_object2->setId(d->count++);
}

void dtkMetaTypeTestCase::cleanup(void)
{
#if !defined(Q_CC_MSVC) || _MSC_FULL_VER > 190023025
    delete d->no_copyable_data;
    delete d->derive_no_copyable_data;
#endif
    delete d->data;
    delete d->derive_data;
    delete d->abstract;
    delete d->virtual_object;
    delete d->virtual_object2;
}

void dtkMetaTypeTestCase::cleanupTestCase(void)
{

}

void dtkMetaTypeTestCase::testCanConvert(void)
{
    // Non QObject No Copyable Data pointer
#if !defined(Q_CC_MSVC) || _MSC_FULL_VER > 190023025
    {
        QVERIFY(!dtkMetaType::canConvert<NoCopyableData *>(QMetaType::type("DeriveNoCopyableData*")));

        QVERIFY(!dtkMetaType::canConvert<DeriveNoCopyableData *>(QMetaType::type("NoCopyableData*")));
        QMetaType::registerConverter<DeriveNoCopyableData *, NoCopyableData *>();
        QVERIFY(dtkMetaType::canConvert<DeriveNoCopyableData *>(QMetaType::type("NoCopyableData*")));
    }
#endif

    // Non QObject Data pointer
    {
        QVERIFY(!dtkMetaType::canConvert<Data *>(QMetaType::type("DeriveData*")));

        QVERIFY(!dtkMetaType::canConvert<DeriveData *>(QMetaType::type("Data*")));
        QMetaType::registerConverter<DeriveData *, Data *>();
        QVERIFY(dtkMetaType::canConvert<DeriveData *>(QMetaType::type("Data*")));
    }

    // Non QObject Abstract class
    {
        QVERIFY(!dtkMetaType::canConvert<MyAbstract *>(QMetaType::type("DeriveMyAbstract*")));

        QVERIFY(!dtkMetaType::canConvert<DeriveMyAbstract *>(QMetaType::type("MyAbstract*")));
        QMetaType::registerConverter<DeriveMyAbstract *, MyAbstract *>();
        QVERIFY(dtkMetaType::canConvert<DeriveMyAbstract *>(QMetaType::type("MyAbstract*")));
    }

    // QObject Abstract class
    {
        QVERIFY(dtkMetaType::canConvert<DeriveVirtualObject *>(QMetaType::type("VirtualObject*")));

        QVERIFY(!dtkMetaType::canConvert<DeriveVirtualObject *>(QMetaType::type("VirtualObject2*")));
        qRegisterMetaType<VirtualObject2 *>();
        QVERIFY(dtkMetaType::canConvert<DeriveVirtualObject *>(QMetaType::type("VirtualObject2*")));

        QVERIFY(!dtkMetaType::canConvert<VirtualObject2 *>(QMetaType::type("VirtualObject *")));
        QMetaType::registerConverter<VirtualObject2 *, VirtualObject *>();
        QVERIFY(dtkMetaType::canConvert<VirtualObject2 *>(QMetaType::type("VirtualObject*")));
    }
}

void dtkMetaTypeTestCase::testVariantFromValue(void)
{

    // Non QObject No copyable Data pointer
#if !defined(Q_CC_MSVC) || _MSC_FULL_VER > 190023025
    {
        NoCopyableData *d0 = d->no_copyable_data;
        QVariant v_d0 = dtkMetaType::variantFromValue(d0);
        QVERIFY(v_d0.isValid());
        QCOMPARE(v_d0.typeName(), "NoCopyableData*");
        QCOMPARE(*(v_d0.value<NoCopyableData *>()), *d0);

        DeriveNoCopyableData *dd0 = d->derive_no_copyable_data;
        QVariant v_dd0 = dtkMetaType::variantFromValue(dd0);
        QVERIFY(v_dd0.isValid());
        QCOMPARE(v_dd0.typeName(), "DeriveNoCopyableData*");
        QCOMPARE(*(v_dd0.value<DeriveNoCopyableData *>()), *dd0);
        QVERIFY(v_dd0.canConvert(v_d0.userType()));

        NoCopyableData *d1 = dd0;
        QVariant v_d1 = dtkMetaType::variantFromValue(d1);
        QVERIFY(v_d1.isValid());
        QVERIFY(v_d1.userType() != v_dd0.userType());
        QCOMPARE(v_d1.typeName(), "NoCopyableData*");

        NoCopyableData *d2 = v_dd0.value<NoCopyableData *>();
        QCOMPARE(*d1, *d2);
    }
#endif

    // Non QObject Data
    {
        Data d0 = *d->data;
        QVariant v_d0 = dtkMetaType::variantFromValue(d0);
        QVERIFY(v_d0.isValid());
        QCOMPARE(v_d0.typeName(), "Data");
        QCOMPARE(v_d0.value<Data>(), d0);
    }

    // Non QObject Data pointer
    {
        Data *d0 = d->data;
        QVariant v_d0 = dtkMetaType::variantFromValue(d0);
        QVERIFY(v_d0.isValid());
        QCOMPARE(v_d0.typeName(), "Data*");
        QCOMPARE(*(v_d0.value<Data *>()), *d0);

        DeriveData *dd0 = d->derive_data;
        QVariant v_dd0 = dtkMetaType::variantFromValue(dd0);
        QVERIFY(v_dd0.isValid());
        QCOMPARE(v_dd0.typeName(), "DeriveData*");
        QCOMPARE(*(v_dd0.value<DeriveData *>()), *dd0);
        QVERIFY(v_dd0.canConvert(v_d0.userType()));

        Data *d1 = dd0;
        QVariant v_d1 = dtkMetaType::variantFromValue(d1);
        QVERIFY(v_d1.isValid());
        QVERIFY(v_d1.userType() != v_dd0.userType());
        QCOMPARE(v_d1.typeName(), "Data*");

        Data *d2 = v_dd0.value<Data *>();
        QCOMPARE(*d1, *d2);
    }

    // Non QObject Abstract class
    {
        MyAbstract *a0 = d->abstract;

        QVariant v_a0 = dtkMetaType::variantFromValue(a0);
        QVERIFY(v_a0.isValid());
        QCOMPARE(v_a0.typeName(), "MyAbstract*");
        QCOMPARE(*(v_a0.value<MyAbstract *>()), *a0);

        DeriveMyAbstract *b0 = dynamic_cast<DeriveMyAbstract *>(a0);
        QVariant v_b0 = dtkMetaType::variantFromValue(b0);
        QVERIFY(v_b0.isValid());
        QCOMPARE(v_b0.typeName(), "DeriveMyAbstract*");
        QCOMPARE(*(v_b0.value<DeriveMyAbstract *>()), *b0);

        QVERIFY(v_b0.canConvert(v_a0.userType()));
        QVERIFY(v_b0.convert(v_a0.userType()));

    }

    // QObject Abstract class
    {
        VirtualObject *a0 = d->virtual_object;

        // As DeriveVirtualObject* type has been registered, the
        // created variant is of the lowest type even if it is created
        // from the abstract class.
        QVariant v_a0 = dtkMetaType::variantFromValue(a0);
        QVERIFY(v_a0.isValid());
        QCOMPARE(v_a0.typeName(), "DeriveVirtualObject*");
        QCOMPARE(*(v_a0.value<VirtualObject *>()), *a0);

        VirtualObject2 *b1 = d->virtual_object2;
        QVariant vv_b1 = QVariant::fromValue(b1);
        QVERIFY(vv_b1.canConvert(qMetaTypeId<VirtualObject *>()));
        QVERIFY(vv_b1.convert(qMetaTypeId<VirtualObject *>()));
        QCOMPARE(*(vv_b1.value<VirtualObject *>()), *(dynamic_cast<VirtualObject *>(b1)));
    }
}

void dtkMetaTypeTestCase::testClone(void)
{
#if !defined(Q_CC_MSVC) || _MSC_FULL_VER > 190023025
    // Non QObject No Copyable Data pointer
    {
        // Cloning return nullptr;
        NoCopyableData *d0 = d->no_copyable_data;
        NoCopyableData *c0 = dtkMetaType::clone(d0);
        QVERIFY(!c0);

        // Cloning return nullptr;
        DeriveNoCopyableData *dd0 = d->derive_no_copyable_data;
        DeriveNoCopyableData *cc0 = dtkMetaType::clone(dd0);
        QVERIFY(!cc0);

        // Cloning return nullptr;
        NoCopyableData *d1 = dd0;
        NoCopyableData *c1 = dtkMetaType::clone(d1);
        QVERIFY(!c1);
    }
#endif

    // Non QObject Data pointer
    {
        Data *d0 = d->data;
        Data *c0 = dtkMetaType::clone(d0);
        QCOMPARE(*d0, *c0);

        DeriveData *dd0 = d->derive_data;
        DeriveData *cc0 = dtkMetaType::clone(dd0);
        QCOMPARE(*dd0, *cc0);

        // When cloning from parent class, slicing occurs.
        Data *d1 = dd0;
        Data *c1 = dtkMetaType::clone(d1);
        // The resulting copy is not a DeriveData object.
        QVERIFY(!dynamic_cast<DeriveData *>(c1));
    }

    // Non QObject Abstract class
    {
        MyAbstract *a0 = d->abstract;
        QVERIFY(dynamic_cast<DeriveMyAbstract *>(a0));

        // Here again slicing occurs
        MyAbstract *c0 = dtkMetaType::clone(a0);
        QVERIFY(!dynamic_cast<DeriveMyAbstract *>(c0));
    }

    // QObject Abstract class
    {
        VirtualObject *a0 = d->virtual_object;
        QVERIFY(dynamic_cast<DeriveVirtualObject *>(a0));

        // To avoid slicing when copying, the deriveed class must be
        // registered at runtime
        qRegisterMetaType<DeriveVirtualObject>();
        VirtualObject *c0 = dtkMetaType::clone(a0);
        QVERIFY(dynamic_cast<DeriveVirtualObject *>(c0));
        QCOMPARE(*c0, *a0);

        VirtualObject2 *b1 = d->virtual_object2;
        VirtualObject2 *c1 = dtkMetaType::clone(b1);
        QVERIFY(dynamic_cast<DeriveVirtualObject *>(c1));
        QCOMPARE(*c1, *b1);
    }
}

void dtkMetaTypeTestCase::testCopy(void)
{
    // Non QObject No Copyable Data pointer
#if !defined(Q_CC_MSVC) || _MSC_FULL_VER > 190023025
    {
        // Cloning return nullptr;
        NoCopyableData *d0 = d->no_copyable_data;
        NoCopyableData *c0 = new NoCopyableData(-12, "dummy");
        dtkMetaType::copy(d0, c0);
        QCOMPARE(QString("dummy"), c0->name());
        delete c0;

        // Cloning return nullptr;
        DeriveNoCopyableData *dd0 = d->derive_no_copyable_data;
        DeriveNoCopyableData *cc0 = new DeriveNoCopyableData(-12, "dummy", 3.14159);
        dtkMetaType::copy(dd0, cc0);
        QCOMPARE(3.14159, cc0->value());
        delete cc0;

    }
#endif

    // Non QObject Data pointer
    {
        Data *d0 = d->data;
        Data *c0 = new Data();
        dtkMetaType::copy(d0, c0);
        QCOMPARE(*d0, *c0);
        delete c0;

        DeriveData *dd0 = d->derive_data;
        DeriveData *cc0 = new DeriveData();
        dtkMetaType::copy(dd0, cc0);
        QCOMPARE(*dd0, *cc0);
        delete cc0;

        // When cloning from parent class, slicing occurs.
        Data *d1 = dd0;
        Data *c1 = new DeriveData;
        dtkMetaType::copy(d1, c1);
        QVERIFY(!(*dd0 == *dynamic_cast<DeriveData *>(c1)));
        delete c1;
    }

    // Non QObject Abstract class
    {
        MyAbstract *a0 = d->abstract;
        QVERIFY(dynamic_cast<DeriveMyAbstract *>(a0));

        // No slicing occurs since the Abstract class is copy
        // assignable at the top level and handles all the
        // members. But it is luck.
        MyAbstract *c0 = new DeriveMyAbstract;
        dtkMetaType::copy(a0, c0);
        QCOMPARE(*a0, *c0);
        delete c0;
    }

    // QObject Abstract class
    {
        VirtualObject *a0 = d->virtual_object;
        QVERIFY(dynamic_cast<DeriveVirtualObject *>(a0));

        // To avoid slicing when copying, the deriveed class must be
        // registered at runtime
        qRegisterMetaType<DeriveVirtualObject>();
        VirtualObject *c0 = new DeriveVirtualObject;
        dtkMetaType::copy(a0, c0);
        QCOMPARE(*c0, *a0);
        delete c0;

        VirtualObject2 *b1 = d->virtual_object2;
        VirtualObject2 *c1 = new DeriveVirtualObject;
        dtkMetaType::copy(b1, c1);
        QCOMPARE(*c1, *b1);
        delete c1;
    }
}

void dtkMetaTypeTestCase::testCloneContent(void)
{
    // Non QObject Data pointer
    {
        int a = 67;
        QVariant v = dtkMetaType::variantFromValue(a);

        QVariant vv = dtkMetaType::cloneContent(v);
    }

    {
        // QObject *o = new QObject();
        // QVariant v = QVariant::fromValue(o);
        // qDebug() << v << QMetaType::TypeFlags(v.userType());

    }

    // Non QObject No copyable Data pointer
#if !defined(Q_CC_MSVC) || _MSC_FULL_VER > 190023025
    {
        NoCopyableData *d0 = d->no_copyable_data;
        QVariant v = dtkMetaType::variantFromValue(d0);
        QVariant vv = dtkMetaType::cloneContent(v);
        NoCopyableData *c0 = vv.value<NoCopyableData *>();
        QVERIFY(!c0);

        DeriveNoCopyableData *dd0 = d->derive_no_copyable_data;
        v = dtkMetaType::variantFromValue(dd0);

        if (QMetaType::type("DeriveNoCopyableData*") == QMetaType::UnknownType)
            qRegisterMetaType<DeriveNoCopyableData *>();

        vv = dtkMetaType::cloneContent(v);
        DeriveNoCopyableData *cc0 = vv.value<DeriveNoCopyableData *>();
        QVERIFY(!cc0);
    }
#endif

    // Non QObject Data pointer
    {
        Data *d0 = d->data;
        QVariant v = dtkMetaType::variantFromValue(d0);
        QVariant vv = dtkMetaType::cloneContent(v);
        Data *c0 = vv.value<Data *>();
        QVERIFY(static_cast<void *>(d0) != static_cast<void *>(c0));
        QCOMPARE(*d0, *c0);

        DeriveData *dd0 = d->derive_data;
        v = dtkMetaType::variantFromValue(dd0);

        if (QMetaType::type("DeriveData") == QMetaType::UnknownType)
            qRegisterMetaType<DeriveData>();

        vv = dtkMetaType::cloneContent(v);
        DeriveData *cc0 = vv.value<DeriveData *>();
        QVERIFY(static_cast<void *>(dd0) != static_cast<void *>(cc0));
        QCOMPARE(*dd0, *cc0);

        // When cloning from parent class, slicing occurs.
        Data *d1 = dd0;
        v = dtkMetaType::variantFromValue(d1);
        vv = dtkMetaType::cloneContent(v);
        Data *c1 = vv.value<Data *>();
        // The resulting copy is not a DeriveData object.
        QVERIFY(!dynamic_cast<DeriveData *>(c1));
    }

    // // Non QObject Abstract class
    // {
    //     MyAbstract *a0 = d->abstract;
    //     QVERIFY(dynamic_cast<DeriveMyAbstract*>(a0));

    //     // Here again slicing occurs
    //     QVariant v = dtkMetaType::variantFromValue(a0);
    //     QVariant vv = dtkMetaType::cloneContent(v);
    //     MyAbstract *c0 = vv.value<MyAbstract *>();
    //     QVERIFY(!dynamic_cast<DeriveMyAbstract*>(c0));
    // }

    // QObject Abstract class
    {
        VirtualObject *a0 = d->virtual_object;
        QVERIFY(dynamic_cast<DeriveVirtualObject *>(a0));

        // To avoid slicing when copying, the deriveed class must be
        // registered at runtime
        qRegisterMetaType<DeriveVirtualObject>();
        QVariant v = dtkMetaType::variantFromValue(a0);
        QVariant vv = dtkMetaType::cloneContent(v);
        VirtualObject *c0 = vv.value<VirtualObject *>();
        QVERIFY(dynamic_cast<DeriveVirtualObject *>(c0));
        QCOMPARE(*c0, *a0);

        VirtualObject2 *b1 = d->virtual_object2;
        v = dtkMetaType::variantFromValue(b1);
        vv = dtkMetaType::cloneContent(v);
        VirtualObject2 *c1 = vv.value<VirtualObject2 *>();
        QVERIFY(dynamic_cast<DeriveVirtualObject *>(c1));
        QCOMPARE(*c1, *b1);
    }
}

void dtkMetaTypeTestCase::testCreateEmptyContainer(void)
{
    {
        QVector<double> vec(5, 3.14159);
        QVariant var = dtkMetaType::variantFromValue(vec);
        var.clear();
        var = dtkMetaType::variantFromValue(&vec);
        QVERIFY(var.canConvert<dtkMetaContainerSequential>());

        QVariant res = dtkMetaType::createEmptyContainer(var);
        QVector<double> *v_res = res.value<QVector<double> *>();
        QVERIFY(v_res);
        QVERIFY(v_res->size() == 0);
        delete v_res;
    }

    {
        QList<double> list;
        list << 3.14159;
        list << 3.14159;
        list << 3.14159;
        list << 3.14159;
        list << 3.14159;

        QVariant var = dtkMetaType::variantFromValue(list);
        var.clear();
        var = dtkMetaType::variantFromValue(&list);
        QVERIFY(var.canConvert<dtkMetaContainerSequential>());

        QVariant res = dtkMetaType::createEmptyContainer(var);
        QList<double> *l_res = res.value<QList<double> *>();
        QVERIFY(l_res);
        QVERIFY(l_res->size() == 0);
        delete l_res;
    }
}

void dtkMetaTypeTestCase::testDestroyPointer(void)
{
    {
        QVector<double> *vec = NULL;
        QVariant var = dtkMetaType::variantFromValue(vec);
        QVERIFY(var.canConvert<dtkMetaContainerSequential>());
        QVERIFY(!dtkMetaType::destroyPointer(var));

        vec = new QVector<double>(5, 3.14159);
        var = dtkMetaType::variantFromValue(vec);
        QVERIFY(dtkMetaType::destroyPointer(var));
    }
}

DTKTEST_MAIN_NOGUI(dtkMetaTypeTest, dtkMetaTypeTestCase)

#include "dtkMetaTypeTest.moc"

//
// dtkMetaTypeTest.cpp ends here
