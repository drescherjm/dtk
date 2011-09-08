/* main.cpp --- 
 * 
 * Author: 
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Sep  6 14:15:35 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep  8 09:48:36 2011 (+0200)
 *           By: jwintz
 *     Update #: 157
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>

int main(int argc, char **argv)
{
    if(argc < 2) {
        qDebug() << "Usage:" << argv[0] << "count";
        return 0;
    }

    const int max = 100000;
    
    int count = atoi(argv[1]);

    if(count > max) {
        qDebug() << "Count is too large";
        return 0;
    }
    
    int m_array[max];

// /////////////////////////////////////////////////////////////////
// Initialize data
// /////////////////////////////////////////////////////////////////

    for(int i = 0; i < count; i++)
        m_array[i] = i+1;

// /////////////////////////////////////////////////////////////////
// Compute sum
// /////////////////////////////////////////////////////////////////

    int sum = 0;
        
    for(int i = 0; i < count; i++)
        sum += m_array[i];
    
    qDebug() << "Sum is" << sum;

    return 0;
}
