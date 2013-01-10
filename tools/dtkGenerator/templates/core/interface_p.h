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

#include %4

class %1;

////////////////////////////////////////////////////
// %1Private interface
////////////////////////////////////////////////////

class DTKCORE_EXPORT %1Private : public %3Private
{
public:
    %1Private(%1 *q = 0) : %3Private(q) {}
    %1Private(const %1Private& other) : %3Private(other) {}

public:
    virtual ~%1Private(void) {}

public:
    // private members of the class are put here in the d-pointer, eg
    // int index;
};

////////////////////////////////////////////////////
// %1 protected constructors
////////////////////////////////////////////////////

DTK_IMPLEMENT_PRIVATE(%1, %3);

#endif
