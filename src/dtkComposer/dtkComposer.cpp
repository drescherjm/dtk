/* dtkComposer.cpp ---
 *
 * Author: Thibaud Kloczko
 * Created: Tue Apr  9 12:49:06 2013 (+0200)
 */

/* Change Log:
 *
 */

#include "dtkComposer.h"
#include "dtkComposerNodeFactory.h"

namespace dtkComposer
{
    namespace node
    {
        namespace _private {
            dtkComposerNodeFactory _factory;
        }

        dtkComposerNodeFactory& factory(void) {
            return _private::_factory;
        }
    }
}
