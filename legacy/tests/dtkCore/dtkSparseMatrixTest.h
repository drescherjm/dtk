/* dtkSparseMatrixTest.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: mar. janv. 28 16:54:23 2014 (+0100)
 */

/* Change Log:
 * 
 */


#pragma once

#include <dtkCore/dtkTest.h>

//class dtkSparseMatrixTestObjectPrivate;

class dtkSparseMatrixTestObject : public QObject
{
    Q_OBJECT

public:
             dtkSparseMatrixTestObject(void);
    virtual ~dtkSparseMatrixTestObject(void);

private slots:
    void initTestCase(void);
    void init(void);
    void cleanup(void);
    void cleanupTestCase(void);

private slots:
    void testCreate(void);

private:
    //dtkSparseMatrixTestObjectPrivate *d;
};


