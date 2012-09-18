/* dtkComposerTransmitterEmitter.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Sep 18 09:19:03 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Sep 18 09:19:41 2012 (+0200)
 *           By: tkloczko
 *     Update #: 3
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
    return QString::number(*m_data);
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
