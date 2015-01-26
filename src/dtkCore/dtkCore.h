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

#include <fstream>

inline bool dtkFileIsBinary(const QString& path)
{
    int c; std::ifstream a(path.toUtf8().constData());

    while(((c = a.get()) != EOF) && (c <= 127)) { ; }

    return (c != EOF);
}
