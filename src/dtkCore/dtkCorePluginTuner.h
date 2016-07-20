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

#pragma once

#include <QVariant>

// /////////////////////////////////////////////////////////////////
// dtkCorePluginTuner interface
// /////////////////////////////////////////////////////////////////

template < typename T > class dtkCorePluginTuner
{
public:
    dtkCorePluginTuner(void);
    virtual ~dtkCorePluginTuner(void);

    void setObject(T *object);
    void setMap(const QVariantHash& map);

    virtual void update(void) = 0;

    T *object(void) const;
    const QVariantHash& map(void) const;

private:
    T *m_object;
    QVariantHash m_map;
};

// /////////////////////////////////////////////////////////////////

#include "dtkCorePluginTuner.tpp"

//
// dtkCorePluginTuner.h ends here
