/* dtkComposerTransmitterHandler.tpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Mar 21 15:29:10 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Mar 25 17:04:40 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 154
 */

/* Change Log:
 * 
 */

#include <dtkCore/dtkCore.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler implementation
// /////////////////////////////////////////////////////////////////

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

template <typename T> T *dtkComposerTransmitterHandler<T *>::data(dtkComposerTransmitter& t)
{
    T *source = t.variant().value<T *>();

    switch(t.dataTransmission()) {
    case dtkComposerTransmitter::AutoCopy:
	if (!t.enableCopy()) {
	    return source;
	} else {
	    return dtkComposerTransmitterCopier<T *, IsPointerToTypeDerivedFromCoreObject<T *>::Value>::copy(source, t.d->variant);
	}
    	break;
    case dtkComposerTransmitter::Reference:
    	return source;
    	break;
    case dtkComposerTransmitter::Copy:
    	return dtkComposerTransmitterCopier<T *, IsPointerToTypeDerivedFromCoreObject<T *>::Value>::copy(source, t.d->variant);
    	break;
    default:
        return source;
    }
}

template <typename T> T *dtkComposerTransmitterHandler<T *>::constData(dtkComposerTransmitter& t)
{
    return t.variant().value<T>();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterCopier implementation
// /////////////////////////////////////////////////////////////////

template <typename T, bool U> T *dtkComposerTransmitterCopier<T, U>::copy(T *source, QVariant& target)
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
// dtkComposerTransmitterCopier dtkCoreObject implementation
// /////////////////////////////////////////////////////////////////

template <typename T> T *dtkComposerTransmitterCopier<T, true>::copy(T *source, QVariant& target)
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
