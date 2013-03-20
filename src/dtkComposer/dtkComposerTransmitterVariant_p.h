/* dtkComposerTransmitterVariant_p.h --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: Fri Aug  3 14:36:46 2012 (+0200)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERVARIANT_P_H
#define DTKCOMPOSERTRANSMITTERVARIANT_P_H

#include <dtkConfig.h>

#if defined(DTK_HAVE_PLOT)
#include <dtkPlot/dtkPlotCurve.h>
#endif

#include <QtCore>

class dtkComposerTransmitter;
class dtkComposerTransmitterVariant;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariantPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterVariantPrivate
{
public:
    QList<dtkComposerTransmitter *> emitters;
    QList<dtkComposerTransmitterVariant *> variants;

public:
    dtkComposerTransmitter        *active_emitter;
    dtkComposerTransmitterVariant *active_variant;

public:
    QVector<const dtkComposerType *> data_types;

public:
    dtkComposerTransmitterVariant *twin;

    bool twinned;

    bool already_ask;

public:
    dtkComposerVariant m_variant;

public:
    bool data_owner;

#if defined(DTK_HAVE_PLOT)
public:
    dtkPlotCurve curve;
#endif

};

#endif
