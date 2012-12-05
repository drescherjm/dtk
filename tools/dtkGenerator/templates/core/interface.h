/* %1.h ---
 *
 * Author: %Author%
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef %2_H
#define %2_H

#include <dtkCore/dtkAbstract%5.h>

#include "%3Export.h"

class %1Private;

// /////////////////////////////////////////////////////////////////
// %1 interface
// /////////////////////////////////////////////////////////////////

class %4CORE_EXPORT %1 : public dtkAbstract%5
{
    Q_OBJECT

public:
             %1(void);
             %1(const %1& other);
    virtual ~%1(void);

public:
    virtual %1 *clone(void); // If your class is pure virtual you need to set this method to pure virtual too! 

public:
    %1& operator = (const %1& other);

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
    // Methods you want to overload from dtkAbstract%5

   // Try to sort in the alphabetical order

public:
    // Miscellaneous methods

    // Try to sort in the alphabetical order

private:
    DTK_DECLARE_PRIVATE(%1);
};

Q_DECLARE_METATYPE(%1)  // If your class is pure virtual, you cannot register to QMetatype.
Q_DECLARE_METATYPE(%1*) // Hence, you need to comment theses lines.

#endif

