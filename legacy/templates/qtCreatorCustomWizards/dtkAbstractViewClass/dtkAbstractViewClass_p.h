/* %ClassName%_p.h ---
 *
 * Author: %Author%
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef %ClassName:u%_P_H
#define %ClassName:u%_P_H

#include "%Layer%Export.h"

#include <dtkCore/dtkAbstractView_p.h>

class %ClassName%;

////////////////////////////////////////////////////
// %ClassName%Private interface
////////////////////////////////////////////////////

class DTKCORE_EXPORT %ClassName%Private : public dtkAbstractViewPrivate
{
public:
    %ClassName%Private(%ClassName% *q = 0) : dtkAbstractViewPrivate(q) {}
    %ClassName%Private(const %ClassName%Private& other) : dtkAbstractViewPrivate(other) {}

public:
    virtual ~%ClassName%Private(void) {}

public:
    // private members of the class are put here in the d-pointer, eg
    // int index;
};

////////////////////////////////////////////////////
// %ClassName% protected constructors
////////////////////////////////////////////////////

DTK_IMPLEMENT_PRIVATE(%ClassName%, dtkAbstractView);

#endif
