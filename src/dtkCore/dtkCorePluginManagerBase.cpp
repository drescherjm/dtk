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
    QHash<QString, QVariant> names;
    QHash<QString, QVariant> versions;
    QHash<QString, QVariant> concepts;
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

void dtkCorePluginManagerBase::insertName(const QString& path, const QVariant& name)
{
    d->names.insert(path, name);
}

void dtkCorePluginManagerBase::insertVersion(const QString& path, const QVariant& version)
{
    d->versions.insert(path, version);
}

void dtkCorePluginManagerBase::insertConcept(const QString& path, const QVariant& concept)
{
    d->concepts.insert(path, concept);
}

QString dtkCorePluginManagerBase::pluginPath(const QVariant& name) const
{
    return d->names.key(name);
}

QVariant dtkCorePluginManagerBase::name(const QString& path) const
{
    return d->names.value(path);
}

QVariant dtkCorePluginManagerBase::version(const QString& path) const
{
    return d->versions.value(path);
}

QVariant dtkCorePluginManagerBase::concept(const QString& path) const
{
    return d->concepts.value(path);
}

bool dtkCorePluginManagerBase::hasName(const QVariant& name) const
{
    for (const QVariant& n : d->names) {
        if (n == name) {
            return true;
        }
    }
    return false;
}

bool dtkCorePluginManagerBase::hasVersion(const QVariant& version) const
{
    for (const QVariant& v : d->versions) {
        if (v == version) {
            return true;
        }
    }
    return false;
}

bool dtkCorePluginManagerBase::hasConcept(const QVariant& concept) const
{
    for (const QVariant& c : d->concepts) {
        if (c == concept) {
            return true;
        }
    }
    return false;
}

QHash<QString, QVariant>::const_iterator dtkCorePluginManagerBase::namesBegin(void) const
{
    return d->names.cbegin();
}

QHash<QString, QVariant>::const_iterator dtkCorePluginManagerBase::namesEnd(void) const
{
    return d->names.cend();
}

QHash<QString, QVariant>::const_iterator dtkCorePluginManagerBase::versionsBegin(void) const
{
    return d->versions.cbegin();
}

QHash<QString, QVariant>::const_iterator dtkCorePluginManagerBase::versionsEnd(void) const
{
    return d->versions.cend();
}

QHash<QString, QVariant>::const_iterator dtkCorePluginManagerBase::conceptsBegin(void) const
{
    return d->concepts.cbegin();
}

QHash<QString, QVariant>::const_iterator dtkCorePluginManagerBase::conceptsEnd(void) const
{
    return d->concepts.cend();
}

QStringList dtkCorePluginManagerBase::pluginPaths(void) const
{
    return d->names.keys();
}

QVariantList dtkCorePluginManagerBase::names(void) const
{
    return d->names.values();
}

QVariantList dtkCorePluginManagerBase::versions(void) const
{
    return d->versions.values();
}

QVariantList dtkCorePluginManagerBase::concepts(void) const
{
    return d->concepts.values();
}

dtkCorePluginManagerBase *dtkCorePluginManagerBase::s_instance = NULL;
