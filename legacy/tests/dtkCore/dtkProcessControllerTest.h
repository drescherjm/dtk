/* dtkProcessControllerTest.h ---
 * 
 * Author: Julien Wintz
 * Created: Thu Aug 29 14:48:59 2013 (+0200)
 * Version: 
 * Last-Updated: Thu Aug 29 17:05:31 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 23
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkCore/dtkTest.h>

class dtkProcessControllerTestObjectPrivate;

class dtkProcessControllerTestObject : public QObject
{
    Q_OBJECT

public:
     dtkProcessControllerTestObject(void);
    ~dtkProcessControllerTestObject(void);

private slots:
    void initTestCase(void);
    void init(void);
    
private slots:
    void testStart(void);
    void testProcess(void);
    void testStop(void);

private slots:
    void cleanup(void);
    void cleanupTestCase(void);

private:
    dtkProcessControllerTestObjectPrivate *d;
};
