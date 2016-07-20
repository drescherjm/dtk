/* dtkContainerVector.cpp ---
 *
 * Author: Julien Wintz
 * Created: Mon Sep 30 17:00:53 2013 (+0200)
 * Version:
 * Last-Updated: Mon Sep 30 17:01:07 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Change Log:
 *
 */

#include "dtkContainerVector.h"

template <> QString dtkContainerVector<double>::description(void) const
{
    QString string;

    string = "[ " ;

    qlonglong count = m_vector.count();

    if (count > 0) {
        QString string2 = QString("%1").arg(m_vector.at(0));
        string += string2;
    }

    for (qlonglong i = 1; i < count; ++i) {
        string.append("; ");
        QString string2 = QString("%1").arg(m_vector.at(i));
        string += string2;
    }

    string.append(" ]");

    return string;
}
