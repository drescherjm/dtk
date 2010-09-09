/* dtkMath.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2008 - Thibaud Kloczko, Inria.
 * Created: Tue Jul  6 16:57:24 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep  9 11:35:42 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 22
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkMath.h"
#include "dtkVector3D.h"

//! dtkBubbleSort(unsigned int indices[], int size) 
/*! 
 * Sorts the integer of an array by growing values.
 */
void dtkBubbleSort(unsigned int indices[], int size) 
{
    bool ordered = false;
    int j = 0;
    while ( (j<size-1) && (!ordered) ) {
        ordered = true;
        for (int k = 0; k<(size-1-j); k++) {
            if (indices[k] > indices[k+1]) {
                unsigned int temp = indices[k];
                indices[k] = indices[k+1];
                indices[k+1] = temp;
                ordered = false;
            }
        }
        j++;
    }
}
