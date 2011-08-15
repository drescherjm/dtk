#ifndef DTKTESTSINGLETON_H
#define DTKTESTSINGLETON_H

#include <dtkCore/dtkSingletonDeclare.h>

#include <QObject>


class dtkTestSingleton : public QObject
{

    DTK_DECLARE_SINGLETON( dtkTestSingleton );
public:
    static int InstanceCount ();
private:
    dtkTestSingleton();
    ~dtkTestSingleton();

    static int ms_count;

};
#endif // DTKTESTSINGLETON_H
