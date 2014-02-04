/* dtkComposer.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Tue Apr  9 12:49:06 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 10 15:09:19 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 37
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
	    dtkComposerNodeFactory factory;
	}

	dtkComposerNodeFactory& factory(void) {
	    return _private::factory;
	}
    }
}
