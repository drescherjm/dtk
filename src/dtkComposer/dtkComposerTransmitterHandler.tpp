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

#include <dtkLog>

#include <dtkMeta/dtkMeta.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler implementation
// /////////////////////////////////////////////////////////////////

template <typename T> inline void dtkComposerTransmitterHandler<T>::init(dtkComposerTransmitter& t)
{
    t.d->type_list << qMetaTypeId<T>(reinterpret_cast<T *>(0));
    t.d->variant = QVariant(t.d->type_list.first(), 0);
}

template <typename T> inline bool dtkComposerTransmitterHandler<T>::enableConnection(dtkComposerTransmitter& t)
{
    return dtkMetaType::canConvert<T>(t.d->type_list);
}

template <typename T> inline T dtkComposerTransmitterHandler<T>::data(dtkComposerTransmitter& t)
{
    return t.variant().value<T>();
}

template <typename T> inline T dtkComposerTransmitterHandler<T>::constData(dtkComposerTransmitter& t)
{
    return t.variant().value<T>();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler pointer implementation
// /////////////////////////////////////////////////////////////////

template <typename T> inline void dtkComposerTransmitterHandler<T *>::init(dtkComposerTransmitter& t)
{
    t.d->type_list << qMetaTypeId<T*>(reinterpret_cast<T **>(0));
    T *ptr = NULL;
    t.d->variant = QVariant::fromValue(ptr);
    t.d->swap = QVariant::fromValue(ptr);
}

template <typename T> inline bool dtkComposerTransmitterHandler<T *>::enableConnection(dtkComposerTransmitter& t)
{
    return dtkMetaType::canConvert<T *>(t.d->type_list);
}

template <typename T> inline T *dtkComposerTransmitterHandler<T *>::data(dtkComposerTransmitter& t)
{
    T *source = t.variant().value<T *>();

    switch(t.dataTransmission()) {
    case dtkComposerTransmitter::AutoCopy:
	if (!t.enableCopy()) {
	    return source;
	} else {
        return copy(source, t.d->variant, t.d->swap);
	}
    	break;
    case dtkComposerTransmitter::Reference:
        return source;
        break;
    case dtkComposerTransmitter::Copy:
        return copy(source, t.d->variant, t.d->swap);
    	break;
    default:
        return source;
    }
}

template <typename T> inline T *dtkComposerTransmitterHandler<T *>::constData(dtkComposerTransmitter& t)
{
    return t.variant().value<T *>();
}

template <typename T> inline T *dtkComposerTransmitterHandler<T *>::copy(T *source, QVariant& target, QVariant& swap)
{
    if (!source)
        return source;

    T *dest = target.value<T *>();
    if (!dest) {
        dest = dtkMetaType::clone(source);
        target.setValue(dest);
    } else {
        if (dest != source) {
            dtkMetaType::copy(source, dest);
        } else {
            dest = swap.value<T *>();
            if (!dest) {
                dest = dtkMetaType::clone(source);
                if (!dest) {
                    dtkWarn() << Q_FUNC_INFO << "Copy failed. nullptr is returned.";
                }
            } else {
                dtkMetaType::copy(source, dest);
                if (!dest) {
                    dtkWarn() << Q_FUNC_INFO << "Copy failed. nullptr is returned.";
                }
            }
            swap.setValue(source);
            target.setValue(dest);
        }
    }

    return dest;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandlerVariant implementation
// /////////////////////////////////////////////////////////////////

inline QVariant dtkComposerTransmitterHandlerVariant::data(dtkComposerTransmitter& t)
{
    QVariant source = t.variant();

    switch(t.dataTransmission()) {
    case dtkComposerTransmitter::AutoCopy:
	if (!t.enableCopy()) {
	    return source;
	} else {
            copy(source, t.d->variant);
            return t.d->variant;
	}
    	break;
    case dtkComposerTransmitter::Reference:
        return source;
        break;
    case dtkComposerTransmitter::Copy:
        copy(source, t.d->variant);
        return t.d->variant;
    	break;
    default:
        return source;
    }
}

inline bool dtkComposerTransmitterHandlerVariant::containSamePointer(const QVariant& v0, const QVariant& v1)
{
    if (QString(v0.typeName()).endsWith("*") && QString(v1.typeName()).endsWith("*")) {

        const void *v0_ptr = *static_cast<const void * const *>(v0.data());
        const void *v1_ptr = *static_cast<const void * const *>(v1.data());

        return (v0_ptr && v1_ptr && (v0_ptr == v1_ptr));
    }

    return false;
}

inline void dtkComposerTransmitterHandlerVariant::clearPointer(QVariant& v)
{
    void *ptr = *static_cast<void **>(v.data());
    QString type_name = QString(v.typeName());
    type_name.chop(1);
    int type_id = QMetaType::type(qPrintable(type_name));
    QMetaType::destroy(type_id, ptr);
    v.clear();
}

inline void dtkComposerTransmitterHandlerVariant::copy(const QVariant& source, QVariant& target)
{
    if (!source.isValid()) {
        target = source;
        return;
    }

    if (containSamePointer(source, target))
        clearPointer(target);

    target = dtkMetaType::cloneContent(source);
}


//
// dtkComposerTransmitterHandler.tpp ends here
