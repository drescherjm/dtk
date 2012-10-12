/* %ClassName%.cpp ---
 *
 * Author: %Author%
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "%ClassName%.h"
#include "%ClassName%_p.h"

#include <dtkLog>

// /////////////////////////////////////////////////////////////////
// %ClassName% implementation
// /////////////////////////////////////////////////////////////////

%ClassName%::%ClassName%(void) : dtkAbstractView(*new %ClassName%Private(this), 0)
{
    DTK_D(%ClassName%);

    d->numberOfChannels = 0;
}

%ClassName%::%ClassName%(const %ClassName%& other) : dtkAbstractView(*new %ClassName%Private(*other.d_func()), other)
{

}

%ClassName%::~%ClassName%(void)
{

}

//! Returns a new %ClassName% that is a copy of this.
/*!
 *  This method can be overloaded through the hierarchy enabling a
 *  deep copy of this. Note that, using covariance of returned type,
 *  the returned argument can be of the more derived type.
 *
 *  Example:
 *  \code
 *  class xyzData : public %ClassName%
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
%ClassName% *%ClassName%::clone(void)
{
    return new %ClassName%(*this);
}

%ClassName%& %ClassName%::operator = (const %ClassName%& other)
{
    this->copy(other);

    return (*this);
}

//! Enables to make a deep copy of the attributes through the class
//! hierarchy.
/*!
 *  This method is called by the assignement operator which delegates
 *  the copy process. When re-implementing this method into a derived
 *  class of %ClassName%, one must called first the copy method
 *  of the parent to ensure that all the attributes are really copied.
 *
 *  Nevertheless, some caution must be taken to avoid slicing problem
 *  as shown in the following example.
 *
 *  Example:
 *  \code
 *  class xyzData : public %ClassName%
 *  {
 *    ...
 *    void copy(const dtkAbstractView& other);
 *    ...
 *  };
 *
 *  void xyzData::copy(const dtkAbstractView& other)
 *  {
 *     // copy of the parent attributes
 *     %ClassName%::copy(other);
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
void %ClassName%::copy(const dtkAbstractView& other)
{
    dtkAbstractView::copy(other);

    if (this->identifier() == other.identifier()) {

        const %ClassName%& view = reinterpret_cast<const %ClassName%&>(other);

        DTK_D(%ClassName%);

    } else {
        dtkWarn() << "Other is not of same type than this, slicing is occuring.";
    }
}

//! Returns Class name.
/*!
 *
 */
QString %ClassName%::identifier(void) const
{
    return "%ClassName%";
}
