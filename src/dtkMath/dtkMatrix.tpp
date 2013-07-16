#include "dtkMatrix_p.h"

template <typename T> T dtkMatrix::at(int i)
{
    return static_cast<T *>(d->buffer)[i];
}
