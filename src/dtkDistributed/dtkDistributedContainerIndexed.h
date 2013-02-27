/* dtkDistributedContainerIndexed.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Wed Feb 13 15:53:54 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkDistributedContainer.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainerIndexed interface
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedContainerIndexed : public virtual dtkDistributedContainer<T>
{
public:
             dtkDistributedContainerIndexed(void) : dtkDistributedContainer<T>() {;}
    virtual ~dtkDistributedContainerIndexed(void) {;}

public:
    // virtual void resize(const qlonglong& size) = 0;

    virtual void    set(const qlonglong& index, const T& value) = 0;
    // virtual void insert(const qlonglong& index, const T& value) = 0;

    // virtual void removeAt(const qlonglong& index) = 0;

public:
    virtual T at(const qlonglong& index) const = 0;
};
