// Version: $Id$
// 
// 

// Commentary: 
// 
// 

// Change Log:
// 
// 

// Code:


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
    if (m_source == d->active_emitter)	
	return m_source->variant();

    return d->variant;
}

inline void dtkComposerTransmitterProxyLoop::setVariant(const QVariant& v)
{
    d->variant = v;
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

// 
// dtkComposerTransmitterProxyLoop.tpp ends here
