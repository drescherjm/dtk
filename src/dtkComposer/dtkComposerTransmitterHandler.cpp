/* dtkComposerTransmitterHandler.cpp ---
 *
 * Author: Thibaud Kloczko
 * Created: 2013 Fri Jan 18 14:25:40 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerTransmitterHandler.h"

#include <dtkContainer>

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

void dtkComposerTransmitterVariantHandler<dtkComposerVariant>::setData(dtkComposerVariant& data, dtkComposerTransmitterVariant& t_variant)
{
    t_variant.d->variant = data;

    if (t_variant.d->container) {
        delete t_variant.d->container;
        t_variant.d->container = NULL;
    }
}
