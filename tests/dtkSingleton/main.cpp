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

#include "dtkTestSingleton.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>
#include <dtkCore/dtkSingleton.h>

//#include <dtkCore/dtkSmartPointer.h>

#include <iostream>
#include <stdexcept>

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

inline void CheckTestResult( bool condition, const char *cond, const char *linkText)
{
    if (!condition) {
        QString msg = QString("%1 Test failed (%3)").arg(linkText).arg(cond);
        throw std::runtime_error(msg.toStdString());
    }
}

#define CHECK_TEST_RESULT(cond) CheckTestResult((cond), DTK_STRINGIZE(cond), DTK_LINK_TEXT)


int main(int argc, char *argv[])
{
    int ret = DTK_FAILURE;

    try {

        QCoreApplication app( argc, argv );

        CHECK_TEST_RESULT( dtkTestSingleton::InstanceCount() == 0 );
        dtkTestSingleton * singletonInstance = dtkTestSingleton::instance();
        CHECK_TEST_RESULT( singletonInstance );
        CHECK_TEST_RESULT( dtkTestSingleton::InstanceCount() == 1 );

        // Repeat : instance count should not change.
        singletonInstance = dtkTestSingleton::instance();
        CHECK_TEST_RESULT( singletonInstance );
        CHECK_TEST_RESULT( dtkTestSingleton::InstanceCount() == 1 );

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
