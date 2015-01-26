/* dtkComposer.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Tue Apr  9 12:43:49 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr 15 10:30:06 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 32
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

class dtkComposerNodeFactory;

namespace dtkComposer
{
    namespace node {
        DTKCOMPOSER_EXPORT dtkComposerNodeFactory& factory(void);
    }
}
