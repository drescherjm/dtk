#include "dtkComposerTransmitterEmitter.h"


template <> QString dtkComposerTransmitterEmitter<qreal>::dataIdentifier(void)
{
    return QString::number(*m_data);
};
template <> QString dtkComposerTransmitterEmitter<qlonglong>::dataIdentifier(void)
{
    return QString::number(*m_data);
};
template <> QString dtkComposerTransmitterEmitter<QString>::dataIdentifier(void)
{
    return *m_data;
};
template <> QString dtkComposerTransmitterEmitter<bool>::dataIdentifier(void)
{
    return QString::number(static_cast<int>(*m_data));
};
