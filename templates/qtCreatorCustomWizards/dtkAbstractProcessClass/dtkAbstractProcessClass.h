/* %ClassName%.h ---
 *
 * Author: %Author%
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef %ClassName:u%_H
#define %ClassName:u%_H

#include <dtkCore/dtkAbstractProcess.h>

#include "%Layer%Export.h"

class %ClassName%Private;

// /////////////////////////////////////////////////////////////////
// %ClassName% interface
// /////////////////////////////////////////////////////////////////

class %Layer:u%_EXPORT %ClassName% : public dtkAbstractProcess
{
    Q_OBJECT

public:
             %ClassName%(void);
             %ClassName%(const %ClassName%& other);
    virtual ~%ClassName%(void);

public:
    virtual %ClassName% *clone(void);

public:
    %ClassName%& operator = (const %ClassName%& other);

protected:
   virtual void copy(const dtkAbstractObject& other);

public:
   QString identifier(void) const;

public:
    // Add your own setter methods

    // Try to sort in the alphabetical order

public:
    // Add your own getter methods

    // Try to sort in the alphabetical order

public:
    // Methods you want to overload from dtkAbstractProcess

   // Try to sort in the alphabetical order

public:
    // Miscellaneous methods

    // Try to sort in the alphabetical order

private:
    DTK_DECLARE_PRIVATE(%ClassName%);
};

Q_DECLARE_METATYPE(%ClassName%)
Q_DECLARE_METATYPE(%ClassName%*)

#endif

