/* dtkComposer.cpp ---
 *
 * Author: Thibaud Kloczko
 * Created: Tue Apr  9 12:49:06 2013 (+0200)
 */

/* Change Log:
 *
 */

#include "dtkComposerExport.h"

#include "dtkComposer.h"
#include "dtkComposerNodeFactory.h"

namespace dtkComposer
{
    namespace node
    {
        namespace _private {
            dtkComposerNodeFactory factory;
        }

        DTKCOMPOSER_EXPORT dtkComposerNodeFactory& factory(void) {
            return _private::factory;
        }
    }
}
