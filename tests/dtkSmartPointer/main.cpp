/* main.cpp --- 
 * 
 * Author: John Stark
 * Copyright (C) 2011 -John Stark, Inria.
 * Created: 
 * Version: $Id$
 * Last-Updated: Tue Jun 28 16:52:15 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 39
 */

/* Commentary: 
 * Perform some tests using dtkSmartPointer with dtkAbstractData-derived objects.
 * 
 * Warning : when the instance count of a dtkAbstractObject reaches zero, it calls (this->deleteLater()).
 * This means that the object is not actually deleted until an event loop is active. 
 * 
 */

/* Change log:
 * 
 */

#include <dtkConfig.h>

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>

#include <dtkCore/dtkSmartPointer.h>

#include <iostream>
#include <stdexcept>
#include <vector>

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class TestData : public dtkAbstractData {
public:
    static QString s_TypeName;

     TestData(void) {}
    ~TestData(void) {}

    static dtkAbstractData *create(void) {
        return new  TestData();
    }

    QString description(void) const {
        return s_TypeName;
    }

    static bool registerType(void) {
        return dtkAbstractDataFactory::instance()->registerDataType(s_TypeName, create);
    }

};

QString TestData::s_TypeName = "TestDataType";

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

inline void CheckTestResult( bool condition, const char *cond, const char *file, const int line = 0 )
{
    if (!condition) {
        QString msg = QString("%1(%2): Test failed (%3)").arg(file).arg(line).arg(cond);
        throw std::runtime_error(msg.toStdString());
    }
}

#define CHECK_TEST_RESULT(cond) CheckTestResult((cond), DTK_STRINGIZE(cond), __FILE__, __LINE__)

int main(int argc, char *argv[])
{
    int ret = DTK_FAILURE;

    try {

        QCoreApplication app( argc, argv );

        if (!TestData::registerType())
            throw(std::runtime_error( "Failed to register data type"));

        dtkAbstractDataFactory *factory = dtkAbstractDataFactory::instance();

        // First check basic factory creation.
        dtkAbstractData *pData = factory->create( TestData::s_TypeName );
        CHECK_TEST_RESULT(pData != NULL);
        pData->enableDeferredDeletion(false);
        CHECK_TEST_RESULT(pData->count() == 0);

        TestData *pTestData = dynamic_cast< TestData * >( pData );
        CHECK_TEST_RESULT(pTestData != NULL);

        pTestData = NULL;
        delete pData;
        pData = NULL;

        // Instantiate, test for Null.
        dtkSmartPointer< TestData > myInstance;
        CHECK_TEST_RESULT( !myInstance );  // Check cast-to-bool
        CHECK_TEST_RESULT( myInstance.isNull() );
        CHECK_TEST_RESULT( myInstance.refCount() == 0 );

        pData = factory->create( TestData::s_TypeName );
        CHECK_TEST_RESULT(pData != NULL);
        myInstance = dynamic_cast<TestData*>(pData);
        CHECK_TEST_RESULT( myInstance );
        CHECK_TEST_RESULT( !myInstance.isNull() );
        CHECK_TEST_RESULT( myInstance.refCount() == 1 );
        myInstance->enableDeferredDeletion(false);

        // Test assignment to NULL
        TestData *notSmartPtr = myInstance;
        notSmartPtr = myInstance;
        notSmartPtr->retain();
        CHECK_TEST_RESULT( notSmartPtr->count() == 2 );
        myInstance = NULL;
        CHECK_TEST_RESULT( !myInstance );
        CHECK_TEST_RESULT( notSmartPtr->count() == 1 );
        myInstance.takePointer( notSmartPtr );
        CHECK_TEST_RESULT( myInstance.refCount() == 1 );
        notSmartPtr = NULL;

        dtkSmartPointer< TestData > myOtherInstance;
        myOtherInstance = factory->createSmartPointer( TestData::s_TypeName );
        myOtherInstance->enableDeferredDeletion(false);

        dtkSmartPointer< TestData > myOtherInstance2;
        myOtherInstance2 = factory->createSmartPointer( TestData::s_TypeName );
        myOtherInstance2->enableDeferredDeletion(false);

        {   // Test copy-construction of dtkSmartPointer.
            dtkSmartPointer< TestData > copyInstance(myInstance) ;
            CHECK_TEST_RESULT( !copyInstance.isNull() );
            CHECK_TEST_RESULT( copyInstance == myInstance );
            CHECK_TEST_RESULT( copyInstance != myOtherInstance );
            CHECK_TEST_RESULT( copyInstance.refCount() == 2 );
        }

        {   // Test assignment construction (same type)
            dtkSmartPointer< TestData > copyInstance = myInstance;
            CHECK_TEST_RESULT( !copyInstance.isNull() );
            CHECK_TEST_RESULT( copyInstance == myInstance );
            CHECK_TEST_RESULT( copyInstance != myOtherInstance );
            CHECK_TEST_RESULT( copyInstance.refCount() == 2 );
            // Test assignment (same type)
            copyInstance = myOtherInstance;
            CHECK_TEST_RESULT( !copyInstance.isNull() );
            CHECK_TEST_RESULT( copyInstance != myInstance );
            CHECK_TEST_RESULT( copyInstance == myOtherInstance );
            CHECK_TEST_RESULT( copyInstance.refCount() == 2 );
        }

        {   // Scope a pointer
            // Test copy constructor from other type
            dtkSmartPointer< dtkAbstractData > basePtr( myInstance );
            CHECK_TEST_RESULT( !basePtr.isNull() );
            CHECK_TEST_RESULT( basePtr == myInstance );
            CHECK_TEST_RESULT( basePtr.refCount() == 2);
        }

        {   // Scope a pointer
            // Test assignment from other type.
            dtkSmartPointer< dtkAbstractData > basePtr;
            basePtr = myInstance;
            CHECK_TEST_RESULT( !basePtr.isNull() );
            CHECK_TEST_RESULT( basePtr == myInstance );
            CHECK_TEST_RESULT( basePtr.refCount() == 2);
            // End of scope, count should decrease.
        }
        CHECK_TEST_RESULT( myInstance.refCount() == 1);

        // Test a set - this needs a hash function
        typedef QSet< dtkSmartPointer< dtkAbstractData > > DataSetContainer;
        DataSetContainer mySetContainer;

        // Add smartpointer instances.
        mySetContainer.insert(myInstance);
        mySetContainer.insert(myOtherInstance);
        mySetContainer.insert(myOtherInstance2);

        // Should now have 2 registered instances, 1 in this scope, 1 in container
        CHECK_TEST_RESULT( myInstance.refCount() == 2);
        CHECK_TEST_RESULT( myOtherInstance.refCount() == 2);
        CHECK_TEST_RESULT( myOtherInstance2.refCount() == 2);

        // After clearing the container the references should be cleared.
        mySetContainer.clear();
        CHECK_TEST_RESULT( myInstance.refCount() == 1);
        CHECK_TEST_RESULT( myOtherInstance.refCount() == 1);
        CHECK_TEST_RESULT( myOtherInstance2.refCount() == 1);

        typedef QHash<QString, dtkSmartPointer< dtkAbstractData > > DataContainer;
        DataContainer myHashMapContainer;
        myHashMapContainer["bar"] = myInstance;
        myHashMapContainer["foo"] = myOtherInstance;
        myHashMapContainer["gee"] = myOtherInstance2;

        CHECK_TEST_RESULT( myInstance.refCount() == 2);
        CHECK_TEST_RESULT( myOtherInstance.refCount() == 2);
        CHECK_TEST_RESULT( myOtherInstance2.refCount() == 2);

        myHashMapContainer.clear();

        CHECK_TEST_RESULT( myInstance.refCount() == 1);
        CHECK_TEST_RESULT( myOtherInstance.refCount() == 1);
        CHECK_TEST_RESULT( myOtherInstance2.refCount() == 1);

        // And an stl container
        typedef std::vector< dtkSmartPointer< dtkAbstractData > > StlContainer;
        StlContainer myVector;
        myVector.push_back( myInstance );
        myVector.push_back( myOtherInstance );
        myVector.push_back( myOtherInstance2 );
        CHECK_TEST_RESULT( myInstance.refCount() == 2);
        CHECK_TEST_RESULT( myOtherInstance.refCount() == 2);
        CHECK_TEST_RESULT( myOtherInstance2.refCount() == 2);

        // Now manipulate the vector
        myVector.resize(2);
        CHECK_TEST_RESULT( myInstance.refCount() == 2);
        CHECK_TEST_RESULT( myOtherInstance.refCount() == 2);
        CHECK_TEST_RESULT( myOtherInstance2.refCount() == 1);

        // This may cause a re-assignment of the buffer used by the vector.
        myVector.resize(10);
        CHECK_TEST_RESULT( myInstance.refCount() == 2);
        CHECK_TEST_RESULT( myOtherInstance.refCount() == 2);
        CHECK_TEST_RESULT( myOtherInstance2.refCount() == 1);

        CHECK_TEST_RESULT( myVector.at(0) == myInstance);
        CHECK_TEST_RESULT( myVector.at(1) == myOtherInstance);
        CHECK_TEST_RESULT( myVector.at(9).isNull());

        myVector.clear();
        CHECK_TEST_RESULT( myInstance.refCount() == 1);
        CHECK_TEST_RESULT( myOtherInstance.refCount() == 1);
        CHECK_TEST_RESULT( myOtherInstance2.refCount() == 1);

        // Test releasePointer();
        notSmartPtr = myInstance.releasePointer();
        CHECK_TEST_RESULT( myInstance.isNull() );
        CHECK_TEST_RESULT( notSmartPtr != NULL );
        CHECK_TEST_RESULT( notSmartPtr->count() == 1 );

        {   // Test const-ness
            const TestData* pConstData = myOtherInstance;
            dtkSmartPointer<const TestData> myConstInstance;
            myConstInstance = pConstData;
            CHECK_TEST_RESULT( !myConstInstance.isNull() );
            CHECK_TEST_RESULT( myConstInstance == myOtherInstance );
            CHECK_TEST_RESULT( myOtherInstance.refCount() == 2 );

            dtkSmartPointer<const TestData> myOtherConstInstance = myConstInstance;
            CHECK_TEST_RESULT(myOtherConstInstance->description() == TestData::s_TypeName);
        }

        // Test constructor from pointer.
        // This constructs the smart pointer, and adds a reference.
        myInstance = dtkSmartPointer<TestData>( notSmartPtr );
        CHECK_TEST_RESULT( !myInstance.isNull() );
        CHECK_TEST_RESULT( myInstance.refCount() == 2 );
        notSmartPtr->release();

        ret = DTK_SUCCEED;
    }
    catch (std::exception &e) {
        dtkDebug() << e.what();
    }
    catch (...) {
        dtkDebug() << "Caught an unknown exception" ;
    }

    if (ret == DTK_SUCCEED) {
        dtkDebug() << " Test succeeded";
    } else {
        dtkDebug() << " Test failed";
    }

    return ret;
}
