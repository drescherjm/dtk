/* dtkComposerNodeTrackerVrpn.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Apr 26 16:50:56 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 17:55:21 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODETRACKERVRPN_H
#define DTKCOMPOSERNODETRACKERVRPN_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeTrackerVrpnPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeTrackerVrpn : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeTrackerVrpn(void);
    ~dtkComposerNodeTrackerVrpn(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "vrpnTracker";
    }

    inline QString titleHint(void) {
        return "VrpnTracker";
    }

    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "url";

        return dtkComposerNodeLeaf::outputLabelHint(port);
    }

    inline QString outputLabelHint(int port) {
        if (port == 0)
            return "head position";

        if (port == 1)
            return "head orientation";

        return dtkComposerNodeLeaf::outputLabelHint(port);
    }

private:
    dtkComposerNodeTrackerVrpnPrivate *d;
};

#endif
