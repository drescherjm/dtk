/* dtkTest.h --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb  4 15:02:54 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Mar 22 11:40:16 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtTest>

#define DTKTEST_MAIN(TestMain, TestObject)	        \
    int TestMain(int argc, char **argv)			\
    {							\
	QApplication app(argc, argv);			\
	TestObject tc;					\
	return QTest::qExec(&tc, argc, argv);		\
    }

#define DTKTEST_MAIN_GUI(TestMain, TestObject)		\
    int TestMain(int argc, char **argv)			\
    {							\
	QGuiApplication app(argc, argv);		\
	TestObject tc;					\
	return QTest::qExec(&tc, argc, argv);		\
    }

#define DTKTEST_MAIN_NOGUI(TestMain, TestObject)	\
    int TestMain(int argc, char **argv)			\
    {							\
	QCoreApplication app(argc, argv);		\
	TestObject tc;					\
	return QTest::qExec(&tc, argc, argv);		\
    }
