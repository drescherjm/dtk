/* dtkComposerTransmitterHandler.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2012 Tue Dec  4 20:22:24 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */


#ifndef DTKCOMPOSERTRANSMITTERHANDLER_H
#define DTKCOMPOSERTRANSMITTERHANDLER_H



class dtkComposerTransmitterVariant;
class dtkComposerVariant;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler interface
// /////////////////////////////////////////////////////////////////

template <typename T, bool U> class dtkComposerTransmitterHandler
{
public:
    static inline T *copyData(T* data, T*& copy, bool enable_copy);
    static inline T *copyData(T* data, T*& copy, bool enable_copy, dtkComposerVariant& variant);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler specific interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterHandler<T, true>
{
public:
    static inline T *copyData(T* data, T*& copy, bool enable_copy);
    static inline T *copyData(T* data, T*& copy, bool enable_copy, dtkComposerVariant& variant);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariantHandler interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterVariantHandler
{
public:
    static void setData(T& data, dtkComposerTransmitterVariant& t_variant);

public:
    static T data(dtkComposerTransmitterVariant& t_variant);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariantHandler interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterVariantHandler<T*>
{
public:
    static void setData(T *data, dtkComposerTransmitterVariant& t_variant);

public:
    static T *data(dtkComposerTransmitterVariant& t_variant);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariantHandler interface
// /////////////////////////////////////////////////////////////////

template <> class  dtkComposerTransmitterVariantHandler<dtkComposerVariant>
{
public:
    static void setData(dtkComposerVariant& data, dtkComposerTransmitterVariant& t_variant);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterHandler.tpp"

#endif
