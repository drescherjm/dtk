/* dtkComposerTransmitterProxyLoop.tpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Fri Mar 29 15:46:58 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Apr  2 10:21:44 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 47
 */

/* Change Log:
 * 
 */

#include "dtkComposerTransmitter_p.h"

// ///////////////////////////////////////////////////////////////////
// dtkComposerTransmitterProxyLoop inline implementations
// ///////////////////////////////////////////////////////////////////

bool dtkComposerTransmitterProxyLoop::enableCopy(void)
{
    bool enable_copy = (d->receivers.count() > 1);

    if (m_source)
	enable_copy = (enable_copy || m_source->enableCopy());

    return enable_copy;
}

QVariant dtkComposerTransmitterProxyLoop::variant(void)
{
    if (m_source)	
	return m_source->variant();

    return d->variant;
}

QVariantList dtkComposerTransmitterProxyLoop::allData(void)
{
    if (m_source)
	m_source->allData();

    return QVariantList();
}

void dtkComposerTransmitterProxyLoop::enableLoopMode(void)
{
    m_source = static_cast<dtkComposerTransmitter *>(m_twin);
}

void dtkComposerTransmitterProxyLoop::disableLoopMode(void)
{
    m_source = d->active_emitter;
}

void dtkComposerTransmitterProxyLoop::setTwin(dtkComposerTransmitterProxyLoop *twin)
{
    m_twin = twin;
}

dtkComposerTransmitterProxyLoop *dtkComposerTransmitterProxyLoop::twin(void) const
{
    return m_twin;
}
