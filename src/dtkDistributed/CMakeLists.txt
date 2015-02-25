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

project(dtkDistributed)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkDistributed
  dtkDistributed.h
  dtkDistributedAbstractApplication.h
  dtkDistributedApplication.h
  dtkDistributedArray
  dtkDistributedArray.h
  dtkDistributedArray.tpp
  dtkDistributedArrayCache
  dtkDistributedArrayCache.h
  dtkDistributedArrayNavigator
  dtkDistributedArrayNavigator.h
  dtkDistributedBufferManager
  dtkDistributedBufferManager.h
  dtkDistributedCommunicator
  dtkDistributedCommunicator.h
  dtkDistributedCommunicatorStatus.h
  dtkDistributedContainer.h
  dtkDistributedController.h
  dtkDistributedCoreApplication.h
  dtkDistributedGraph
  dtkDistributedGraph.h
  dtkDistributedGraph.tpp
  dtkDistributedItem.h
  dtkDistributedIterator
  dtkDistributedIterator.h
  dtkDistributedLocalMessage.h
  dtkDistributedMapper
  dtkDistributedMapper.h
  dtkDistributedMessage.h
  dtkDistributedNavigator
  dtkDistributedNavigator.h
  dtkDistributedPolicy
  dtkDistributedPolicy.h
  dtkDistributedRequest.h
  dtkDistributedResourceManager.h
  dtkDistributedResourceManagerLocal.h
  dtkDistributedResourceManagerOar.h
  dtkDistributedResourceManagerTorque.h
  dtkDistributedStaticArray
  dtkDistributedStaticArray.h
  dtkDistributedStaticArray.tpp
  dtkDistributedServerDaemon.h
  dtkDistributedSettings
  dtkDistributedSettings.h
  dtkDistributedSlave.h
)

set(${PROJECT_NAME}_SOURCES
  dtkDistributed.cpp
  dtkDistributedAbstractApplication.cpp
  dtkDistributedBufferManager.cpp
  dtkDistributedCommunicator.cpp
  dtkDistributedCommunicatorStatus.cpp
  dtkDistributedController.cpp
  dtkDistributedLocalMessage.cpp
  dtkDistributedMapper.cpp
  dtkDistributedMessage.cpp
  dtkDistributedPolicy.cpp
  dtkDistributedResourceManager.cpp
  dtkDistributedResourceManagerLocal.cpp
  dtkDistributedResourceManagerOar.cpp
  dtkDistributedResourceManagerTorque.cpp
  dtkDistributedServerDaemon.cpp
  dtkDistributedSettings.cpp
  dtkDistributedSlave.cpp
)

## #################################################################
## Build rules
## #################################################################

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_RPATH 0)
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH    "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Network)
qt5_use_modules(${PROJECT_NAME} Widgets)
qt5_use_modules(${PROJECT_NAME} Xml)

target_link_libraries(${PROJECT_NAME} dtkCore)
target_link_libraries(${PROJECT_NAME} dtkLog)

## #################################################################
## Export header file
## #################################################################

add_compiler_export_flags()

generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME "${PROJECT_NAME}Export.h")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}"
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export")

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS}
 "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export"
 "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export.h")

## ###################################################################
## Install rules - files
## ###################################################################

install(FILES ${${PROJECT_NAME}_HEADERS}
  DESTINATION include/${PROJECT_NAME}
    COMPONENT distributed)

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT distributed
         EXPORT dtkDepends)

######################################################################
### CMakeLists.txt ends here
