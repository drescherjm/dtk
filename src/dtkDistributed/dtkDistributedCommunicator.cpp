/* @(#)dtkDistributedCommunicator.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/07 13:59:41
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedCommunicator.h"

// #include <dtk/dtkGlobal.h>

dtkDistributedCommunicator::dtkDistributedCommunicator(void) : QObject()
{

}

dtkDistributedCommunicator::~dtkDistributedCommunicator(void)
{
    // delete d;

    // d = NULL;
}

dtkDistributedCommunicator::dtkDistributedCommunicator(const dtkDistributedCommunicator& other)
{

}

dtkDistributedCommunicator& dtkDistributedCommunicator::operator = (const dtkDistributedCommunicator& other)
{
    return *this;

}

void dtkDistributedCommunicator::initialize(void)
{
   // DTK_DEFAULT_IMPLEMENTATION;
}

bool dtkDistributedCommunicator::initialized(void)
{
   // DTK_DEFAULT_IMPLEMENTATION;

   return false;
}

void dtkDistributedCommunicator::uninitialize(void)
{
   // DTK_DEFAULT_IMPLEMENTATION;
}

int dtkDistributedCommunicator::rank(void)
{
   // DTK_DEFAULT_IMPLEMENTATION;
   return 0;
}

int dtkDistributedCommunicator::size(void)
{
   // DTK_DEFAULT_IMPLEMENTATION;
   return 1;
}

qlonglong dtkDistributedCommunicator::allocate(qlonglong count, qlonglong size, void *buffer)
{
    return -1;
}

void dtkDistributedCommunicator::get(qint32 from, qlonglong position, void *array, qlonglong buffer_id)
{
    
}

QByteArray dtkDistributedCommunicator::get(qint32 from, qlonglong position, qlonglong size, qlonglong buffer_id)
{
    return QByteArray();
}

void dtkDistributedCommunicator::put(qint32 dest, qlonglong position, qlonglong size, const QByteArray &data, qlonglong buffer_id)
{

}

// template<class T> T * get(qint32 from, qlonglong position, qlonglong size, qlonglong buffer_id);
// template<class T> void put(qint32 dest, qlonglong position, qlonglong size, const T &data, qlonglong buffer_id);
