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

if(DTK_BUILD_DISTRIBUTED)
  add_subdirectory(dtkDistributedServer)
  add_subdirectory(dtkDistributedSlave)
  add_subdirectory(dtkDistributedDashboard)
endif(DTK_BUILD_DISTRIBUTED)

add_subdirectory(dtkPluginsMetaInfoFetcher)
add_subdirectory(dtkDeploy)
add_subdirectory(dtkConceptGenerator)

######################################################################
### CMakeLists.txt ends here
