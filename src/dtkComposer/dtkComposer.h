/* dtkComposer.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Tue Apr  9 12:43:49 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 10 15:02:48 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 29
 */

/* Change Log:
 * 
 */

#pragma once

class dtkComposerNodeFactory;

namespace dtkComposer
{
    namespace node {
	dtkComposerNodeFactory& factory(void);
    }
}

