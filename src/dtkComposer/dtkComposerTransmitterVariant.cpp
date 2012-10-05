/* dtkComposerTransmitterVariant.cpp --- 
 * 
 * Author: tkloczko
 * Created: Sat Mar  3 17:51:22 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkConfig.h>

#include "dtkComposerTransmitter_p.h"
#include "dtkComposerTransmitterVariant.h"
#include "dtkComposerTransmitterVariant_p.h"

#include <dtkContainer>

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>

#if defined(DTK_BUILD_DISTRIBUTED)
#include <dtkDistributed/dtkDistributedMessage.h>
#endif

#include <dtkLog/dtkLog.h>

#include <dtkMath/dtkMath.h>

// /////////////////////////////////////////////////////////////////
// Template specializations for atomic types
// /////////////////////////////////////////////////////////////////

template <> bool *dtkComposerTransmitterVariant::data(void)
{
    QVariant& emitter_variant = this->variant();
    int emitter_type = emitter_variant.userType();

    if (emitter_type == e->metatypes[dtkComposerTransmitterVariantPrivate::BoolStar]) {
        e->value_b = *(emitter_variant.value<bool*>());

    } else if (emitter_type == e->metatypes[dtkComposerTransmitterVariantPrivate::LongLongStar]) {
    e->value_b = static_cast<bool>(*(emitter_variant.value<qlonglong*>()));

    } else if (emitter_type == e->metatypes[dtkComposerTransmitterVariantPrivate::RealStar]) {
        e->value_b = static_cast<bool>(*(emitter_variant.value<qreal*>()));

    } else if (emitter_type == e->metatypes[dtkComposerTransmitterVariantPrivate::StringStar]) {
        e->value_b = (emitter_variant.value<QString*>())->toLongLong();

    } else if (emitter_type <= QMetaType::Double && emitter_type != 0) {
        e->value_b = emitter_variant.value<bool>();

    } else if (emitter_type == QMetaType::QString) {
        e->value_b = emitter_variant.value<bool>();

    } else {
        if (emitter_variant.canConvert<bool>()) {
            e->value_b = emitter_variant.value<bool>();
        } else {
            e->value_b = 0.;
            return NULL;
        }
    }

    return &(e->value_b);
}

template <> qlonglong *dtkComposerTransmitterVariant::data(void)
{
    QVariant& emitter_variant = this->variant();
    int emitter_type = emitter_variant.userType();

    if (emitter_type == e->metatypes[dtkComposerTransmitterVariantPrivate::LongLongStar]) {
        e->value_i = *(emitter_variant.value<qlonglong*>());

    } else if (emitter_type == e->metatypes[dtkComposerTransmitterVariantPrivate::RealStar]) {
        e->value_i = static_cast<qlonglong>(*(emitter_variant.value<qreal*>()));

    } else if (emitter_type == e->metatypes[dtkComposerTransmitterVariantPrivate::StringStar]) {
        e->value_i = (emitter_variant.value<QString*>())->toLongLong();

    } else if (emitter_type == e->metatypes[dtkComposerTransmitterVariantPrivate::BoolStar]) {
        e->value_i = static_cast<qlonglong>(*(emitter_variant.value<bool*>()));

    } else if (emitter_type <= QMetaType::Double && emitter_type != 0) {
        e->value_i = emitter_variant.value<qlonglong>();

    } else if (emitter_type == QMetaType::QString) {
        e->value_i = emitter_variant.value<qlonglong>();

    } else {
        if (emitter_variant.canConvert<qlonglong>()) {
            e->value_i = emitter_variant.value<qlonglong>();
        } else {
            e->value_i = 0.;
            return NULL;
        }
    }

    return &(e->value_i);
}

template <> qreal *dtkComposerTransmitterVariant::data(void)
{
    QVariant& emitter_variant = this->variant();
    int emitter_type = emitter_variant.userType();

    if (emitter_type == e->metatypes[dtkComposerTransmitterVariantPrivate::RealStar]) {
        e->value_r = *(emitter_variant.value<qreal*>());

    } else if (emitter_type == e->metatypes[dtkComposerTransmitterVariantPrivate::LongLongStar]) {
        e->value_r = static_cast<qreal>(*(emitter_variant.value<qlonglong*>()));

    } else if (emitter_type == e->metatypes[dtkComposerTransmitterVariantPrivate::StringStar]) {
        e->value_r = (emitter_variant.value<QString*>())->toDouble();

    } else if (emitter_type == e->metatypes[dtkComposerTransmitterVariantPrivate::BoolStar]) {
        e->value_r = static_cast<qreal>(*(emitter_variant.value<bool*>()));

    } else if (emitter_type <= QMetaType::Double && emitter_type != 0) {
        e->value_r = emitter_variant.value<qreal>();

    } else if (emitter_type == QMetaType::QString) {
        e->value_r = emitter_variant.value<qreal>();

    } else {
        if (emitter_variant.canConvert<qreal>()) {
            e->value_r = emitter_variant.value<qreal>();
        } else {
            e->value_r = 0.;
            return NULL;
        }
    }

    return &(e->value_r);
}

template <> QString *dtkComposerTransmitterVariant::data(void)
{
    QVariant& emitter_variant = this->variant();
    int emitter_type = emitter_variant.userType();

    if (emitter_type == e->metatypes[dtkComposerTransmitterVariantPrivate::StringStar]) {
        e->value_s = *(emitter_variant.value<QString*>());

    } else if (emitter_type == e->metatypes[dtkComposerTransmitterVariantPrivate::RealStar]) {
        e->value_s.setNum(*(emitter_variant.value<qreal*>()), 'G', 16);

    } else if (emitter_type == e->metatypes[dtkComposerTransmitterVariantPrivate::LongLongStar]) {
        e->value_s.setNum(*(emitter_variant.value<qlonglong*>()));

    } else if (emitter_type == e->metatypes[dtkComposerTransmitterVariantPrivate::BoolStar]) {
        e->value_s = QString::number(static_cast<int>(*(emitter_variant.value<bool*>())));

    } else if (emitter_type == QMetaType::Double) {
        e->value_s.setNum(emitter_variant.value<qreal>(), 'G', 16);

    } else if (emitter_type < QMetaType::Double && emitter_type != 0) {
        e->value_s = emitter_variant.value<QString>();

    } else if (emitter_type == QMetaType::QString) {
        e->value_s = emitter_variant.value<QString>();

    } else {
        if (emitter_variant.canConvert<QString>()) {
            e->value_s = emitter_variant.value<QString>();
        } else {
            e->value_s = 0.;
            return NULL;
        }
    }

    return &(e->value_s);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariant implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitterVariant::dtkComposerTransmitterVariant(dtkComposerNode *parent) : dtkComposerTransmitter(parent), e(new dtkComposerTransmitterVariantPrivate)
{
    e->active_emitter = NULL;
    e->active_variant = NULL;

    e->twin = NULL;
    e->twinned = false;
    e->already_ask = false;

    e->m_variant.clear();
}

dtkComposerTransmitterVariant::~dtkComposerTransmitterVariant(void)
{
    delete e;

    e = NULL;
}

void dtkComposerTransmitterVariant::clearData(void)
{
    d->object = NULL;
    d->variant.clear();
    e->m_variant.clear();
    if (d->container) 
        delete d->container;
    d->container = NULL;
}

//! Puts \a data into the variant transmitter which then plays the
//! role of an emitter.
/*! 
 *  This methods resets the container of the transmiter. This is quite
 *  important because it enables to test whether the variant
 *  transmitter contains a container or not using isReset() method
 *  from the dtkAbstractContainerWrapper class.
 *  
 *  
 */
void dtkComposerTransmitterVariant::setData(const QVariant& data)
{
    d->data_type = data.userType();
    d->variant = data;
    if (d->container) {
        delete d->container;
        d->container = NULL;
    }
}

void dtkComposerTransmitterVariant::setData(dtkAbstractContainerWrapper *data)
{
    d->data_type = qMetaTypeId<dtkAbstractContainerWrapper>(reinterpret_cast<dtkAbstractContainerWrapper*>(0));
    d->container = data;
    d->variant.setValue(d->container);
    d->object = data;
}

void dtkComposerTransmitterVariant::setDataFrom(dtkComposerTransmitterVariant *source)
{
    d->data_type = source->dataType();
    d->variant = source->variant();

    dtkAbstractContainerWrapper *container = source->container();
    if (d->container != container) {
        delete d->container;
        d->container = container;
    }

    d->object = source->object();
}

void dtkComposerTransmitterVariant::setDataFrom(QByteArray& array)
{
    qint64 data_type;
    QDataStream stream(&array, QIODevice::ReadOnly);
    stream >> data_type;
    QString type = QString(QMetaType::typeName(data_type));

    dtkDebug() << DTK_PRETTY_FUNCTION << "Try to set data from " << type << data_type;

    switch(data_type) {
    case QMetaType::Double: {
        stream >> e->value_r;
        this->setData<double>(&e->value_r);
        break;
    }
    case QMetaType::LongLong: {
        stream >> e->value_i;
        this->setData<qlonglong>(&e->value_i);
        break;
    }
    case QMetaType::QString: {
        e->value_s = QString(array);
        this->setData<QString>(&e->value_s);
        break;
    }
    default:

        if (data_type == qMetaTypeId<dtkVector3DReal>(0)) {

            dtkVector3DReal *v = new dtkVector3D<qreal>();
            v->deserialize(array);
            this->setData<dtkVector3DReal>(v);

        } else if (data_type == qMetaTypeId<dtkVectorReal>(0)) {

            dtkVectorReal *v = new dtkVector<qreal>();
            v->deserialize(array);
            this->setData<dtkVectorReal>(v);

        } else if (data_type == qMetaTypeId<dtkQuaternionReal>(0)) {

            dtkQuaternionReal *q = new dtkQuaternion<qreal>();
            q->deserialize(array);
            this->setData<dtkQuaternionReal>(q);

        } else if (data_type == qMetaTypeId<dtkMatrixReal>(0)) {

            dtkMatrixReal *m = new dtkMatrix<qreal>();
            m->deserialize(array);
            this->setData<dtkMatrixReal>(m);

        } else if (data_type == qMetaTypeId<dtkMatrixSquareReal>(0)) {

            dtkMatrixSquareReal *m = new dtkMatrixSquareReal();
            m->deserialize(array);
            this->setData<dtkMatrixSquareReal>(m);

        } else if (data_type == qMetaTypeId<dtkAbstractData>()) {
            qint64 real_type;
            stream >> real_type;

            QString typeName = QString(QMetaType::typeName(real_type));
            qlonglong header_length=2*sizeof(real_type);
            if (array.size() >  header_length) {
                dtkAbstractData *data;
                array.remove(0,header_length);
                data = dtkAbstractDataFactory::instance()->create(typeName)->deserialize(array);
                if (!data) {
                    dtkError() << "Deserialization failed for type" << typeName;
                } else {
                    dtkDebug() << "set dtkAbstractData in transmitter, size is" << array.size() << typeName;;
                    this->setData<dtkAbstractData>(data);
                }
            } else {
                dtkWarn() << "No data in byte array, can't create " << typeName;
            }
        }
    }
}

QByteArray dtkComposerTransmitterVariant::dataToByteArray(void)
{
    qint64 data_type = this->dataType();

    QByteArray array = QByteArray();

    QDataStream stream(&array, QIODevice::WriteOnly);

    switch(data_type) {
    case QMetaType::Double: {
        double data = *this->data<double>();
        stream << data_type;
        stream << data;
        break;
    }
    case QMetaType::LongLong: {
        qlonglong data = *this->data<qlonglong>();
        stream << data_type;
        stream << data;
        break;
    }
    case QMetaType::QString: {
        stream << data_type;
        array.append(this->data<QString>()->toAscii());
        break;
    }
    default:
        if (dtkAbstractObject *o = this->object()) {
            if (dtkAbstractData *data = qobject_cast<dtkAbstractData*>(o)) {

                if (QByteArray *data_array = data->serialize()) {
                    if (data_type == qMetaTypeId<dtkAbstractData>()) {
                        stream << data_type;
                        const char* typeName = this->dataIdentifier().toAscii().data();
                        qint64 real_type = QMetaType::type( typeName );
                        stream << real_type;
                    } else {
                        qint64 parent_type = qMetaTypeId<dtkAbstractData>();
                        stream << parent_type;
                        stream << data_type;
                    }

                    array.append(*data_array);
                } else {
                    dtkError() <<"serialization failed";
                }
            }
        }

        else if (data_type == qMetaTypeId<dtkVector3DReal>(0)) {

            stream << data_type;
            array.append(*(this->data<dtkVector3DReal>()->serialize()));

        } else if (data_type == qMetaTypeId<dtkVectorReal>(0)) {

            stream << data_type;
            array.append(*(this->data<dtkVectorReal>()->serialize()));

        } else if (data_type == qMetaTypeId<dtkQuaternionReal>(0)) {

            stream << data_type;
            array.append(*(this->data<dtkQuaternionReal>()->serialize()));

        } else if (data_type == qMetaTypeId<dtkMatrixReal>(0)) {

            stream << data_type;
            array.append(*(this->data<dtkMatrixReal>()->serialize()));

        } else if (data_type == qMetaTypeId<dtkMatrixSquareReal>(0)) {

            stream << data_type;
            array.append(*(this->data<dtkMatrixSquareReal>()->serialize()));

        } else {
            dtkWarn() << "Unable to serialize the data into QByteArray.";
        }
    }

    return array;
}

QVariant& dtkComposerTransmitterVariant::variant(void)
{
    if (e->twinned)
        return d->variant;

    if (e->active_variant)
        return e->active_variant->variant();

    if (e->active_emitter)
        return e->active_emitter->variant();

    return d->variant;
}

dtkAbstractContainerWrapper *dtkComposerTransmitterVariant::containerFromEmitter(void)
{
    if (e->twinned)
        return d->container;

    if (e->active_variant)
        return e->active_variant->container();

    if (e->active_emitter)
        return e->active_emitter->container();

    return d->container;
}

dtkAbstractContainerWrapper *dtkComposerTransmitterVariant::container(void)
{
    dtkAbstractContainerWrapper *container = this->containerFromEmitter();

    if (!container)
        return NULL;

    switch(this->dataTransmission()) {
    case dtkComposerTransmitter::AutoCopy:
        if (this->enableCopy()) {
            if (!d->container)
                d->container = container->clone();
            else
                *(d->container) = *container;
            return d->container;
        } else {
            return container;
        }
        break;
    case dtkComposerTransmitter::Copy:
        return container->clone();
        break;
    case dtkComposerTransmitter::Reference:
        return container;
        break;
    default:
        break;
    };

    return NULL;
}

dtkAbstractObject *dtkComposerTransmitterVariant::object(void)
{
    if (e->twinned)
        return d->object;

    if (e->active_variant)
        return e->active_variant->object();

    if (e->active_emitter)
        return e->active_emitter->object();

    return d->object;
}

int dtkComposerTransmitterVariant::dataType(void)
{
    if (e->twinned)
        return d->data_type;

    if (e->active_variant) 
        return e->active_variant->dataType();

    if (e->active_emitter)
        return e->active_emitter->dataType();

    return d->data_type;
}

QString dtkComposerTransmitterVariant::dataIdentifier(void)
{
    if (dtkAbstractObject *o = this->object())
        return o->identifier();

    return QString(QMetaType::typeName(this->dataType()));
}

QString dtkComposerTransmitterVariant::dataDescription(void)
{
    if (dtkAbstractObject *o = this->object())
        return o->description();

    if(QString *s = this->data<QString>())
        return *s;

    QString address;
    QTextStream addressStream (&address);
    addressStream << (d->variant.value<void*>());

    return address;
}

QStringList dtkComposerTransmitterVariant::allDataIdentifier(void)
{
    QStringList list;

    if (e->twinned) {

        list << QString(QMetaType::typeName(d->data_type));

    } else {

        int count = e->emitters.count();

        for(int i = 0; i < count; ++i) {
            if (e->emitters.at(i)->active()) {
                list << e->emitters.at(i)->dataIdentifier();
            }
        }

        count = e->variants.count();

        for(int i = 0; i < count; ++i) {
            if (e->variants.at(i)->active()) {
                list << e->variants.at(i)->dataIdentifier();
            }
        }
    }

    return list;
}

QStringList dtkComposerTransmitterVariant::allDataDescription(void)
{
    QStringList list;

    if (e->twinned) {

        QString address;
        QTextStream addressStream (&address);
        addressStream << (d->variant.value<void*>());

        list << address;

    } else {

        int count = e->emitters.count();

        for(int i = 0; i < count; ++i) {
            if (e->emitters.at(i)->active()) {
                list << e->emitters.at(i)->dataDescription();
            }
        }

        count = e->variants.count();

        for(int i = 0; i < count; ++i) {
            if (e->variants.at(i)->active()) {
                list << e->variants.at(i)->dataDescription();
            }
        }
    }

    return list;
}

void dtkComposerTransmitterVariant::setActive(bool active)
{
    d->active = active;

    if (!active)
        return;

    foreach(dtkComposerTransmitter *receiver, d->receivers)
        receiver->activateEmitter(this);
}

//! 
/*! 
 *  
 */
void dtkComposerTransmitterVariant::activateEmitter(dtkComposerTransmitter *emitter)
{
    e->active_emitter = NULL;
    e->active_variant = NULL;

    foreach(dtkComposerTransmitter *em, e->emitters) {
        if (emitter == em) {
            e->active_emitter = emitter;
            break;
        }
    }
}

//! 
/*! 
 *  
 */
void dtkComposerTransmitterVariant::activateEmitter(dtkComposerTransmitterVariant *emitter)
{
    e->active_emitter = NULL;
    e->active_variant = NULL;
    
    foreach(dtkComposerTransmitterVariant *v, e->variants) {
        if (emitter == v) {
            e->active_variant = v;
            break;
        }
    }
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariant::enableCopy(void)
{
    if (e->twinned) {
        if (e->already_ask)
            return false;
        else {
            e->already_ask = true;
            if (d->receivers.count() > 1)
                return true;
        }
    }

    if (e->active_variant)
        return e->active_variant->enableCopy();

    if (e->active_emitter)
        return e->active_emitter->enableCopy();

    return (d->receivers.count() > 1);
}

void dtkComposerTransmitterVariant::reset(void)
{
    e->already_ask = false;
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariant::isEmpty(void) const
{
    if (e->emitters.isEmpty() && e->variants.isEmpty())
        return true;

    return false;
};

void dtkComposerTransmitterVariant::setTwin(dtkComposerTransmitterVariant *twin)
{
    e->twin = twin;
}

dtkComposerTransmitterVariant *dtkComposerTransmitterVariant::twin(void)
{
    return e->twin;
}
    
void dtkComposerTransmitterVariant::setTwinned(bool twinned)
{
    e->twinned = twinned;
}

//! Returns.
/*! 
 *  
 */
dtkComposerTransmitter::Kind dtkComposerTransmitterVariant::kind(void) const
{
    return dtkComposerTransmitter::Variant;
}

QString dtkComposerTransmitterVariant::kindName(void) const
{
    return "Variant";
}

void dtkComposerTransmitterVariant::setDataTypes(const QList<int>& data_types)
{
    e->data_types = data_types;
}

QList<int> dtkComposerTransmitterVariant::dataTypes(void)
{
    return e->data_types;
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariant::connect(dtkComposerTransmitter *transmitter)
{
    if (transmitter->kind() == Variant) {
        dtkComposerTransmitterVariant *v = dynamic_cast<dtkComposerTransmitterVariant *>(transmitter);        

        if (e->data_types.isEmpty() || v->dataTypes().isEmpty()) {
            if (!e->variants.contains(v)) {
                e->variants << v;
                e->active_variant = v;
                e->active_emitter = NULL;
                v->appendReceiver(this);
                return true;
            }
        } else {
            foreach(int t, v->dataTypes()) {
                if (!e->variants.contains(v) && e->data_types.contains(t)) {
                    e->variants << v;
                    e->active_variant = v;
                    e->active_emitter = NULL;
                    v->appendReceiver(this);
                    return true;
                }
            }
        }
    }

    if (e->data_types.isEmpty() || e->data_types.contains(transmitter->dataType())) {
        if (!e->emitters.contains(transmitter)) {
            e->emitters << transmitter;
            e->active_emitter = transmitter;
            e->active_variant = NULL;
            transmitter->appendReceiver(this);
            return true;
        }
    }

    return false;
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariant::disconnect(dtkComposerTransmitter *transmitter)
{
    transmitter->removeReceiver(this);

    bool ok = false;

    if (transmitter->kind() == Variant) {
        
        dtkComposerTransmitterVariant *v = static_cast<dtkComposerTransmitterVariant *>(transmitter);
        
        ok = e->variants.removeOne(v);

        if (v == e->active_variant) {

            e->active_variant = NULL;

            foreach(dtkComposerTransmitterVariant *var, e->variants) {
                if (var->active())
                    e->active_variant = var;
            }
            
            if (!e->active_variant) {
                foreach(dtkComposerTransmitter *em, e->emitters) {
                    if (em->active())
                        e->active_emitter = em;
                }
            }
        }
            
    } else {

        ok = e->emitters.removeOne(transmitter);

        if (transmitter == e->active_emitter) {

            e->active_emitter = NULL;

            foreach(dtkComposerTransmitter *em, e->emitters) {
                if (em->active())
                    e->active_emitter = em;
            }

            if (!e->active_emitter) {
                foreach(dtkComposerTransmitterVariant *var, e->variants) {
                    if (var->active())
                        e->active_variant = var;
                }
            }            

        }
    }    
    
    return ok ;
}

//! 
/*! 
 *  
 */
dtkComposerTransmitter::LinkMap dtkComposerTransmitterVariant::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    DTK_UNUSED(transmitter);

    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
}

//! 
/*! 
 *  
 */
dtkComposerTransmitter::LinkMap dtkComposerTransmitterVariant::rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    DTK_UNUSED(transmitter);

    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
}
