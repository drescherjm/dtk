/* dtkCorePluginManager.cpp ---
 *
 * Author: Thibaud Kloczko
 * Created: jeu. avril  3 08:45:28 2014 (+0200)
 */

/*!
  \class dtkCorePluginManagerPrivate
  \internal
  \brief The dtkCorePluginManagerPrivate class is the private implementation of dtkCorePluginManager.
*/

/*! \fn bool dtkCorePluginManagerPrivate::check(const QString& path)
    \internal
    Checks validity of the plugin library \a path (name, version, dependencies).
*/

/*!
  \class dtkCorePluginManager
  \inmodule dtkCore
  \brief The dtkCorePluginManager class is a template class that handles plugins.
*/

/*! \fn dtkCorePluginManager::dtkCorePluginManager(void)
    Constructs the plugin manager.
*/

/*! \fn dtkCorePluginManager::~dtkCorePluginManager(void)
    Destroys the plugin manager
*/

/*! \fn void dtkCorePluginManager::initialize(const QString& path)
    Scans and loads each plugin library located in directory \a path.

    \sa scan(), load(), uninitialize()
*/

/*! \fn void dtkCorePluginManager::uninitialize(void)
    Unloads all plugin libraries handled by the manager.

    \sa initialize()
*/

/*! \fn void dtkCorePluginManager::scan(const QString& path)
    Scans plugin library \a path and stores plugin metadatas (name, version, dependencies).

    \sa initialize(), load()
*/

/*! \fn void dtkCorePluginManager::setVerboseLoading(bool value)
    Set verbose loading to \a value. If true, the plugin manager will log (using dtkLog) failures at the warn level and normal loading at the trace level

    \sa verboseLoading()
*/

/*! \fn bool dtkCorePluginManager::verboseLoading(void) const
    return current status of verbose loading.

    \sa setVerboseLoading()
*/

/*! \fn void dtkCorePluginManager::load(const QString& path)
    Checks the validity of the plugin library \a path, and if so creates the plugin.

    \sa initialize(), scan(), unload()
 */

/*! \fn void dtkCorePluginManager::unload(const QString& path)
    Destroys the plugin of the plugin library \a path. Destroys the related plugin loader.

    \sa load()
 */

/*! \fn QStringList dtkCorePluginManager::plugins(void)
    Returns all absolute path to all the plugin libraries handled by the manager.
 */
