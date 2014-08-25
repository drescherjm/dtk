// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include <QtCore>
#include <QtDebug>

#include <dtkLogExport>

class QFileSystemWatcher;

// ///////////////////////////////////////////////////////////////////
// dtkLoggingCategory
// ///////////////////////////////////////////////////////////////////

class DTKLOG_EXPORT dtkLoggingCategoryPrivate
{
public:
             dtkLoggingCategoryPrivate(void);
    virtual ~dtkLoggingCategoryPrivate(void);

public:
    bool statusMessageType(const QtMsgType &type);

public:
    bool _enabledDebug;
    bool _enabledWarning;
    bool _enabledCritical;
    bool _registered;
     int _references;
};

// ///////////////////////////////////////////////////////////////////
// dtkLoggingCategory
// ///////////////////////////////////////////////////////////////////

class DTKLOG_EXPORT dtkLoggingCategory
{
    Q_DISABLE_COPY(dtkLoggingCategory)

public:
     dtkLoggingCategory(const char *category);
    ~dtkLoggingCategory(void);

    bool isEnabled(QtMsgType msgtype);

    const char *categoryName(void);

    static dtkLoggingCategory& defaultCategory(void);

private:
    dtkLoggingCategoryPrivate *d_ptr;

    const char *_categoryName;

    friend class dtkLoggingPrivate;
};

// ///////////////////////////////////////////////////////////////////
// dtkLogConfigFilterItem
// ///////////////////////////////////////////////////////////////////

class DTKLOG_EXPORT dtkLogConfigFilterItem
{
public:
    dtkLogConfigFilterItem(const QString &category, bool active);
    int pass(dtkLoggingCategory *log, const QtMsgType &type);
    void parse(void);
    int _type;
    QString _category;
    bool _active;
};

// ///////////////////////////////////////////////////////////////////
// dtkLogging
// ///////////////////////////////////////////////////////////////////

class DTKLOG_EXPORT dtkLoggingPrivate : public QObject
{
    Q_OBJECT

public:
             dtkLoggingPrivate();
    virtual ~dtkLoggingPrivate();

public:
    static QString resolveConfigFile(const QString &path);

public:
    void setLoggingRulesFile(const QString &path);
    void setLoggingRules(const QByteArray &configcontent);
    bool isEnabled(dtkLoggingCategory &category, QtMsgType type);
    void unregisterCategory(dtkLoggingCategory &category);
    bool checkEnvironment() { return _environment; }
    bool registerCategories() { return _registerCategories; }
    dtkLoggingCategoryPrivate *categoryPrivate(dtkLoggingCategory &category);
    void releasePrivate(dtkLoggingCategory &category);

public:
    Q_INVOKABLE void createFileWatcher();

public:
    void readSettings(QIODevice &device);
    void updateCategory(dtkLoggingCategory *log);

signals:
    void configurationChanged();

public slots:
    void fileChanged(const QString &path);

public:
    QFileSystemWatcher *_configFileWatcher;
    QList<dtkLoggingCategory *> _registeredCategories;
    QString _configFile;
    QMutex _mutexRegisteredCategory;
    QList<dtkLogConfigFilterItem> _logConfigItemList;
    bool _environment;
    bool _registerCategories;
    QMutex _privateCategoryObjectsMutex;
    QMap<QString, dtkLoggingCategoryPrivate *> _privateCategoryObjects;
};

// ///////////////////////////////////////////////////////////////////
// Helper functions
// ///////////////////////////////////////////////////////////////////

dtkLoggingPrivate *dtkLogger(void);

/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the logger module of the Qt Toolkit.
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
g** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
****************************************************************************/

//
// dtkLogger_p.h ends here
