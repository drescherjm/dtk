/* dtkComposerTransmitterHandler.tpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Mar 21 15:29:10 2013 (+0100)
 * Version: 
 * Last-Updated: Thu Jul 11 10:03:18 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 273
 */

/* Change Log:
 * 
 */

#include <dtkCore/dtkCore.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler implementation
// /////////////////////////////////////////////////////////////////

template <typename T> void dtkComposerTransmitterHandler<T>::init(dtkComposerTransmitter& t)
{
    t.d->type_list << qMetaTypeId<T>(reinterpret_cast<T *>(0));
    t.d->variant = QVariant(t.d->type_list.first(), 0);
}

template <typename T> bool dtkComposerTransmitterHandler<T>::enableConnection(dtkComposerTransmitter& t)
{
    bool enable_connection = true;
    QVariant var = QVariant(qMetaTypeId<T>(reinterpret_cast<T *>(0)), 0);

    foreach(int t, t.d->type_list) {
	if (!var.canConvert(t)) {
	    enable_connection = false;
	    break;
	}
    }

    return enable_connection;
}

template <typename T> T dtkComposerTransmitterHandler<T>::data(dtkComposerTransmitter& t)
{
    return t.variant().value<T>();
}

template <typename T> T dtkComposerTransmitterHandler<T>::constData(dtkComposerTransmitter& t)
{
    return t.variant().value<T>();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler pointer implementation
// /////////////////////////////////////////////////////////////////

template <typename T> void dtkComposerTransmitterHandler<T *>::init(dtkComposerTransmitter& t)
{
    t.d->type_list << qMetaTypeId<T*>(reinterpret_cast<T **>(0));
    T *ptr = NULL;
    t.d->variant = QVariant::fromValue(ptr);
}

template <typename T> bool dtkComposerTransmitterHandler<T *>::enableConnection(dtkComposerTransmitter& t)
{
    bool enable_connection = true;
    T *ptr = new T();
    QVariant var = QVariant::fromValue(ptr);

    foreach(int t, t.d->type_list) {
	if (!var.canConvert(t)) {
	    enable_connection = false;
	    break;
	}
    }

    delete ptr;

    return enable_connection;
}

template <typename T> T *dtkComposerTransmitterHandler<T *>::data(dtkComposerTransmitter& t)
{
    T *source = t.variant().value<T *>();

    switch(t.dataTransmission()) {
    case dtkComposerTransmitter::AutoCopy:
	if (!t.enableCopy()) {
	    return source;
	} else {
	    return dtkComposerTransmitterHandlerHelper<T *, IsPointerToTypeDerivedFromCoreObject<T *>::Value>::copy(source, t.d->variant);
	}
    	break;
    case dtkComposerTransmitter::Reference:
    	return source;
    	break;
    case dtkComposerTransmitter::Copy:
    	return dtkComposerTransmitterHandlerHelper<T *, IsPointerToTypeDerivedFromCoreObject<T *>::Value>::copy(source, t.d->variant);
    	break;
    default:
        return source;
    }
}

template <typename T> T *dtkComposerTransmitterHandler<T *>::constData(dtkComposerTransmitter& t)
{
    return t.variant().value<T *>();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterCopier implementation
// /////////////////////////////////////////////////////////////////

template <typename T, bool U> T *dtkComposerTransmitterHandlerHelper<T *, U>::copy(T *source, QVariant& target)
{
    if (!source)
        return source;

    T *copy = target.value<T *>();
    if (!copy) {
	copy = new T(*source);
	target.setValue(copy);
    } else {
	*copy = *source;
    }

    return copy;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterCopier implementation for dtkCoreObject
// /////////////////////////////////////////////////////////////////

template <typename T> T *dtkComposerTransmitterHandlerHelper<T *, true>::copy(T *source, QVariant& target)
{
    if (!source)
        return source;

    T *copy = target.value<T*>();;
    if (!copy) {
	copy = source->clone();
	target.setValue(copy);
    } else {
	*copy = *source;
    }

    return copy;
}
