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

#include "dtkComposerMetatype.h"
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
        if (d->container)
            delete d->container;
    }
    d->container = NULL;
}

void dtkComposerTransmitterVariant::setData(dtkAbstractContainerWrapper *data)
{
    d->container = data;
    d->variant.setValue(d->container);
}

void dtkComposerTransmitterVariant::setDataFrom(dtkComposerTransmitterVariant *source)
{
    d->variant = source->variant();
    d->data_type = &(source->dataType());

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
}

void dtkComposerTransmitterVariant::setDataFrom(QByteArray& array)
{
    QDataStream stream(&array, QIODevice::ReadOnly);

    qlonglong header_length;
    qint64 data_type;
    QString data_identifier;
    QByteArray data_array;

    stream >> data_type >> data_identifier;
    header_length = sizeof(qint64) + sizeof(qint32) + 2 * data_identifier.size();
    data_array = QByteArray::fromRawData(array.data() + header_length, array.size() - header_length);

    dtkDebug() << "dtkComposerTransmitterVariant::" << Q_FUNC_INFO << "Try to set data of type " << data_type << data_identifier;

    if (data_type < QMetaType::User) {
        d->variant.setValue(data_array);
        d->variant.convert(QVariant::Type(data_type));

    } else {

        if (data_type == dtkMatrixReal_Id) {
                
            dtkMatrixReal *data = d->variant.value<dtkMatrixReal*>();
            if (!data) {
                data = dtkMatrix<double>::create(data_identifier);
                d->variant.setValue(data);
            }
                
            data->deserialize(data_array);

            if (!data) {
                dtkError() << "dtkComposerTransmitterVariant::" << Q_FUNC_INFO << "Deserialization failed for" << data_identifier;
                return;
            }

        }

        else if (data_type == dtkMatrixInteger_Id) {
                
            dtkMatrixInteger *data = d->variant.value<dtkMatrixInteger*>();
            if (!data) {
                data = dtkMatrix<qlonglong>::create(data_identifier);
                d->variant.setValue(data);
            }
                
            data->deserialize(data_array);

            if (!data) {
                dtkError() << "dtkComposerTransmitterVariant::" << Q_FUNC_INFO << "Deserialization failed for" << data_identifier;
                return;
            }

        } else if (data_type == dtkAbstractData_Id) {

            dtkAbstractData *data = d->variant.toAbstractData();
            if (!data) {
                data = dtkAbstractDataFactory::instance()->create(data_identifier);
                d->variant.setValue(data);
            }
                
            data->deserialize(data_array);

            if (!data) {
                dtkError() << "dtkComposerTransmitterVariant::" << Q_FUNC_INFO << "Deserialization failed for" << data_identifier;
                return;
            }

        }
#if defined(DTK_HAVE_PLOT)
        else if (data_type == dtkPlotCurve_Id) {

            dtkPlotCurve *curve = d->variant.value<dtkPlotCurve*>();
            if (!curve) {
                curve = new dtkPlotCurve;
                d->variant.setValue(curve);
            }
            QDataStream curve_stream(&data_array, QIODevice::ReadOnly);
            qlonglong size_curve;
            curve_stream >> size_curve;

            QColor c;
            curve_stream >> c;
            curve->setColor(c);

            QPointF p;
            for (int i = 0; i < size_curve; ++i) {
                curve_stream >> p;
                curve->append(p);
            }

        } 
#endif
        else {
            dtkError() << "dtkComposerTransmitterVariant::" << Q_FUNC_INFO << "Deserialization not handled for" << data_identifier;
            return;
        }
    }
}

QByteArray dtkComposerTransmitterVariant::dataToByteArray(void)
{
    QByteArray array = this->dataHeader();

    dtkComposerVariant v = this->variant();

    qint64 type = dtkComposerTypes->value(v.userType(), v.userType());

    if (type < dtkPlotCurve_Id) {

        array += v.toByteArray();

    } 
#if defined(DTK_HAVE_PLOT)
    else if (type == dtkPlotCurve_Id) {
        QDataStream stream(&array, QIODevice::WriteOnly);
        dtkPlotCurve *curve = v.value<dtkPlotCurve*>();
        
        QVector<QPointF> curve_data = curve->data();
        stream << (qlonglong)curve_data.size();
        stream << curve->color();
        foreach(QPointF p, curve_data)
            stream << p;
    }
#endif

    return array;
}

dtkComposerVariant& dtkComposerTransmitterVariant::variant(void)
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

const dtkComposerType& dtkComposerTransmitterVariant::dataType(void)
{
    if (e->twinned)
        return *d->data_type;

    if (e->active_variant) 
        return e->active_variant->dataType();

    if (e->active_emitter)
        return e->active_emitter->dataType();

    return *d->data_type;
}

QString dtkComposerTransmitterVariant::dataIdentifier(void)
{
    if (e->twinned)
        return d->variant.identifier();

    if (e->active_variant)
        return e->active_variant->variant().identifier();

    if (e->active_emitter)
        return e->active_emitter->variant().identifier();

    return d->variant.identifier();    
}

QString dtkComposerTransmitterVariant::dataDescription(void)
{
    if (e->twinned)
        return d->variant.description();

    if (e->active_variant)
        return e->active_variant->variant().description();

    if (e->active_emitter)
        return e->active_emitter->variant().description();

    return d->variant.description();
}

QStringList dtkComposerTransmitterVariant::allDataIdentifier(void)
{
    QStringList list;

    if (e->twinned) {

        list << this->dataIdentifier();

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
    if (e->twinned)
        return (d->receivers.count() > 1);

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

void dtkComposerTransmitterVariant::setDataTypes(const QVector<const dtkComposerType*>& data_types)
{
    e->data_types = data_types;
}

QVector<const dtkComposerType*> dtkComposerTransmitterVariant::dataTypes(void)
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
        dtkComposerTransmitterVariant *v = static_cast<dtkComposerTransmitterVariant *>(transmitter); 

        if (!e->variants.contains(v)) {

            if (e->data_types.isEmpty() || v->dataTypes().isEmpty()) {
                e->variants << v;
                e->active_variant = v;
                e->active_emitter = NULL;
                v->appendReceiver(this);
                return true;

            } else {
                foreach(const dtkComposerType *t, v->dataTypes()) {
                    foreach(const dtkComposerType *tt, e->data_types) {
                        if (*tt == *t) {
                            e->variants << v;
                            e->active_variant = v;
                            e->active_emitter = NULL;
                            v->appendReceiver(this);
                            return true;
                        }
                    }
                }
            }
        }

    } else if (!e->emitters.contains(transmitter)) {
        if (e->data_types.isEmpty()) {
            e->emitters << transmitter;
            e->active_emitter = transmitter;
            e->active_variant = NULL;
            transmitter->appendReceiver(this);
            return true;

        } else {
            const dtkComposerType *t = &(transmitter->dataType());
            foreach(const dtkComposerType *type, e->data_types) {
                if (*t == *type) {
                    e->emitters << transmitter;
                    e->active_emitter = transmitter;
                    e->active_variant = NULL;
                    transmitter->appendReceiver(this);
                    return true;                    
                }
            }
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
