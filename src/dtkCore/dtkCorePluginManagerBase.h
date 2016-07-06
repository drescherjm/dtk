/* @(#)dtkCorePluginManagerBase.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2016 - Nicolas Niclausse, Inria.
 * Created: 2016/07/04 14:04:27
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkCoreExport.h"

#include <QtCore>

class dtkCorePluginManagerBasePrivate;

// /////////////////////////////////////////////////////////////////
// dtkCorePluginManagerBase interface
// /////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkCorePluginManagerBase
{
public:
    static dtkCorePluginManagerBase *instance(void);

public:
    void    insertName(const QString& path, const QVariant& name);
    void insertVersion(const QString& path, const QVariant& version);
    void insertConcept(const QString& path, const QVariant& concept);

public:
    QString pluginPath(const QVariant& name) const;

    QVariant    name(const QString& path) const;
    QVariant version(const QString& path) const;
    QVariant concept(const QString& path) const;

public:
    bool    hasName(const QVariant& name) const;
    bool hasVersion(const QVariant& version) const;
    bool hasConcept(const QVariant& concept) const;

public:
    QHash<QString, QVariant>::const_iterator namesBegin(void) const;
    QHash<QString, QVariant>::const_iterator   namesEnd(void) const;

    QHash<QString, QVariant>::const_iterator versionsBegin(void) const;
    QHash<QString, QVariant>::const_iterator   versionsEnd(void) const;

    QHash<QString, QVariant>::const_iterator conceptsBegin(void) const;
    QHash<QString, QVariant>::const_iterator   conceptsEnd(void) const;

public:
    QStringList pluginPaths(void) const;

    QVariantList    names(void) const;
    QVariantList versions(void) const;
    QVariantList concepts(void) const;

private:
    dtkCorePluginManagerBase(void);

private:
    static dtkCorePluginManagerBase *s_instance;

private:
    dtkCorePluginManagerBasePrivate *d;
};
