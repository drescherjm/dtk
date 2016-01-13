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

## #################################################################
## Essential layer
## #################################################################

add_subdirectory(dtk)
add_subdirectory(dtkCore)

if(DTK_BUILD_COMPOSER)
  add_subdirectory(dtkComposer)
  add_subdirectory(dtkMonitoring)
endif(DTK_BUILD_COMPOSER)

if(DTK_BUILD_DISTRIBUTED)
  add_subdirectory(dtkDistributed)
endif(DTK_BUILD_DISTRIBUTED)

if(DTK_BUILD_SCRIPT)
  add_subdirectory(dtkScript)
endif(DTK_BUILD_SCRIPT)

add_subdirectory(dtkLog)
add_subdirectory(dtkMath)
add_subdirectory(dtkMeta)
add_subdirectory(dtkTest)
add_subdirectory(dtkWidgets)

## #################################################################
## Essential target
## #################################################################

set(DTK_TARGETS)
set(DTK_TARGETS ${DTK_TARGETS} dtkCore)

if(DTK_BUILD_COMPOSER)
  set(DTK_TARGETS ${DTK_TARGETS} dtkComposer)
  set(DTK_TARGETS ${DTK_TARGETS} dtkMonitoring)
endif(DTK_BUILD_COMPOSER)

if(DTK_BUILD_DISTRIBUTED)
  set(DTK_TARGETS ${DTK_TARGETS} dtkDistributed)
endif(DTK_BUILD_DISTRIBUTED)

if(DTK_BUILD_SCRIPT)
  set(DTK_TARGETS ${DTK_TARGETS} dtkScript)
endif(DTK_BUILD_SCRIPT)

set(DTK_TARGETS ${DTK_TARGETS} dtkLog)
set(DTK_TARGETS ${DTK_TARGETS} dtkMath)
set(DTK_TARGETS ${DTK_TARGETS} dtkMeta)
set(DTK_TARGETS ${DTK_TARGETS} dtkWidgets)

## #################################################################
## Support layer
## #################################################################

if(DTK_BUILD_SUPPORT_COMPOSER)
  add_subdirectory(dtkComposerSupport)
endif(DTK_BUILD_SUPPORT_COMPOSER)

if(DTK_BUILD_SUPPORT_CORE)
  add_subdirectory(dtkCoreSupport)
endif(DTK_BUILD_SUPPORT_CORE)

if(DTK_BUILD_SUPPORT_CONTAINER)
  add_subdirectory(dtkContainerSupport)
endif(DTK_BUILD_SUPPORT_CONTAINER)

if(DTK_BUILD_SUPPORT_DISTRIBUTED)
  add_subdirectory(dtkDistributedSupport)
endif(DTK_BUILD_SUPPORT_DISTRIBUTED)

if(DTK_BUILD_SUPPORT_GUI)
  add_subdirectory(dtkGuiSupport)
endif(DTK_BUILD_SUPPORT_GUI)

if(DTK_BUILD_SUPPORT_MATH)
  add_subdirectory(dtkMathSupport)
endif(DTK_BUILD_SUPPORT_MATH)

if(DTK_BUILD_SUPPORT_PLOT)
  add_subdirectory(dtkPlotSupport)
endif(DTK_BUILD_SUPPORT_PLOT)

if(DTK_BUILD_SUPPORT_VR)
  add_subdirectory(dtkVrSupport)
endif(DTK_BUILD_SUPPORT_VR)

## #################################################################
## Support targets
## #################################################################

if(DTK_BUILD_SUPPORT_CORE)
  set(DTK_TARGETS ${DTK_TARGETS} dtkCoreSupport)
endif(DTK_BUILD_SUPPORT_CORE)

if(DTK_BUILD_SUPPORT_CONTAINER)
  set(DTK_TARGETS ${DTK_TARGETS} dtkContainerSupport)
endif(DTK_BUILD_SUPPORT_CONTAINER)

if(DTK_BUILD_SUPPORT_COMPOSER)
  set(DTK_TARGETS ${DTK_TARGETS} dtkComposerSupport)
endif(DTK_BUILD_SUPPORT_COMPOSER)

if(DTK_BUILD_SUPPORT_DISTRIBUTED)
  set(DTK_TARGETS ${DTK_TARGETS} dtkDistributedSupport)
endif(DTK_BUILD_SUPPORT_DISTRIBUTED)

if(DTK_BUILD_SUPPORT_GUI)
  set(DTK_TARGETS ${DTK_TARGETS} dtkGuiSupport)
endif(DTK_BUILD_SUPPORT_GUI)

if(DTK_BUILD_SUPPORT_MATH)
  set(DTK_TARGETS ${DTK_TARGETS} dtkMathSupport)
endif(DTK_BUILD_SUPPORT_MATH)

if(DTK_BUILD_SUPPORT_PLOT)
  set(DTK_TARGETS ${DTK_TARGETS} dtkPlotSupport)
endif(DTK_BUILD_SUPPORT_PLOT)

if(DTK_BUILD_SUPPORT_VR)
  set(DTK_TARGETS ${DTK_TARGETS} dtkVrSupport)
endif(DTK_BUILD_SUPPORT_VR)

## #################################################################
## Target export
## #################################################################

export(TARGETS ${DTK_TARGETS} FILE "${CMAKE_BINARY_DIR}/dtkDepends.cmake")

######################################################################
### CMakeLists.txt ends here
