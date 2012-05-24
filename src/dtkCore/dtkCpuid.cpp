/* @(#)dtkCpuid.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/25 13:18:27
 * Version: $Id$
 * Last-Updated: mer. avril 25 15:46:20 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 46
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

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

/* public: */
/*   const uint32_t &EAX() const {return regs[0];}; */
/*   const uint32_t &EBX() const {return regs[1];}; */
/*   const uint32_t &ECX() const {return regs[2];}; */
/*   const uint32_t &EDX() const {return regs[3];}; */

void dtkCpuid::load(unsigned i) {
#if defined(Q_OS_WIN) && defined(MSVC)
    __cpuid((int *)d->regs, (int)i);
#else
    asm volatile
      ("cpuid" : "=a" (d->regs[0]), "=b" (d->regs[1]), "=c" (d->regs[2]), "=d" (d->regs[3])
       : "a" (i), "c" (0));
    // ECX is set to zero for CPUID function 4
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
