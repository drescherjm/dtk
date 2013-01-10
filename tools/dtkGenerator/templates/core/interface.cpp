/* %1.cpp ---
 *
 * Author: %Author%
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "%1.h"
#include "%1_p.h"

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// %1 implementation
// /////////////////////////////////////////////////////////////////

%1::%1(void) : %3(*new %1Private(this), 0)
{
    // DTK_D(%1);
}

%1::%1(const %1& other) : %3(*new %1Private(*other.d_func()), other)
{

}

%1::~%1(void)
{

}

//! Returns a new %1 that is a copy of this.
/*!
 *  This method can be overloaded through the hierarchy enabling a
 *  deep copy of this. Note that, using covariance of returned type,
 *  the returned argument can be of the more derived type.
 *
 *  Example:
 *  \code
 *  class xyzData : public %1
 *  {
 *    ...
 *    xyzData *clone(void); // Covariant returned argument
 *    ...
 *  };
 *
 *  xyzData *xyzData::clone(void)
 *  {
 *     return new xyzData(*this);
 *  }
 *  \endcode
 */
%1 *%1::clone(void)
{
    return new %1(*this);
}

%1& %1::operator = (const %1& other)
{
    this->copy(other);

    return (*this);
}

//! Enables to make a deep copy of the attributes through the class
//! hierarchy.
/*!
 *  This method is called by the assignement operator which delegates
 *  the copy process. When re-implementing this method into a derived
 *  class of %1, one must called first the copy method
 *  of the parent to ensure that all the attributes are really copied.
 *
 *  Nevertheless, some caution must be taken to avoid slicing problem
 *  as shown in the following example.
 *
 *  Example:
 *  \code
 *  class xyzData : public %1
 *  {
 *    ...
 *    void copy(const dtkAbstract%2& other);
 *    ...
 *  };
 *
 *  void xyzData::copy(const dtkAbstract%2& other)
 *  {
 *     // copy of the parent attributes
 *     %1::copy(other);
 *
 *     // copy of the xyzData attributes
 *     if (other.identifier() == this->identifier()) {
 *        // cast other into xyzData and do the copy
 *     } else {
 *        dtkWarn() << "other is not of same type than this, slicing is occuring.";
 *     }
 *  }
 *  \endcode
 */
void %1::copy(const dtkAbstractObject& other)
{
    dtkAbstract%2::copy(other);

    if (this->identifier() == other.identifier()) {

        const %1& process = reinterpret_cast<const %1&>(other);

        DTK_D(%1);

    } else {
        dtkWarn() << "Other is not of same type than this, slicing is occuring.";
    }
}

//! Returns Class name.
/*!
 *
 */
QString %1::identifier(void) const
{
    return "%1";
}
