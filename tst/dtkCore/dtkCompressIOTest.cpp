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

#include "dtkCompressIOTest.h"

#include <dtkCore>
#include <QtCore>


// ///////////////////////////////////////////////////////////////////
// dtkIteratorTestCase
// ///////////////////////////////////////////////////////////////////

dtkCompressIOTestCase::dtkCompressIOTestCase(void)
{
}

dtkCompressIOTestCase::~dtkCompressIOTestCase(void)
{
}

void dtkCompressIOTestCase::initTestCase(void)
{
}

void dtkCompressIOTestCase::init(void)
{

}

void dtkCompressIOTestCase::testWrite(void)
{
    QFile file("foo.gz");
    QByteArray data = QByteArray("The quick brown fox\nhello world\n");
    dtkIOCompressor compressor(&file);
    compressor.open(QIODevice::WriteOnly);
    compressor.write(data);
    compressor.close();
}

void dtkCompressIOTestCase::testRead(void)
{
    QByteArray data = QByteArray("The quick brown fox\n");
    QFile file("foo.gz");

    dtkIOCompressor compressor(&file);
    compressor.open(QIODevice::ReadOnly);
    QByteArray text = compressor.readLine();
    QVERIFY (data == text);

    data = QByteArray("hello world\n");
    text = compressor.readLine();
    QVERIFY (data == text);
    compressor.close();

}


void dtkCompressIOTestCase::cleanup(void)
{

}

void dtkCompressIOTestCase::cleanupTestCase(void)
{
}

DTKTEST_MAIN_NOGUI(dtkCompressIOTest, dtkCompressIOTestCase)

//
// dtkCompressIOTest.cpp ends here
