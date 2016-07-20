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
    void    insertName(const QString& path, const QString& name);
    void insertVersion(const QString& path, const QString& version);
    void insertConcept(const QString& path, const QString& concept);

public:
    QString pluginPath(const QString& name) const;

    QString    name(const QString& path) const;
    QString version(const QString& path) const;
    QString concept(const QString& path) const;

public:
    bool    hasName(const QString& name) const;
    bool hasVersion(const QString& version) const;
    bool hasConcept(const QString& concept) const;

public:
    QHash<QString, QString>::const_iterator namesBegin(void) const;
    QHash<QString, QString>::const_iterator   namesEnd(void) const;

    QHash<QString, QString>::const_iterator versionsBegin(void) const;
    QHash<QString, QString>::const_iterator   versionsEnd(void) const;

    QHash<QString, QString>::const_iterator conceptsBegin(void) const;
    QHash<QString, QString>::const_iterator   conceptsEnd(void) const;

public:
    QStringList pluginPaths(void) const;

    QStringList    names(void) const;
    QStringList versions(void) const;
    QStringList concepts(void) const;

private:
    dtkCorePluginManagerBase(void);

private:
    static dtkCorePluginManagerBase *s_instance;

private:
    dtkCorePluginManagerBasePrivate *d;
};
