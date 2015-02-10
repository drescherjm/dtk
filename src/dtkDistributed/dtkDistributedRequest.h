/* dtkDistributedRequest.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/02/09 20:27:16
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkDistributedExport.h"

class dtkDistributedRequest
{

public:
    virtual ~dtkDistributedRequest(void) {;}

public:
    virtual void wait(void) {;};

};



