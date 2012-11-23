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

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// %ClassName% implementation
// /////////////////////////////////////////////////////////////////

%ClassName%::%ClassName%(void) : dtkAbstractData(*new %ClassName%Private(this), 0)
{
    // DTK_D(%ClassName%);
}

%ClassName%::%ClassName%(const %ClassName%& other) : dtkAbstractData(*new %ClassName%Private(*other.d_func()), other)
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

// Assignement operator
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
 *    void copy(const dtkAbstractData& other);
 *    ...
 *  };
 *
 *  void xyzData::copy(const dtkAbstractData& other)
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
void %ClassName%::copy(const dtkAbstractObject& other)
{
    dtkAbstractData::copy(other); // This call ensures that the
                                  // attributes of the parent class
                                  // are copied too.

    // The following code can be uncommented if the current class
    // contains some attributes. If not, it can be deleted.
    
    // if (this->identifier() == other.identifier()) {

    //     const %ClassName%& data = reinterpret_cast<const %ClassName%&>(other);

    //     DTK_D(%ClassName%);

    //     // Do the copy !!!

    // } else {
    //     dtkWarn() << "Other is not of same type than this, slicing is occuring.";
    // }
}

//! Comparison operator.
/*!
 *  
 */
bool %ClassName%::operator == (const %ClassName%& other) const
{
    return this->isEqual(other);
}

//! Enables to make a deep comparison between all the attributes through the class
//! hierarchy.
/*!
 *  This method is called by the comparator operator == which
 *  delegates the comparison. When re-implementing this method into a
 *  derived class of %ClassName%, one must called the isEqual
 *  method of the parent to ensure the comparison through all the
 *  attributes.
 *
 *  Example:
 *  \code
 *  class xyzData : public %ClassName%
 *  {
 *    ...
 *    bool isEqual(const dtkAbstractObject& other);
 *    ...
 *  };
 *
 *  bool xyzData::isEqual(const dtkAbstractObject& other)
 *  {
 *     // comparison of the parent attributes
 *     if (!%ClassName%::isEqual(other))
 *        return false;
 *
 *     // comparison of the types.
 *     if (this->identifier() != other.identifier())
 *        return false;
 *
 *     // comparison of the xyzData attributes after casting of other.
 *     ...
 *
 *     // comparison of parent attributes
 *    if (!%ClassName%::isEqual(other))
 *       return false;
 *
 *    return true;
 *  }
 *  \endcode
 */
bool %ClassName%::isEqual(const dtkAbstractObject& other) const
{
    if (this == &other)
        return true;

    if (this->identifier() != other.identifier())
        return false;

    const %ClassName%& data = reinterpret_cast<const %ClassName%&>(other);

    DTK_D(const %ClassName%);

    // Do the Test !!!

    // if (d->readers          != data.d_func()->readers          ||
    //     d->writers          != data.d_func()->writers          ||
    //     d->converters       != data.d_func()->converters       ||
    //     d->serializers      != data.d_func()->serializers      ||
    //     d->deserializers    != data.d_func()->deserializers    ||
    //     d->path             != data.d_func()->path             ||
    //     d->paths            != data.d_func()->paths            ||
    //     d->numberOfChannels != data.d_func()->numberOfChannels ||
    //     d->thumbnails       != data.d_func()->thumbnails)
    //    return false;

    if (!dtkAbstractObject::isEqual(other))
        return false;

    return true;  
}

//! Returns Class name.
/*!
 *
 */
QString %ClassName%::identifier(void) const
{
    return "%ClassName%";
}
