/* dtkComposerVariant.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Mar 20 12:50:55 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Mar 20 13:07:04 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 26
 */

/* Change Log:
 * 
 */

#include "dtkComposerVariant.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerVariant implementation
// /////////////////////////////////////////////////////////////////

dtkComposerVariant::dtkComposerVariant(void) : QVariant(), m_object(0), m_data(0), m_matrix(0)
{

};

dtkComposerVariant::dtkComposerVariant(const dtkComposerVariant& other) : QVariant(other), m_object(other.m_object), m_data(other.m_data), m_matrix(other.m_matrix)
{
    
}

dtkComposerVariant::dtkComposerVariant(const QVariant& variant) : QVariant(variant), m_object(0), m_data(0), m_matrix(0)
{

}

dtkComposerVariant::~dtkComposerVariant(void)
{
    this->m_object = NULL;
    this->m_data   = NULL;
    this->m_matrix = NULL;
}
    
dtkComposerVariant& dtkComposerVariant::operator = (const dtkComposerVariant& other)
{
    if (this == &other)
        return *this;

    QVariant::operator=(other);

    this->m_object = other.m_object;
    this->m_data   = other.m_data;
    this->m_matrix = other.m_matrix;

    return (*this);
}

bool dtkComposerVariant::operator == (const dtkComposerVariant& other)
{
    if (this == &other)
        return true;

    if (this->m_object != other.m_object ||
        this->m_data   != other.m_data   || 
        this->m_matrix != other.m_matrix ||
        !this->QVariant::operator==(other))
        return false;

    return true;
}

bool dtkComposerVariant::operator != (const dtkComposerVariant& other)
{
    return !(this->operator==(other));
}

dtkComposerVariant dtkComposerVariant::fromQVariant(const QVariant& variant)
{
    dtkComposerVariant result(variant);
    return result;
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

template<> QByteArray dtkComposerVariant::value(void) const
{
    if (this->m_data)
        return *((const_cast<dtkAbstractData*>(m_data))->serialize());

    if (this->m_matrix)
        return *((const_cast<dtkMatrixReal*>(m_matrix))->serialize());
    
    return this->QVariant::toByteArray();
}
