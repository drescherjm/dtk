/* @(#)dtkCorePluginManagerBase.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2016 - Nicolas Niclausse, Inria.
 * Created: 2016/07/04 14:23:33
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkCorePluginManagerBase.h"

// /////////////////////////////////////////////////////////////////
// dtkCorePluginManagerBasePrivate class
// /////////////////////////////////////////////////////////////////

class dtkCorePluginManagerBasePrivate
{
public:
    QHash<QString, QString> names;
    QHash<QString, QString> versions;
    QHash<QString, QString> concepts;
};

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

dtkCorePluginManagerBase::dtkCorePluginManagerBase(void) : d(new dtkCorePluginManagerBasePrivate)
{

}

dtkCorePluginManagerBase* dtkCorePluginManagerBase::instance(void)
{
    if(!s_instance) {
        s_instance = new dtkCorePluginManagerBase;
    }

    return s_instance;
};

void dtkCorePluginManagerBase::insertName(const QString& path, const QString& name)
{
    d->names.insert(path, name);
}

void dtkCorePluginManagerBase::insertVersion(const QString& path, const QString& version)
{
    d->versions.insert(path, version);
}

void dtkCorePluginManagerBase::insertConcept(const QString& path, const QString& concept)
{
    d->concepts.insert(path, concept);
}

QString dtkCorePluginManagerBase::pluginPath(const QString& name) const
{
    return d->names.key(name);
}

QString dtkCorePluginManagerBase::name(const QString& path) const
{
    return d->names.value(path);
}

QString dtkCorePluginManagerBase::version(const QString& path) const
{
    return d->versions.value(path);
}

QString dtkCorePluginManagerBase::concept(const QString& path) const
{
    return d->concepts.value(path);
}

bool dtkCorePluginManagerBase::hasName(const QString& name) const
{
    for (const QString& n : d->names) {
        if (n == name) {
            return true;
        }
    }
    return false;
}

bool dtkCorePluginManagerBase::hasVersion(const QString& version) const
{
    for (const QString& v : d->versions) {
        if (v == version) {
            return true;
        }
    }
    return false;
}

bool dtkCorePluginManagerBase::hasConcept(const QString& concept) const
{
    for (const QString& c : d->concepts) {
        if (c == concept) {
            return true;
        }
    }
    return false;
}

QHash<QString, QString>::const_iterator dtkCorePluginManagerBase::namesBegin(void) const
{
    return d->names.cbegin();
}

QHash<QString, QString>::const_iterator dtkCorePluginManagerBase::namesEnd(void) const
{
    return d->names.cend();
}

QHash<QString, QString>::const_iterator dtkCorePluginManagerBase::versionsBegin(void) const
{
    return d->versions.cbegin();
}

QHash<QString, QString>::const_iterator dtkCorePluginManagerBase::versionsEnd(void) const
{
    return d->versions.cend();
}

QHash<QString, QString>::const_iterator dtkCorePluginManagerBase::conceptsBegin(void) const
{
    return d->concepts.cbegin();
}

QHash<QString, QString>::const_iterator dtkCorePluginManagerBase::conceptsEnd(void) const
{
    return d->concepts.cend();
}

QStringList dtkCorePluginManagerBase::pluginPaths(void) const
{
    return d->names.keys();
}

QStringList dtkCorePluginManagerBase::names(void) const
{
    return d->names.values();
}

QStringList dtkCorePluginManagerBase::versions(void) const
{
    return d->versions.values();
}

QStringList dtkCorePluginManagerBase::concepts(void) const
{
    return d->concepts.values();
}

dtkCorePluginManagerBase *dtkCorePluginManagerBase::s_instance = NULL;
