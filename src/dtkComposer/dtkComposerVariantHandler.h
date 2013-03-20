/* dtkComposerVariantHandler.h ---
 * 
 * Author: Julien Wintz
 * Created: Wed Mar 20 12:58:00 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Mar 20 13:06:58 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Change Log:
 * 
 */

#ifndef DTKVARIANTHANDLER_H
#define DTKVARIANTHANDLER_H

#include "dtkComposerVariant.h"
#include "dtkComposerType.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerVariantHandler interface
// /////////////////////////////////////////////////////////////////

template<typename T, bool U> class dtkComposerVariantHandler
{
public:
    static inline bool             canConvert(const dtkComposerVariant& variant);
    static inline bool     canConvertToObject(const dtkComposerVariant& variant);
    static inline bool       canConvertToData(const dtkComposerVariant& variant);
    static inline bool canConvertToMatrixReal(const dtkComposerVariant& variant);

public:
    static inline void      setValue(dtkComposerVariant& variant, const T& value);
    static inline void     setObject(dtkComposerVariant& variant, const T& value);
    static inline void       setData(dtkComposerVariant& variant, const T& value);
    static inline void setMatrixReal(dtkComposerVariant& variant, const T& value);

public:
    static inline T           value(const dtkComposerVariant& variant);
    static inline T     objectValue(const dtkComposerVariant& variant);
    static inline T       dataValue(const dtkComposerVariant& variant);
    static inline T matrixRealValue(const dtkComposerVariant& variant);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerVariantHandler specialized interface
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkComposerVariantHandler<T, true>
{
public:
    static inline bool             canConvert(const dtkComposerVariant& variant);
    static inline bool     canConvertToObject(const dtkComposerVariant& variant);
    static inline bool       canConvertToData(const dtkComposerVariant& variant);
    static inline bool canConvertToMatrixReal(const dtkComposerVariant& variant);

public:
    static inline void      setValue(dtkComposerVariant& variant, const T& value);
    static inline void     setObject(dtkComposerVariant& variant, const T& value);
    static inline void       setData(dtkComposerVariant& variant, const T& value);
    static inline void setMatrixReal(dtkComposerVariant& variant, const T& value);

public:
    static inline T           value(const dtkComposerVariant& variant);
    static inline T     objectValue(const dtkComposerVariant& variant);
    static inline T       dataValue(const dtkComposerVariant& variant);
    static inline T matrixRealValue(const dtkComposerVariant& variant);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerVariantHandler implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerVariantHandler.tpp"

#endif
