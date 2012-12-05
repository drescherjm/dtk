/* %1_p.h ---
 *
 * Author: %Author%
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef %2_P_H
#define %2_P_H

#include "%3CoreExport.h"

#include <dtkCore/dtkAbstract%4_p.h>

class %1;

////////////////////////////////////////////////////
// %1Private interface
////////////////////////////////////////////////////

class DTKCORE_EXPORT %1Private : public dtkAbstract%4Private
{
public:
    %1Private(%1 *q = 0) : dtkAbstract%4Private(q) {}
    %1Private(const %1Private& other) : dtkAbstract%4Private(other) {}

public:
    virtual ~%1Private(void) {}

public:
    // private members of the class are put here in the d-pointer, eg
    // int index;
};

////////////////////////////////////////////////////
// %1 protected constructors
////////////////////////////////////////////////////

DTK_IMPLEMENT_PRIVATE(%1, dtkAbstract%4);

#endif
