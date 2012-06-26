/* dtkTestSingleton.cpp ---
 *
 * Author: Babette Lekouta
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Aug 18 19:42:04 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr  3 16:52:09 2012 (+0200)
 *           By: Babette Lekouta
 *     Update #: 2
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkSmartPointerTest.h"

#include <dtkConfig.h>

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkGlobal.h>

#include <dtkCore/dtkSmartPointer.h>

#include <vector>

#include <QtCore>

class dtkSmartPointerTestData : public dtkAbstractData
{
public:
     dtkSmartPointerTestData(void) {}
    ~dtkSmartPointerTestData(void) {}

    static dtkAbstractData *create(void) {
        return new  dtkSmartPointerTestData();
    }

    QString description(void) const {
        return s_type;
    }

    static bool registerType(void) {
        return dtkAbstractDataFactory::instance()->registerDataType(s_type, create);
    }

public:
    static QString s_type;
};

QString dtkSmartPointerTestData::s_type = "dtkSmartPointerTestDataType";

// /////////////////////////////////////////////////////////////////
// dtkSmartPointerTestObject
// /////////////////////////////////////////////////////////////////

class dtkSmartPointerTestObjectPrivate
{
public:
    dtkSmartPointer<dtkSmartPointerTestData> instance;
    dtkSmartPointer<dtkSmartPointerTestData> myOtherInstance;
    dtkSmartPointer<dtkSmartPointerTestData> myOtherInstance2;

};

dtkSmartPointerTestObject::dtkSmartPointerTestObject(void)
{
    d = NULL;
}

dtkSmartPointerTestObject::~dtkSmartPointerTestObject(void)
{

}

void dtkSmartPointerTestObject::initTestCase(void)
{
    if(!dtkSmartPointerTestData::registerType())
        QFAIL("Unable to register test data to data factory");

    d = new dtkSmartPointerTestObjectPrivate;
}

void dtkSmartPointerTestObject::init(void)
{

}

void dtkSmartPointerTestObject::cleanup(void)
{

}

void dtkSmartPointerTestObject::cleanupTestCase(void)
{
    if (d)
        delete d;
}

void dtkSmartPointerTestObject::testSmartPointer(void)
{
    // First check basic factory creation.
    dtkAbstractDataFactory *factory = dtkAbstractDataFactory::instance();
    dtkAbstractData *pData = factory->create( dtkSmartPointerTestData::s_type );
    QVERIFY(pData != NULL);
    pData->enableDeferredDeletion(false);
    QVERIFY(pData->count() == 0);

    dtkSmartPointerTestData *pTestData = dynamic_cast< dtkSmartPointerTestData * >( pData );
    QVERIFY(pData != NULL);
    pTestData = NULL;
    delete pData;
    pData = NULL;

    // Instantiate, test for Null.
    QVERIFY( !d->instance );
    QVERIFY( d->instance.isNull() );
    QVERIFY( d->instance.refCount() == 0 );

    pData = factory->create( dtkSmartPointerTestData::s_type );
    QVERIFY(pData != NULL);
    d->instance = dynamic_cast<dtkSmartPointerTestData*>(pData);
    QVERIFY( d->instance );
    QVERIFY( !d->instance.isNull() );
    QVERIFY( d->instance.refCount() == 1 );
    d->instance->enableDeferredDeletion(false);

    // Test assignment to NULL
    dtkSmartPointerTestData *notSmartPtr =  d->instance;
    notSmartPtr =  d->instance;
    notSmartPtr->retain();
    QVERIFY( notSmartPtr->count() == 2 );
    d->instance = NULL;
    QVERIFY(!d->instance );
    QVERIFY( notSmartPtr->count() == 1 );
    d->instance.takePointer( notSmartPtr );
    QVERIFY( d->instance.refCount() == 1 );
    notSmartPtr = NULL;

    d->myOtherInstance = factory->createSmartPointer( dtkSmartPointerTestData::s_type );
    d->myOtherInstance->enableDeferredDeletion(false);

    d->myOtherInstance2 = factory->createSmartPointer( dtkSmartPointerTestData::s_type );
    d->myOtherInstance2->enableDeferredDeletion(false);

    { // Test copy-construction of dtkSmartPointer.
        dtkSmartPointer< dtkSmartPointerTestData > copyInstance(d->instance) ;
        QVERIFY( !copyInstance.isNull() );
        QVERIFY( copyInstance == d->instance );
        QVERIFY( copyInstance != d->myOtherInstance );
        QVERIFY( copyInstance.refCount() == 2 );
    }

    {   // Test assignment construction (same type)
        dtkSmartPointer< dtkSmartPointerTestData > copyInstance(d->instance) ;
        QVERIFY( !copyInstance.isNull() );
        QVERIFY( copyInstance == d->instance );
        QVERIFY( copyInstance != d->myOtherInstance );
        QVERIFY( copyInstance.refCount() == 2 );

        // Test assignment (same type)
        copyInstance = d->myOtherInstance;
        QVERIFY( !copyInstance.isNull() );
        QVERIFY( copyInstance != d->instance );
        QVERIFY( copyInstance == d->myOtherInstance );
        QVERIFY( copyInstance.refCount() == 2 );

    }

    {   // Test copy constructor from other type
        dtkSmartPointer< dtkAbstractData > basePtr( d->instance );
        QVERIFY( !basePtr.isNull() );
        QVERIFY( basePtr == d->instance );
        QVERIFY( basePtr.refCount() == 2);
    }

    {   // Test assignment from other type.
        dtkSmartPointer< dtkAbstractData > basePtr;
        basePtr = d->instance;
        QVERIFY( !basePtr.isNull() );
        QVERIFY( basePtr == d->instance );
        QVERIFY( basePtr.refCount() == 2);
    }

    QVERIFY( d->instance.refCount() == 1);

}

void dtkSmartPointerTestObject::testSmartPointerSet(void)
{
    // Test a set - this needs a hash function
    typedef QSet< dtkSmartPointer< dtkAbstractData > > DataSetContainer;
    DataSetContainer mySetContainer;

    dtkAbstractDataFactory *factory = dtkAbstractDataFactory::instance();

    d->myOtherInstance = factory->createSmartPointer( dtkSmartPointerTestData::s_type );
    d->myOtherInstance->enableDeferredDeletion(false);

    d->myOtherInstance2 = factory->createSmartPointer( dtkSmartPointerTestData::s_type );
    d->myOtherInstance2->enableDeferredDeletion(false);


    // Add smartpointer instances.
    mySetContainer.insert(d->instance);
    mySetContainer.insert(d->myOtherInstance);
    mySetContainer.insert(d->myOtherInstance2);

    // Should now have 2 registered instances, 1 in this scope, 1 in container
    QVERIFY( d->instance.refCount() == 2);
    QVERIFY( d->myOtherInstance.refCount() == 2);
    QVERIFY( d->myOtherInstance2.refCount() == 2);

    // After clearing the container the references should be cleared.
    mySetContainer.clear();
    QVERIFY( d->instance.refCount() == 1);
    QVERIFY( d->myOtherInstance.refCount() == 1);
    QVERIFY( d->myOtherInstance2.refCount() == 1);

}

void dtkSmartPointerTestObject::testSmartPointerHash(void)
{
    dtkAbstractDataFactory *factory = dtkAbstractDataFactory::instance();

    d->myOtherInstance = factory->createSmartPointer( dtkSmartPointerTestData::s_type );
    d->myOtherInstance->enableDeferredDeletion(false);

    d->myOtherInstance2 = factory->createSmartPointer( dtkSmartPointerTestData::s_type );
    d->myOtherInstance2->enableDeferredDeletion(false);

    typedef QHash<QString, dtkSmartPointer< dtkAbstractData > > DataContainer;
    DataContainer myHashMapContainer;
    myHashMapContainer["bar"] = d->instance;
    myHashMapContainer["foo"] = d->myOtherInstance;
    myHashMapContainer["gee"] = d->myOtherInstance2;

    QVERIFY( d->instance.refCount() == 2);
    QVERIFY( d->myOtherInstance.refCount() == 2);
    QVERIFY( d->myOtherInstance2.refCount() == 2);

    myHashMapContainer.clear();

    QVERIFY( d->instance.refCount() == 1);
    QVERIFY( d->myOtherInstance.refCount() == 1);
    QVERIFY( d->myOtherInstance2.refCount() == 1);

}

void dtkSmartPointerTestObject::testSmartPointerVector(void)
{
    dtkAbstractDataFactory *factory = dtkAbstractDataFactory::instance();

    dtkSmartPointerTestData *notSmartPtr =  d->instance;

    d->myOtherInstance = factory->createSmartPointer( dtkSmartPointerTestData::s_type );
    d->myOtherInstance->enableDeferredDeletion(false);

    d->myOtherInstance2 = factory->createSmartPointer( dtkSmartPointerTestData::s_type );
    d->myOtherInstance2->enableDeferredDeletion(false);


    // And an stl container
    typedef std::vector< dtkSmartPointer< dtkAbstractData > > StlContainer;
    StlContainer myVector;
    myVector.push_back( d->instance );
    myVector.push_back( d->myOtherInstance );
    myVector.push_back( d->myOtherInstance2 );
    QVERIFY( d->instance.refCount() == 2);
    QVERIFY( d->myOtherInstance.refCount() == 2);
    QVERIFY( d->myOtherInstance2.refCount() == 2);

    // Now manipulate the vector
    myVector.resize(2);
    QVERIFY( d->instance.refCount() == 2);
    QVERIFY( d->myOtherInstance.refCount() == 2);
    QVERIFY( d->myOtherInstance2.refCount() == 1);

    // This may cause a re-assignment of the buffer used by the vector.
    myVector.resize(10);
    QVERIFY( d->instance.refCount() == 2);
    QVERIFY( d->myOtherInstance.refCount() == 2);
    QVERIFY( d->myOtherInstance2.refCount() == 1);

    QVERIFY( myVector.at(0) == d->instance);
    QVERIFY( myVector.at(1) == d->myOtherInstance);
    QVERIFY( myVector.at(9).isNull());

    myVector.clear();
    QVERIFY( d->instance.refCount() == 1);
    QVERIFY( d->myOtherInstance.refCount() == 1);
    QVERIFY( d->myOtherInstance2.refCount() == 1);

    // Test releasePointer();
    notSmartPtr = d->instance.releasePointer();
    QVERIFY( d->instance.isNull() );
    QVERIFY( notSmartPtr != NULL );
    QVERIFY( notSmartPtr->count() == 1 );

    {   // Test const-ness
        const dtkSmartPointerTestData* pConstData = d->myOtherInstance;
        dtkSmartPointer<const dtkSmartPointerTestData> myConstInstance;
        myConstInstance = pConstData;

        QVERIFY( !myConstInstance.isNull() );
        QVERIFY( myConstInstance == d->myOtherInstance );
        QVERIFY( d->myOtherInstance.refCount() == 2 );

        dtkSmartPointer<const dtkSmartPointerTestData> myOtherConstInstance = myConstInstance;
        QVERIFY(myOtherConstInstance->description() == dtkSmartPointerTestData::s_type);
    }

    // Test constructor from pointer.
    // This constructs the smart pointer, and adds a reference.
    d->instance = dtkSmartPointer<dtkSmartPointerTestData>( notSmartPtr );
    QVERIFY( !d->instance.isNull() );
    QVERIFY( d->instance.refCount() == 2 );
    notSmartPtr->release();

}

DTKTEST_NOGUI_MAIN(dtkSmartPointerTest, dtkSmartPointerTestObject)
