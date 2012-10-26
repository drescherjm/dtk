/* dtkVariant.h --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: 2012 Thu Oct 25 12:42:49 (+0200)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVARIANT_H
#define DTKVARIANT_H

#include "dtkCoreExport.h"
#include "dtkGlobal.h"
#include <dtkContainer/dtkAbstractContainerWrapper.h>

#include <QVariant>

class dtkAbstractObject;
class dtkAbstractData;
class dtkAbstractProcess;
class dtkAbstractView;

template <typename T> class dtkMatrix;
template <typename T> class dtkVector;
template <typename T> class dtkVector3D;
template <typename T> class dtkQuaternion;



// /////////////////////////////////////////////////////////////////
// dtkVariant interface
// /////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkVariant : public QVariant
{
public:
     dtkVariant(void);

     /* dtkVariant(const      bool *value); */
     /* dtkVariant(const qlonglong *value); */
     /* dtkVariant(const    double *value); */
     /* dtkVariant(const   QString *value); */

     /* dtkVariant(const  dtkAbstractObject *value); */
     /* dtkVariant(const    dtkAbstractData *value); */
     /* dtkVariant(const dtkAbstractProcess *value); */
     /* dtkVariant(const    dtkAbstractView *value); */

     /* dtkVariant(const        dtkMatrix<double> *value); */
     /* dtkVariant(const dtkMatrixSquared<double> *value); */
     /* dtkVariant(const        dtkVector<double> *value); */
     /* dtkVariant(const      dtkVector3D<double> *value); */
     /* dtkVariant(const    dtkQuaternion<double> *value); */

     /* dtkVariant(const dtkAbstractContainerWrapper *value); */

     dtkVariant(const dtkVariant& other);
    ~dtkVariant(void);

/* public: */
/*     dtkVariant& operator = (const dtkVariant& other); */

/* public: */
/*     bool operator == (const dtkVariant& other); */
/*     bool operator != (const dtkVariant& other); */

/* public: */
/*     QString  identifier(void) const; */
/*     QString description(void) const; */

/* public: */
/*     void clear(void); */

/* public: */
/*     bool isValid(void) const; */
/*     bool  isNull(void) const; */

/*     bool  isAbstractObject(void) const; */
/*     bool    isAbstractData(void) const; */
/*     bool isAbstractProcess(void) const; */
/*     bool    isAbstractView(void) const; */

/* public: */
/*     bool          *toBoolStar(void) const; */
/*     qlonglong *toLongLongStar(void) const; */
/*     double        *toRealStar(void) const; */
/*     QString     *toStringStar(void) const; */

/*     QByteArray toByteArray(void) const; */
/*     QString       toString(void) const; */

/*     dtkAbstractObject   *toAbstractObject(void) const; */
/*     dtkAbstractData       *toAbstractData(void) const; */
/*     dtkAbstractProcess *toAbstractProcess(void) const; */
/*     dtkAbstractView       *toAbstractView(void) const; */

/*     dtkMatrix<double>              *toMatrixReal(void) const; */
/*     dtkMatrixSquared<double> *toMatrixSquaedReal(void) const; */
/*     dtkVector<double>                  *toVector(void) const; */
/*     dtkVector3D<double>          *toVector3DReal(void) const; */
/*     dtkQuaternion<double>      *toQuaternionReal(void) const; */

/*     dtkAbstractContainerWrapper *toAbstractContainer(void) const; */

public:
    template<typename T> void setValue(const T& value);

    template<typename T> T value(void) const;

private:
    //template<typename T, bool> void convertValue(const T& value);
    //template<typename T, typename B = bool> void convertValueObject(const T& value);

public:
    dtkAbstractObject *m_object;
    dtkMatrix<double> *m_matrix;
    dtkAbstractContainerWrapper *m_container;

private:
    bool      m_value_b;
    qlonglong m_value_i;
    qreal     m_value_r;
    QString   m_value_s;

public:
    template<typename T, bool> friend class dtkVariantConverter;
};

// /////////////////////////////////////////////////////////////////
// dtkVariantConverter interface
// /////////////////////////////////////////////////////////////////

template<typename T, bool> class dtkVariantConverter
{
public:
    static void fromObject(dtkVariant& variant, const T& value)
    {
        variant.QVariant::setValue(value);

        variant.m_object = NULL;
        variant.m_matrix = NULL;
        variant.m_container = NULL;
    }

    static void fromAbstractObject(dtkVariant& variant, const T& value)
    {
        variant.m_object = NULL;
        variant.m_container = NULL;
    }

    static void fromMatrixReal(dtkVariant& variant, const T& value)
    {
        variant.m_matrix = NULL;
    }

public:
    static T toObject(const dtkVariant& variant)
    {
        return variant.QVariant::value<T>();
    }

    static T toAbstractObject(const dtkVariant& variant)
    {
        return NULL;
    }

    static T toMatrixReal(const dtkVariant& variant)
    {
        return NULL;
    }
};

// /////////////////////////////////////////////////////////////////
// dtkVariantConverter interface
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkVariantConverter<T, true>
{
public:
    static void fromAbstractObject(dtkVariant& variant, const T& value)
    {
        variant.m_object = value;
        variant.m_container = dynamic_cast<dtkAbstractContainerWrapper*>(variant.m_object);

        variant.QVariant::setValue(variant.m_object);
    }

    static void fromMatrixReal(dtkVariant& variant, const T& value)
    {
        variant.m_matrix = value;

        variant.QVariant::setValue(variant.m_matrix);
    }

    static void fromObject(dtkVariant& variant, const T& value)
    {
        dtkVariantConverter<T, dtkTypeInfo<T>::dtkAbstractObjectPointer>::fromAbstractObject(variant, value);
        dtkVariantConverter<T, dtkTypeInfo<T>::dtkMatrixRealPointer>::fromMatrixReal(variant, value);
    }

public:
    static T toAbstractObject(const dtkVariant& variant)
    {
        return dynamic_cast<T>(variant.m_object);
    }

    static T toMatrixReal(const dtkVariant& variant)
    {
        return dynamic_cast<T>(variant.m_matrix);
    }

    static T toObject(const dtkVariant& variant)
    {
        if (dtkTypeInfo<T>::dtkAbstractObjectPointer)
            return dtkVariantConverter<T, dtkTypeInfo<T>::dtkAbstractObjectPointer>::toAbstractObject(variant);
        
        return dtkVariantConverter<T, dtkTypeInfo<T>::dtkMatrixRealPointer>::toMatrixReal(variant);
    }
};

// /////////////////////////////////////////////////////////////////
// dtkVariant implementation
// /////////////////////////////////////////////////////////////////

#include "dtkVariant.tpp"

#endif
