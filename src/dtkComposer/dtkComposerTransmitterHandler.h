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



#pragma once

class dtkComposerTransmitter;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterHandler
{
public:
    static void init(dtkComposerTransmitter& t);

public:
    static bool enableConnection(dtkComposerTransmitter& t);

public:
    static T      data(dtkComposerTransmitter& t);
    static T constData(dtkComposerTransmitter& t);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterHandler<T *>
{
public:
    static void init(dtkComposerTransmitter& t);

public:
    static bool enableConnection(dtkComposerTransmitter& t);

public:
    static T      *data(dtkComposerTransmitter& t);
    static T *constData(dtkComposerTransmitter& t);

protected:
    static T *copy(T * source, QVariant& target, QVariant& swap);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandlerVariant
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterHandlerVariant
{
public:
    static QVariant data(dtkComposerTransmitter& t);

protected:
    static bool containSamePointer(const QVariant& v0, const QVariant& v1);
    static void clearPointer(QVariant& v);
    static void copy(const QVariant& source, QVariant& target);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterHandler.tpp"

// 
// dtkComposerTransmitterHandler.h ends here
