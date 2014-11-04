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

#include <dtkMeta/dtkMeta.h>

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
    return dtkMetaType::canConvert<T>(t.d->type_list);
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
    return dtkMetaType::canConvert<T *>(t.d->type_list);
}

template <typename T> T *dtkComposerTransmitterHandler<T *>::data(dtkComposerTransmitter& t)
{
    T *source = t.variant().value<T *>();

    switch(t.dataTransmission()) {
    case dtkComposerTransmitter::AutoCopy:
	if (!t.enableCopy()) {
	    return source;
	} else {
            return copy(source, t.d->variant);
	}
    	break;
    case dtkComposerTransmitter::Reference:
        return source;
        break;
    case dtkComposerTransmitter::Copy:
        return copy(source, t.d->variant);
    	break;
    default:
        return source;
    }
}

template <typename T> T *dtkComposerTransmitterHandler<T *>::constData(dtkComposerTransmitter& t)
{
    return t.variant().value<T *>();
}

template <typename T> inline T *dtkComposerTransmitterHandler<T *>::copy(T *source, QVariant& target)
{
    if (!source)
        return source;

    T *copy = target.value<T *>();
    if (!copy) {
	copy = dtkMetaType::clone(source);
	target.setValue(copy);
    } else {
        *copy = *source;
    }

    return copy;
}

// 
// dtkComposerTransmitterHandler.tpp ends here
