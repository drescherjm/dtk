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
  add_subdirectory(dtkComposerEvaluator)
endif(DTK_BUILD_COMPOSER)

if(DTK_BUILD_DISTRIBUTED AND DTK_BUILD_WIDGETS)
  add_subdirectory(dtkDistributedServer)
  add_subdirectory(dtkDistributedSlave)
  add_subdirectory(dtkDistributedDashboard)
endif(DTK_BUILD_DISTRIBUTED  AND DTK_BUILD_WIDGETS)

add_subdirectory(dtkPluginsMetaInfoFetcher)
add_subdirectory(dtkDeploy)

if(DTK_BUILD_SUPPORT_GUI)
  add_subdirectory(dtkConceptGenerator)
endif(DTK_BUILD_SUPPORT_GUI)

######################################################################
### CMakeLists.txt ends here
