/* dtkComposerTransmitterVariant.cpp --- 
 * 
 * Author: Thibaud Kloczko, Inria.
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

    e->data_owner = false;
}

dtkComposerTransmitterVariant::~dtkComposerTransmitterVariant(void)
{
    delete e;

    e = NULL;
}

void dtkComposerTransmitterVariant::clearData(void)
{
    d->variant.clear();
    e->m_variant.clear(); // cannot delete the pointer that it contains ! Source of memory leak !

    if (e->data_owner) {
        if (d->container) {
            delete d->container;

        } else if (d->object) {
            delete d->object;

        } else if (d->matrix) {
            delete d->matrix;
        }
    }

    d->object = NULL;
    d->container = NULL;
    d->matrix = NULL;
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
    d->object = NULL;
    d->matrix = NULL;
}

void dtkComposerTransmitterVariant::setData(dtkAbstractContainerWrapper *data)
{
    d->data_type = qMetaTypeId<dtkAbstractContainerWrapper>(reinterpret_cast<dtkAbstractContainerWrapper*>(0));
    d->container = data;
    d->variant.setValue(d->container);
    d->object = data;
    d->matrix = NULL;
}

void dtkComposerTransmitterVariant::setDataFrom(dtkComposerTransmitterVariant *source)
{
    d->data_type = source->dataType();
    d->variant = source->variant();

    if (this != source)
        e->data_owner = false;

    dtkAbstractContainerWrapper *container = source->container();
    if (e->data_owner) {
        if (d->container && (d->container != container)) {
            delete d->container;
            d->container = NULL;
        }
    }
    d->container = container;

    d->object = source->object();
    d->matrix = source->matrix();
}

void dtkComposerTransmitterVariant::setDataFrom(QByteArray& array)
{
    this->setVariantFrom(array, true);
}

QVariant dtkComposerTransmitterVariant::setVariantFrom(QByteArray& array, bool self)
{

    qint64 data_type;
    QDataStream stream(&array, QIODevice::ReadOnly);
    qlonglong header_length=sizeof(data_type);
    stream >> data_type;

    dtkDebug() << DTK_PRETTY_FUNCTION << "Try to set data from " << data_type;

    switch(data_type) {
    case QMetaType::Double: {
        if (self) {
            stream >> e->value_r;
            this->setData<double>(&e->value_r);
        } else {
            double r;
            stream >> r;
            return QVariant::fromValue(&r);
        }
        break;
    }
    case QMetaType::LongLong: {
        if (self) {
            stream >> e->value_i;
            this->setData<qlonglong>(&e->value_i);
        } else {
            qlonglong i;
            stream >> i;
            QVariant::fromValue(&i);
        }
        break;
    }
    case QMetaType::QString: {
        if (self) {
            e->value_s = QString(QByteArray::fromRawData(array.data()+header_length,array.size()-header_length));
            this->setData<QString>(&e->value_s);
        } else {
            QString s = QString(QByteArray::fromRawData(array.data()+header_length,array.size()-header_length));
            QVariant::fromValue(&s);
        }
        break;
    }
    default:

        if (self)
            e->data_owner = true;

        if (data_type == e->dtkVector3DReal_Id) {

            if (self) {
                if (!d->matrix)
                    d->matrix = new dtkVector3D<double>();
                d->matrix->deserialize(QByteArray::fromRawData(array.data()+header_length,array.size()-header_length));
                this->setData<dtkVector3DReal>(reinterpret_cast<dtkVector3DReal*>(d->matrix));
            } else {
                dtkVector3D<double> *v = new dtkVector3D<double>();
                v->deserialize(QByteArray::fromRawData(array.data()+header_length,array.size()-header_length));
                return QVariant::fromValue(v);
            }

        } else if (data_type == e->dtkVectorReal_Id) {

            if (self) {
                if (!d->matrix)
                    d->matrix = new dtkVector<double>();
                d->matrix->deserialize(QByteArray::fromRawData(array.data()+header_length,array.size()-header_length));
                this->setData<dtkVectorReal>(reinterpret_cast<dtkVectorReal*>(d->matrix));
            } else {
                dtkVector<double> *v = new dtkVector<double>();
                v->deserialize(QByteArray::fromRawData(array.data()+header_length,array.size()-header_length));
                return QVariant::fromValue(v);
            }

        } else if (data_type == e->dtkQuaternionReal_Id) {

            if (self) {
                if (!d->matrix)
                    d->matrix = new dtkQuaternion<double>();
                d->matrix->deserialize(QByteArray::fromRawData(array.data()+header_length,array.size()-header_length));
                this->setData<dtkQuaternionReal>(reinterpret_cast<dtkQuaternionReal*>(d->matrix));
            } else {
                dtkQuaternion<double> *v = new dtkQuaternion<double>();
                v->deserialize(QByteArray::fromRawData(array.data()+header_length,array.size()-header_length));
                return QVariant::fromValue(v);
            }

        } else if (data_type == e->dtkMatrixReal_Id) {

            if (self) {
                if (!d->matrix)
                    d->matrix = new dtkMatrix<double>();
                d->matrix->deserialize(QByteArray::fromRawData(array.data()+header_length,array.size()-header_length));
                this->setData<dtkMatrixReal>(d->matrix);
            } else {
                dtkMatrixReal *m = new dtkMatrixReal();
                m->deserialize(QByteArray::fromRawData(array.data()+header_length,array.size()-header_length));
                return QVariant::fromValue(m);
            }

        } else if (data_type == e->dtkMatrixSquareReal_Id) {

            if (self) {
                if (!d->matrix)
                d->matrix = new dtkMatrixSquareReal();
                d->matrix->deserialize(QByteArray::fromRawData(array.data()+header_length,array.size()-header_length));
                this->setData<dtkMatrixSquareReal>(reinterpret_cast<dtkMatrixSquareReal*>(d->matrix));
            } else {
                dtkMatrixSquareReal *m = new dtkMatrixSquareReal();
                m->deserialize(QByteArray::fromRawData(array.data()+header_length,array.size()-header_length));
                return QVariant::fromValue(m);
            }

#if defined(DTK_HAVE_PLOT)
        } else if (data_type == e->dtkPlotCurve_Id) {

            qlonglong size_curve;
            stream >> size_curve;
            QPointF p;
            QColor c;
            dtkPlotCurve * curve;
            stream >> c;
            if (self) {
                e->curve.clear();
                e->curve.setColor(c);
            } else {
                curve = new dtkPlotCurve;
                curve->setColor(c);
            }
            for (int i = 0; i < size_curve; ++i) {
                stream >> p;
                if (self)
                    e->curve.append(p);
                else
                    curve->append(p);
            }
            if (self)
                this->setData<dtkPlotCurve>(&e->curve);
            else
                return QVariant::fromValue(curve);
#endif
        } else if (data_type == e->dtkAbstractData_Id) {

            QString typeName ;
            stream >> typeName;
            dtkTrace() << "type name and size:" << typeName << array.size() ;

            header_length=sizeof(data_type)+sizeof(int)+2*typeName.size();

            if (array.size() >  header_length) {

                if (!d->object)
                    d->object = dtkAbstractDataFactory::instance()->create(typeName);

                if (!d->object) {
                    dtkError() << "Unable to create data of type" << typeName;
                    return QVariant();
                }

                if (!(reinterpret_cast<dtkAbstractData*>(d->object))->deserialize(QByteArray::fromRawData(array.data()+header_length,array.size()-header_length))) {
                    dtkError() << "Deserialization failed for type" << typeName;

                } else {
                    dtkDebug() << "set dtkAbstractData in transmitter, size is" << array.size() << typeName;;
                    this->setData<dtkAbstractData>(reinterpret_cast<dtkAbstractData*>(d->object));
                }
            } else {
                dtkWarn() << "No data in byte array, can't create " << typeName;
            }
        } else if (data_type == e->dtkAbstractContainer_Id) {
            qlonglong count;
            stream >> count;
            dtkDebug() << "need to deserialize container of size " << count;
            qlonglong position = sizeof(qlonglong) *2;
            dtkDebug() << "position is  " << position;

            dtkContainerVector<QVariant> *c_vector = new dtkContainerVector<QVariant>();
            dtkAbstractContainerWrapper *c = new dtkContainerVectorWrapper<QVariant>(c_vector);
            for (qlonglong i = 0; i < count; ++i) {
                qlonglong size;
                stream >> size;
                position += sizeof(size);
                dtkDebug() << "item size is " << size << "position is"<< position;
                QByteArray b = array.mid(position, size);
                dtkDebug() << "setting variant from byte array";
                QVariant variant = this->setVariantFrom(b, false);
                position += size;
                dtkDebug() << "append data";
                c->append(variant);
                dtkDebug() << "skip";
                stream.skipRawData(size);

            }
            dtkDebug() << "set container";
            this->setData(c);
            return QVariant();

        } else {

            e->data_owner = false;
            dtkError() << "Deserialization not handled for type" << data_type;
        }
    }
}

QByteArray dtkComposerTransmitterVariant::dataToByteArray(void)
{
    return variantToByteArray( QVariant(), true);
}

QByteArray dtkComposerTransmitterVariant::variantToByteArray(QVariant v, bool self)
{
    qint64 data_type = (self) ? this->dataType() : v.userType();

    QByteArray array = QByteArray();
    QByteArray *tmp_array  = NULL;

    QDataStream stream(&array, QIODevice::WriteOnly);

    switch(data_type) {
    case QMetaType::Double: {
        double data = (self) ? *this->data<double>() : v.value<double>();
        stream << data_type;
        stream << data;
        break;
    }
    case QMetaType::LongLong: {
        qlonglong data = (self) ? *this->data<qlonglong>() : v.value<qlonglong>();
        stream << data_type;
        stream << data;
        break;
    }
    case QMetaType::QString: {
        stream << data_type;
        array.append((self) ? this->data<QString>()->toAscii() : v.value<QString>().toAscii());
        break;
    }
    default:
        dtkAbstractObject *o = this->object();
        if (self && o != NULL) {
            if (dtkAbstractData *data = qobject_cast<dtkAbstractData*>(o)) {
                if (dtkAbstractContainerWrapper *container= qobject_cast<dtkAbstractContainerWrapper*>(o)) {
                    dtkDebug() <<"need to serialize container";
                    stream << e->dtkAbstractContainer_Id;
                    qlonglong count = container->count();
                    stream << count;
                    for(qlonglong i = 0; i < count; ++i) {
                        QVariant q = container->at(i);
                        QByteArray b = this->variantToByteArray(q, false);
                        qlonglong  b_size = b.size();
                        dtkDebug() <<" add item of size " << b_size << "for container";
                        stream << b_size;
                        array.append(b);
                        stream.skipRawData(b_size);
                    }
                } else if (QByteArray *data_array = data->serialize()) {
                    stream << e->dtkAbstractData_Id;
                    stream << this->dataIdentifier();
                    array.append(*data_array);
                } else {
                    dtkError() <<"serialization failed for type" << this->dataIdentifier();
                }
            }
        } else if (!self && data_type == qMetaTypeId<dtkAbstractData *>()) {
            dtkWarn() <<"dtkAbstractData in QVariant ... TODO" ;
        } else if (data_type == qMetaTypeId<dtkVector3DReal>() || data_type == qMetaTypeId<dtkVector3DReal*>() ) {

            stream << e->dtkVector3DReal_Id;
            tmp_array =  (self) ? this->data<dtkVector3DReal>()->serialize() : v.value<dtkVector3DReal*>()->serialize();

        } else if (data_type == qMetaTypeId<dtkVectorReal>() || data_type == qMetaTypeId<dtkVectorReal*>()) {

            stream << e->dtkVectorReal_Id;
            tmp_array =  (self) ? this->data<dtkVectorReal>()->serialize()  : v.value<dtkVectorReal*>()->serialize();;

        } else if (data_type == qMetaTypeId<dtkVectorInteger>() || data_type == qMetaTypeId<dtkVectorInteger*>()) {

            stream << e->dtkVectorInteger_Id;
            tmp_array =  (self) ? this->data<dtkVectorInteger>()->serialize() : v.value<dtkVectorInteger*>()->serialize();

        } else if (data_type == qMetaTypeId<dtkQuaternionReal>() || data_type == qMetaTypeId<dtkQuaternionReal*>()) {

            stream << e->dtkQuaternionReal_Id;
            tmp_array =  (self) ? this->data<dtkQuaternionReal>()->serialize() : v.value<dtkQuaternionReal*>()->serialize();

        } else if (data_type == qMetaTypeId<dtkMatrixReal>() || data_type == qMetaTypeId<dtkMatrixReal*>()) {

            stream << e->dtkMatrixReal_Id;
            tmp_array =  (self) ? this->data<dtkMatrixReal>()->serialize() : v.value<dtkMatrixReal*>()->serialize();

        } else if (data_type == qMetaTypeId<dtkMatrixSquareReal>() || data_type == qMetaTypeId<dtkMatrixSquareReal*>()) {

            stream << e->dtkMatrixSquareReal_Id;
            tmp_array =  (self) ? this->data<dtkMatrixSquareReal>()->serialize() : v.value<dtkMatrixSquareReal*>()->serialize();

#if defined(DTK_HAVE_PLOT)
        } else if (data_type == qMetaTypeId<dtkPlotCurve>() || data_type == qMetaTypeId<dtkPlotCurve*>() ) {
            stream << e->dtkPlotCurve_Id;
            dtkPlotCurve *curve = (self) ? this->data<dtkPlotCurve>() : v.value<dtkPlotCurve *>() ;
            QVector<QPointF> curve_data = curve->data();
            stream << (qlonglong)curve_data.size();
            stream << curve->color();
            foreach(QPointF p, curve_data)
                stream << p;
#endif
        } else {
            dtkWarn() << "Unable to serialize the data into QByteArray." << data_type ;
            data_type = 0;
            stream << data_type;
        }
    }

    if (tmp_array) {
        array.append(*tmp_array);
        delete tmp_array;
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

const dtkAbstractContainerWrapper *dtkComposerTransmitterVariant::constContainer(void)
{
    if (this->dataTransmission() != dtkComposerTransmitter::Copy) {
        return this->containerFromEmitter();

    } else {
        dtkAbstractContainerWrapper *container = this->containerFromEmitter();
        if (!container)
            return NULL;
        return container->clone();
    }
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

dtkMatrix<double> *dtkComposerTransmitterVariant::matrix(void)
{
    if (e->twinned)
        return d->matrix;

    if (e->active_variant)
        return e->active_variant->matrix();

    if (e->active_emitter)
        return e->active_emitter->matrix();

    return d->matrix;
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

    if (QString *s = this->data<QString>())
        return *s;

    qint64 data_type = this->dataType();

    if (data_type == qMetaTypeId<dtkVector3DReal>(0)) {

        return this->data<dtkVector3DReal>()->description();

    } else if (data_type == qMetaTypeId<dtkVectorReal>(0)) {

        return this->data<dtkVectorReal>()->description();

    } else if (data_type == qMetaTypeId<dtkQuaternionReal>(0)) {

        return this->data<dtkQuaternionReal>()->description();

    } else if (data_type == qMetaTypeId<dtkMatrixReal>(0)) {

        return this->data<dtkMatrixReal>()->description();

    } else if (data_type == qMetaTypeId<dtkMatrixSquareReal>(0)) {

        return this->data<dtkMatrixSquareReal>()->description();

#if defined(DTK_HAVE_PLOT)
    } else if (data_type == qMetaTypeId<dtkPlotCurve>(0)) {

        return this->data<dtkPlotCurve>()->description();
#endif
    } else {
        QString address;
        QTextStream addressStream (&address);
        addressStream << (d->variant.value<void*>());

        return address;

    }

    return QString();
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

        list << this->dataDescription();

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
            return false;
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
