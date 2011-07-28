
#include "dtkTestSingleton.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>
#include <dtkCore/dtkSingleton.h>

int dtkTestSingleton::ms_count = 0;

DTK_IMPLEMENT_SINGLETON( dtkTestSingleton );

dtkTestSingleton::dtkTestSingleton()
{
    dtkDebug() << DTK_LINK_TEXT << "Constructor";
    ++ms_count;
}

dtkTestSingleton::~dtkTestSingleton()
{
    dtkDebug() << DTK_LINK_TEXT << "Destructor";
    --ms_count;
}

int dtkTestSingleton::InstanceCount()
{
    return ms_count;
}


