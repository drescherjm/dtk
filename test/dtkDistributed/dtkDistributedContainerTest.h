/* dtkDistributedContainerTest.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Mon Feb  4 15:37:01 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include <QtTest>

class dtkDistributedContainerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void test(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
