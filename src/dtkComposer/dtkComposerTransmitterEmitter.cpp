/* dtkComposerTransmitterEmitter.cpp --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: Tue Sep 18 09:19:03 2012 (+0200)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerTransmitterEmitter.h"

// /////////////////////////////////////////////////////////////////
// Partial specializations for atomic types
// /////////////////////////////////////////////////////////////////

template <> QString dtkComposerTransmitterEmitter<qreal>::dataDescription(void)
{
    return QString::number(*m_data, 'G', 16);
};

template <> QString dtkComposerTransmitterEmitter<qlonglong>::dataDescription(void)
{
    return QString::number(*m_data);
};

template <> QString dtkComposerTransmitterEmitter<QString>::dataDescription(void)
{
    return *m_data;
};

template <> QString dtkComposerTransmitterEmitter<bool>::dataDescription(void)
{
    return QString::number(static_cast<int>(*m_data));
};
