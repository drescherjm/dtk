/* dtkComposerTransmitterHandler.tpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Mar 21 15:29:10 2013 (+0100)
 * Version: 
 * Last-Updated: Sat Mar 23 22:54:04 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 140
 */

/* Change Log:
 * 
 */

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler implementation
// /////////////////////////////////////////////////////////////////

template <typename T> T dtkComposerTransmitterHandler<T>::data(dtkComposerTransmitter& t)
{
    return t.d->variant.value<T>();
}

template <typename T> T dtkComposerTransmitterHandler<T>::constData(dtkComposerTransmitter& t)
{
    return t.d->variant.value<T>();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler pointer implementation
// /////////////////////////////////////////////////////////////////

template <typename T> T *dtkComposerTransmitterHandler<T *>::data(dtkComposerTransmitter& t)
{
    T *source = t.variant.value<T *>();

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
    return t.d->variant.value<T>();
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
	copy = new T(*source)
	target.setValue(copy);
    } else {
	*copy = *data;
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
	copy = data->clone();
	target.setValue(copy);
    } else {
	*copy = *data;
    }

    return copy;
}
