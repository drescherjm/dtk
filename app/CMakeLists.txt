## Version: $Id$
##
######################################################################
##
### Commentary:
##
######################################################################
##
### Change Log:
##
######################################################################
##
### Code:

if(DTK_BUILD_COMPOSER)
  add_subdirectory(dtkCreator)
  add_subdirectory(dtkComposerEvaluator)
endif(DTK_BUILD_COMPOSER)

add_subdirectory(dtkDistributedServer)
add_subdirectory(dtkDistributedSlave)
add_subdirectory(dtkDistributedDashboard)
add_subdirectory(dtkDoc)
add_subdirectory(dtkPluginsMetaInfoFetcher)
add_subdirectory(dtkPluginStore)
add_subdirectory(dtkDeploy)

######################################################################
### CMakeLists.txt ends here
