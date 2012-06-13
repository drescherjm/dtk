/* @(#)dtkCpuid.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/25 13:18:27
 * Version: $Id$
 * Last-Updated: Fri Jun  8 12:28:51 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 52
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkConfig.h>

#include <dtkCore/dtkGlobal.h>

#include "dtkCpuid.h"

#if defined(Q_OS_WIN)
#include <limits.h>
#if defined(MSVC)
typedef unsigned __int32  uint32_t;
#endif
#else
#include <stdint.h>
#endif


class dtkCpuidPrivate
{
public:
  uint32_t regs[4];
};

dtkCpuid::dtkCpuid(void) : d (new dtkCpuidPrivate)
{

}

dtkCpuid::~dtkCpuid(void)
{
    delete d;
}

void dtkCpuid::load(unsigned i) {
#if defined(Q_OS_WIN) && defined(MSVC)
    __cpuid((int *)d->regs, (int)i);
#elif defined(DTK_PLATFORM_64)
    asm volatile
      ("cpuid" : "=a" (d->regs[0]), "=b" (d->regs[1]), "=c" (d->regs[2]), "=d" (d->regs[3])
       : "a" (i), "c" (0));
#endif
}

QString dtkCpuid::vendor(void)
{
    this->load(0); // Get CPU vendor

    QString vendor;
    vendor += QString::fromAscii((const char *)&d->regs[1],4);
    vendor += QString::fromAscii((const char *)&d->regs[3],4);
    vendor += QString::fromAscii((const char *)&d->regs[2],4);
    return vendor;
}
