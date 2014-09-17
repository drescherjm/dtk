/* dtkCore.h ---
 *
 * Author: Julien Wintz
 * Created: Thu Feb 28 16:28:31 2013 (+0100)
 * Version:
 * Last-Updated: mer. sept. 17 11:23:04 2014 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 66
 */

/* Change Log:
 *
 */

#pragma once

#include <QtCore>

// ///////////////////////////////////////////////////////////////////
// SFINAE to detect serializable objects
// ///////////////////////////////////////////////////////////////////

template<typename T> struct IsObjectSerializable
{
    enum { Value = false };
};

// Specialize to avoid sizeof(void) warning
template<> struct IsObjectSerializable<void *>
{
    enum { Value = false };
};

class dtkObjectSerializable;

template<> struct IsObjectSerializable<dtkObjectSerializable *>
{
    enum { Value = true };
};

template<typename T> struct IsObjectSerializable<T *>
{
private:
    typedef qint8  dtk_yes_type;
    typedef qint64 dtk_no_type;

    static dtk_yes_type checkType(dtkObjectSerializable *);
    static dtk_no_type  checkType(...);

public:
    enum { Value = sizeof(checkType(static_cast<T *>(0))) == sizeof(dtk_yes_type) };
};

// ///////////////////////////////////////////////////////////////////
// SFINAE to detect copiable objects
// ///////////////////////////////////////////////////////////////////

template<typename T> struct IsObjectCopiable
{
    enum { Value = false };
};

// Specialize to avoid sizeof(void) warning
template<> struct IsObjectCopiable<void *>
{
    enum { Value = false };
};

class dtkObjectCopiable;

template<> struct IsObjectCopiable<dtkObjectCopiable *>
{
    enum { Value = true };
};

template<typename T> struct IsObjectCopiable<T *>
{
private:
    typedef qint8  dtk_yes_type;
    typedef qint64 dtk_no_type;

    static dtk_yes_type checkType(dtkObjectCopiable *);
    static dtk_no_type  checkType(...);

public:
    enum { Value = sizeof(checkType(static_cast<T *>(0))) == sizeof(dtk_yes_type) };
};


// ///////////////////////////////////////////////////////////////////
// Helper functions
// ///////////////////////////////////////////////////////////////////

inline bool dtkCoreApplicationArgumentsContain(int argc, char **argv, QString value)
{
    for(int i = 1; i < argc; i++)
        if(QString(argv[i]) == value)
            return true;

    return false;
}

inline bool dtkCoreApplicationArgumentsContain(QCoreApplication *application, QString value)
{
    return application->arguments().contains(value);
}

inline QString dtkCoreApplicationArgumentsValue(int argc, char **argv, QString key)
{
    for(int i = 1; i < argc; i++) {
        if(QString(argv[i]) == key) {
            if(i+1 < argc)
                return QString(argv[i+1]);
            else
                return QString();
        }
    }

    return QString();
}

inline QString dtkCoreApplicationArgumentsValue(QCoreApplication *application, QString key)
{
    QStringList args = application->arguments();
    int i = args.indexOf(key);
    if ( i > -1 && i < args.count()) {
        return args.at(i+1);
    } else {
        return QString();
    }
}
