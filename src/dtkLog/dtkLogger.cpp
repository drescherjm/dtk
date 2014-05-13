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

#include "dtkLogger.h"
#include "dtkLogger_p.h"

// qDebug truth table
// ---------------------------------------
// Log enabled | Category enabled | do Log
// ---------------------------------------
//  false      | ignore           | true
//  true       | false            | false
//  true       | true             | true

// qWarning truth table
// ---------------------------------------
// Log enabled | Category enabled | do Log
// ---------------------------------------
//  false      | ignore           | true
//  true       | false            | false
//  true       | true             | true

// qCritical truth table
// ---------------------------------------
// Log enabled | Category enabled | do Log
// ---------------------------------------
//  false      | ignore           | true
//  true       | false            | false
//  true       | true             | true

// dtkDebug truth table
// ---------------------------------------
// Log enabled | Category enabled | do Log
// ---------------------------------------
//  false      | ignore           | false
//  true       | false            | false
//  true       | true             | true

// dtkWarning truth table
// ---------------------------------------
// Log enabled | Category enabled | do Log
// ---------------------------------------
//  false      | ignore           | true
//  true       | false            | false
//  true       | true             | true

// dtkCritical truth table
// ---------------------------------------
// Log enabled | Category enabled | do Log
// ---------------------------------------
//  false      | ignore           | true
//  true       | false            | false
//  true       | true             | true

Q_GLOBAL_STATIC(dtkLoggingPrivate, dtkLogging)

static class dtkLoggingCategoryDefault : public dtkLoggingCategory
{
public:
    dtkLoggingCategoryDefault(void) : dtkLoggingCategory("default") {}
} default_dtkLoggingCategory;

/*!
    \class dtkLoggingCategory

    \brief The dtkLoggingCategory class represents a category logging object for the category logging framework.

    Users can create a dtkLoggingCategory object and use it in conjunction with
    dtkDebug, dtkWarning and dtkCritical.
*/

/*!
    Construct a dtkLoggingCategory object with the provided \a category name.
    The object becomes the local identifier for the category.
*/
dtkLoggingCategory::dtkLoggingCategory(const char *category)
    : _categoryName(category)
{
    d_ptr = NULL;
}

/*!
    Returns the category name.
*/
const char* dtkLoggingCategory::categoryName()
{
    return _categoryName;
}

/*!
    \internal Returns the dtkLoggingCategory object used by the qDebug, qWarning and qCritical macros.
*/
dtkLoggingCategory& dtkLoggingCategory::defaultCategory()
{
    return default_dtkLoggingCategory;
}

/*!
    Destruct a dtkLoggingCategory object
*/
dtkLoggingCategory::~dtkLoggingCategory()
{
    if (!d_ptr)
        return;

    dtkLoggingPrivate *qlp = dtkLogging();

    if (!qlp)
        return;

    qlp->releasePrivate(*this);
}

/*!
    Returns true if a message of type \a msgtype will be printed. Returns false otherwise.

    This function may be useful to avoid doing expensive work to generate data that is only used for debug output.

    \code
        // don't run the expensive code if the string won't print
        if (CAT.isEnabled(QtDebugMsg)) {
            QStringList items;
            foreach (obj, list) {
                items << format(obj);
            }
            dtkDebug(CAT) << items;
        }
    \endcode

    Note that the expansion of dtkDebug() prevents arguments from being evaluated if the string won't print so it is not normally required to check isEnabled().

    \code
        // expensive_func is not called if the string won't print
        dtkDebug(CAT) << expensive_func();
    \endcode
*/
bool dtkLoggingCategory::isEnabled(QtMsgType msgtype)
{
    dtkLoggingPrivate *qlp = dtkLogging();

    if (qlp && qlp->registerCategories())
        return dtkLogging()->isEnabled(*this, msgtype);

    if (d_ptr)
        return d_ptr->statusMessageType(msgtype);

    switch (msgtype) {
        case QtDebugMsg: return false;
        case QtWarningMsg: return true;
        case QtCriticalMsg: return true;
        default: break;
    }
    return false;
}

/*!
    \relates dtkLoggingCategory
    Load logging rules from \a path.

    If \a path is relative, QStandardPaths::writeableLocation(QStandardPaths::ConfigLocation) will be prepended.

    Note that if the QT_LOGGING_CONFIG environment variables points to a file, this function does nothing.
    \sa {Activate Logging Rules}
*/
void dtkSetLoggingRulesFile(const QString &path)
{
    dtkLoggingPrivate *qlp = dtkLogging();

    if (!qlp)
        return;

    if (qlp->checkEnvironment())
        return;

    QString config = dtkLoggingPrivate::resolveConfigFile(path);

    if (!config.isEmpty())
        qlp->setLoggingRulesFile(config);
}

/*!
    \relates dtkLoggingCategory
    Set logging \a rules directly.

    This is primarily intended for applications that wish to provide runtime control of their
    logging rather than relying on the user providing a configuration file.

    Note that if the QT_LOGGING_CONFIG environment variables points to a file, this function does nothing.
    \sa {Activate Logging Rules}
*/
void dtkSetLoggingRules(const QByteArray &rules)
{
    dtkLoggingPrivate *qlp = dtkLogging();

    if (!qlp)
        return;

    if (qlp->checkEnvironment())
        return;

    if (!rules.isEmpty())
        qlp->setLoggingRules(rules);
}

/*!
    \relates dtkLoggingCategory
    \macro dtkDebug(cat)
    Works like qDebug() but using category object \a cat.
    Note: this does not process arguments if the string will not be printed so do not rely on side effects.
    \code
    dtkDebug(CAT) << "my message";
    \endcode
    \sa DTK_LOG_CATEGORY(), {Creating Logging Rules}, dtkLoggingCategory
*/

/*!
    \relates dtkLoggingCategory
    \macro dtkWarning(cat)
    Works like qWarning() but using category object \a cat.
    Note: this does not process arguments if the string will not be printed so do not rely on side effects.
    \code
    dtkWarning(CAT) << "my message";
    \endcode
    \sa DTK_LOG_CATEGORY(), {Creating Logging Rules}, dtkLoggingCategory
*/

/*!
    \relates dtkLoggingCategory
    \macro dtkCritical(cat)
    Works like qCritical() but using category object \a cat.
    Note: this does not process arguments if the string will not be printed so do not rely on side effects.
    \code
    dtkCritical(CAT) << "my message";
    \endcode
    \sa DTK_LOG_CATEGORY(), {Creating Logging Rules}, dtkLoggingCategory
*/

/*!
    \relates dtkLoggingCategory
    \macro DTK_LOG_CATEGORY(cat, categoryname)
    Registers a logging category with local identifier \a cat and complete identifier \a categoryname.

    This macro must be used outside of a class or method.
    \sa {Create your Category Logging Object in your Project}, dtkLoggingCategory
*/

/*!
    \internal For Autotest
 */
dtkLoggingPrivate *dtkLogger(void)
{
    dtkLoggingPrivate *qlp = dtkLogging();

    if (!qlp)
        qFatal("Cannot call dtkLogger() because dtkLogging() is 0");

    return qlp;
}

/*!
    \internal
    dtkLoggingPrivate constructor
 */
dtkLoggingPrivate::dtkLoggingPrivate()
    : QObject(0)
    , _configFileWatcher(0)
    , _environment(false)
    , _registerCategories(false)
{
    if (QCoreApplication::instance())
        this->moveToThread(QCoreApplication::instance()->thread());

    categoryPrivate(default_dtkLoggingCategory)->_enabledDebug = true;

    _registeredCategories.append(&default_dtkLoggingCategory);

    QByteArray ba = qgetenv("DTK_LOGGING_CONFIG");

    if (!ba.isEmpty()) {
        QString path = QString::fromLocal8Bit(ba);
        QString config = dtkLoggingPrivate::resolveConfigFile(path);
        if (!config.isEmpty()) {
            _environment = true;
            setLoggingRulesFile(config);
        }
    }
}

/*!
    \internal
    dtkLoggingPrivate destructor
 */
dtkLoggingPrivate::~dtkLoggingPrivate()
{

}

/*!
    \internal
    Returns the resolved version of \a path.
*/
QString dtkLoggingPrivate::resolveConfigFile(const QString &path)
{
    QFileInfo fi(path);

    if (fi.fileName() == path)
        fi.setFile(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + QLatin1Char('/') + path);

    QString config = fi.absoluteFilePath();

    if (QFile::exists(config))
        return config;

    return QString();
}

/*!
    \internal
    Function to set the logging config file.
    This function set the new dtkLogging configuration config file.
    If QT_LOGGING_CONFIG is set this function will do nothing.
*/
void dtkLoggingPrivate::setLoggingRulesFile(const QString &path)
{
    _registerCategories = false;
    _configFile = path;

    if (!_configFileWatcher) {
        QMetaObject::invokeMethod(this, "createFileWatcher");
    }

    QFile cfgfile(_configFile);

    readSettings(cfgfile);
}

/*!
    \internal
    Invokable function to create the System File Watcher on the applicationthread.
*/
void dtkLoggingPrivate::createFileWatcher()
{
    _configFileWatcher = new QFileSystemWatcher(this);

    connect(_configFileWatcher, SIGNAL(fileChanged(QString)), SLOT(fileChanged(QString)));

    QStringList oldfiles = _configFileWatcher->files();

    if (!oldfiles.isEmpty())
        _configFileWatcher->removePaths(oldfiles);
    _configFileWatcher->addPath(_configFile);
}

/*!
    \internal
    Function to set the logging rules.
    This function set the new logging configuration.
    If QT_LOGGING_CONFIG environment vaiable is in use, this function will not make any changes.
*/
void dtkLoggingPrivate::setLoggingRules(const QByteArray &rules)
{
    _registerCategories = false;

    if (_configFileWatcher) {
        delete _configFileWatcher;
        _configFileWatcher = 0;
    }

    QBuffer buffer;
    buffer.setData(rules);
    readSettings(buffer);
}

/*!
    \internal
    Slot for filewatcher
*/
void dtkLoggingPrivate::fileChanged(const QString &path)
{
    if (path == _configFile) {
        QFile cfgfile(_configFile);
        readSettings(cfgfile);
        _configFileWatcher->addPath(path);
    }
}

/*!
    \internal
    Reads the configuration out from a io device.
*/
void dtkLoggingPrivate::readSettings(QIODevice &device)
{
    QMutexLocker locker(&_mutexRegisteredCategory);
    {
        _logConfigItemList.clear();

        if (device.open(QIODevice::ReadOnly)) {
            QByteArray truearray("true");
            QByteArray line;
            while (!device.atEnd()) {
                line = device.readLine().replace(" ", "");
                line = line.simplified();
                const QList<QByteArray> pair = line.split('=');
                if (pair.count() == 2)
                    _logConfigItemList.append(dtkLogConfigFilterItem(QString::fromLatin1(pair.at(0))
                                                     , (pair.at(1).toLower() == truearray)));
            }
        }

        foreach (dtkLoggingCategory *category, _registeredCategories) {
            updateCategory(category);
        }

        _registerCategories = true;
    }
    emit configurationChanged();
}

/*!
    \internal
    Updates all the registered category members against the filter.
*/
void dtkLoggingPrivate::updateCategory(dtkLoggingCategory *log)
{
    dtkLoggingCategoryPrivate *d_ptr = categoryPrivate(*log);

    if (log == &dtkLoggingCategory::defaultCategory()) {
        d_ptr->_enabledDebug = true;
        d_ptr->_enabledWarning = true;
        d_ptr->_enabledCritical = true;
    } else {
        d_ptr->_enabledDebug = false;
        d_ptr->_enabledWarning = true;
        d_ptr->_enabledCritical = true;
    }

    foreach (dtkLogConfigFilterItem item, _logConfigItemList) {

        int filterpass = item.pass(log, QtDebugMsg);

        if (filterpass != 0)
            d_ptr->_enabledDebug = (filterpass > 0);

        filterpass = item.pass(log, QtWarningMsg);

        if (filterpass != 0)
            d_ptr->_enabledWarning = (filterpass > 0);

        filterpass = item.pass(log, QtCriticalMsg);

        if (filterpass != 0)
            d_ptr->_enabledCritical = (filterpass > 0);
    }
}

/*!
    \internal
    Function that checks if the category is enabled and registered the category member if not already registered.
*/
bool dtkLoggingPrivate::isEnabled(dtkLoggingCategory &category, QtMsgType type)
{
    dtkLoggingCategoryPrivate *d_ptr = categoryPrivate(category);

    if (d_ptr->_registered)
        return d_ptr->statusMessageType(type);

    {
        QMutexLocker locker(&_mutexRegisteredCategory);

        updateCategory(&category);
        d_ptr->_registered = true;
       _registeredCategories.append(&category);
    }

    return d_ptr->statusMessageType(type);
}

/*!
    \internal
    Unregister a category object.
*/
void dtkLoggingPrivate::unregisterCategory(dtkLoggingCategory &category)
{
    QMutexLocker locker(&_mutexRegisteredCategory);
    //lock against _logConfigItemList between updateCategory and readSettings
    categoryPrivate(category)->_registered = false;
    _registeredCategories.removeOne(&category);
}

/*!
    \internal
    Returns the private object for \a cat
*/
dtkLoggingCategoryPrivate *dtkLoggingPrivate::categoryPrivate(dtkLoggingCategory &cat)
{
    if (!cat.d_ptr) {

        QMutexLocker locker(&_privateCategoryObjectsMutex);

        if (!cat.d_ptr) {

            QString strcategory;

            if (cat._categoryName)
                strcategory = QString::fromLatin1(cat._categoryName);

            QMap<QString, dtkLoggingCategoryPrivate* >::iterator it = _privateCategoryObjects.find(strcategory);

            if (it != _privateCategoryObjects.end())
                cat.d_ptr = *it;
            else {
                cat.d_ptr = new dtkLoggingCategoryPrivate;
                _privateCategoryObjects.insert(strcategory, cat.d_ptr);
            }
            cat.d_ptr->_references++;
        }
    }

    return cat.d_ptr;
}

/*!
    \internal
    Releases the private object for \a cat
*/
void dtkLoggingPrivate::releasePrivate(dtkLoggingCategory &cat)
{
    QMutexLocker locker1(&_privateCategoryObjectsMutex);

    cat.d_ptr->_references--;

    if (cat.d_ptr->_references == 0) {

        if (cat.d_ptr->_registered)
            unregisterCategory(cat);

        QString strcategory = QString::fromLatin1(cat._categoryName);

        QMap<QString, dtkLoggingCategoryPrivate* >::iterator it = _privateCategoryObjects.find(strcategory);

        if (it != _privateCategoryObjects.end())
            _privateCategoryObjects.remove(strcategory);

        delete cat.d_ptr;
    }
}

/*!
    \fn dtkLoggingPrivate::checkEnvironment()
    \internal
    Returns true if the environment variable is found.
    The first time this is called, the logging rules file pointed to by the
    environment variable will be processed.
*/

/*!
    \fn dtkLoggingPrivate::regsterCategories()
    \internal
    Returns true if category objects should be registered.
    This is primarily used as an optimization to avoid registering
    category objects if no logging config has been specified.
*/

/*!
    \internal Constructor of the private dtkLoggingCategory object
*/
dtkLoggingCategoryPrivate::dtkLoggingCategoryPrivate()
    : _enabledDebug(false)
    , _enabledWarning(true)
    , _enabledCritical(true)
    , _registered(false)
    , _references(0)
{

}

dtkLoggingCategoryPrivate::~dtkLoggingCategoryPrivate()
{

}

/*!
    \internal Returns true if the message type is activated otherwise false;
*/
bool dtkLoggingCategoryPrivate::statusMessageType(const QtMsgType &type)
{
    switch (type) {
        case QtDebugMsg: return _enabledDebug;
        case QtWarningMsg: return _enabledWarning;
        case QtCriticalMsg: return _enabledCritical;
        default:
            break;
    }
    return false;
}

#define INVALID 0x00
#define CATEGORY 0x01
#define LEFTFILTER 0x02
#define RIGHTFILTER 0x04
#define MIDFILTER 0x06

/*!
    \internal
    Constructor of a filter item.
*/
dtkLogConfigFilterItem::dtkLogConfigFilterItem(const QString &category, bool active)
    : _category(category)
    , _active(active)
{
    parse();
}

/*!
    \internal
    Parses the category and check witch kind of wildcard the filter can contain.
    Allowed is f.e.g.:
             fr.inria.*       LEFTFILTER
              *.inria         RIGHTFILTER
              *.inria*        MIDFILTER
 */
void dtkLogConfigFilterItem::parse()
{
    _type = INVALID;

    int index = _category.indexOf(QString::fromLatin1("*"));

    if (index < 0)
        _type |= CATEGORY;
    else {
        if (index == 0) {
            _type |= RIGHTFILTER;
            _category = _category.remove(0, 1);
            index = _category.indexOf(QString::fromLatin1("*"));
        }
        if (index == (_category.length() - 1)) {
            _type |= LEFTFILTER;
            _category = _category.remove(_category.length() - 1, 1);
        }
    }
}

/*!
    \internal
    return value 1 means filter passed, 0 means filter doesn't influence this category, -1 means category doesn't pass this filter
 */
int dtkLogConfigFilterItem::pass(dtkLoggingCategory *log, const QtMsgType &type)
{
    QString fullCategory = QString::fromLatin1(log->categoryName());
    switch (type) {
        case QtDebugMsg:
            fullCategory += QString::fromLatin1(".debug");
        break;
        case QtWarningMsg:
            fullCategory += QString::fromLatin1(".warning");
        break;
        case QtCriticalMsg:
            fullCategory += QString::fromLatin1(".critical");
        break;
        default:
            break;
    }

    if (_type == CATEGORY) {
        if (_category == QString::fromLatin1(log->categoryName()) || _category == fullCategory)
            return (_active ? 1 : -1);
    }

    int idx = 0;
    if (_type == MIDFILTER) {
        idx = fullCategory.indexOf(_category);
        if (idx >= 0)
            return (_active ? 1 : -1);
    } else {
        idx = fullCategory.indexOf(_category);
        if (_type == LEFTFILTER) {
            if (idx == 0)
                return (_active ? 1 : -1);
        } else if (_type == RIGHTFILTER) {
            if (idx == (fullCategory.count() - _category.count()))
                return (_active ? 1 : -1);
        }
    }
    return 0;
}

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
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
****************************************************************************/

//
// dtkLogger.cpp ends here
