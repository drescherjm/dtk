/* dtkMatrix.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Oct  4 12:36:50 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Oct  4 12:58:12 2012 (+0200)
 *           By: tkloczko
 *     Update #: 23
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkMatrix.h"

// /////////////////////////////////////////////////////////////////
// Partial specializations for atomic types
// /////////////////////////////////////////////////////////////////

template <> QByteArray *dtkMatrix<double>::serialize(void)
{
    unsigned i_end = m_crow * m_ccol;

    if (i_end <= 0)
        return NULL;

    QByteArray *array = new QByteArray;
    array->append(reinterpret_cast<const char*>(&m_crow), sizeof(m_crow));
    array->append(reinterpret_cast<const char*>(&m_ccol), sizeof(m_ccol));

    QDataStream stream(array, QIODevice::WriteOnly);

    for (unsigned i = 0; i < i_end; ++i)
	stream << (*m_rgrow)[i];

    return array;
};

template <> void dtkMatrix<double>::deserialize(const QByteArray& array)
{
    QDataStream stream(array);

    stream >> m_crow;
    stream >> m_ccol;

    unsigned i_end = m_crow * m_ccol;

    if (i_end <= 0)
        return;

    this->allocate(m_crow, m_ccol);

    for (unsigned i = 0; i < i_end; ++i)
	stream >> (*m_rgrow)[i];
};
