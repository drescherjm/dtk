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

project(dtkComposer)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkComposer.h
  dtkComposerCompass.h
  dtkComposerControls.h
  dtkComposerControlsDelegate.h
  dtkComposerControlsListItem.h
  dtkComposerControlsListItemFactory.h
  dtkComposerControlsListItemBoolean.h
  dtkComposerControlsListItemFile.h
  dtkComposerControlsListItemInteger.h
  # dtkComposerControlsListItemLeafProcess.h
  dtkComposerControlsListItemReal.h
  dtkComposerControlsListItemString.h
  dtkComposerEvaluator.h
  dtkComposerEvaluator_p.h
  dtkComposerGraph.h
  dtkComposerGraphEdge.h
  dtkComposerGraphLayouter.h
  dtkComposerGraphNode.h
  dtkComposerGraphNodeBegin.h
  dtkComposerGraphNodeEnd.h
  dtkComposerGraphNode.h
  dtkComposerGraphNodeLeaf.h
  dtkComposerGraphNodeSelectBranch.h
  dtkComposerGraphNodeSetInputs.h
  dtkComposerGraphNodeSetOutputs.h
  dtkComposerGraphNodeSetVariables.h
  dtkComposerGraphView.h
  dtkComposerMetaType.h
  dtkComposerNode.h
  dtkComposerNodeFactory.h
  dtkComposerNodeFactoryView.h
  dtkComposerNodeBoolean.h
  dtkComposerNodeBooleanOperator.h
  dtkComposerNodeComposite.h
  dtkComposerNodeConstants.h
  dtkComposerNodeControl.h
  dtkComposerNodeControlCase.h
  dtkComposerNodeControlDoWhile.h
  dtkComposerNodeControlIf.h
  dtkComposerNodeControlFor.h
  dtkComposerNodeControlForEach.h
  dtkComposerNodeControlMap.h
  dtkComposerNodeControlWhile.h
  dtkComposerNodeFile.h
  dtkComposerNodeFile_p.h
  dtkComposerNodeInteger.h
  dtkComposerNodeLeaf.h
  # dtkComposerNodeLeafData.h
  # dtkComposerNodeLeafProcess.h
  # dtkComposerNodeLeafView.h
  dtkComposerNodeLogger.h
  dtkComposerNodeNumberOperator.h
  dtkComposerNodeProxy.h
  dtkComposerNodeReal.h
  dtkComposerNodeRemote.h
  dtkComposerNodeString.h
  dtkComposerNodeStringOperator.h
  dtkComposerPath.h
  dtkComposerScene.h
  dtkComposerScene_p.h
  dtkComposerSceneEdge.h
  dtkComposerSceneModel.h
  dtkComposerSceneNode.h
  dtkComposerSceneNode_p.h
  dtkComposerSceneNodeComposite.h
  dtkComposerSceneNodeControl.h
  dtkComposerSceneNodeHandle.h
  dtkComposerSceneNodeEditor.h
  dtkComposerSceneNodeEditor_p.h
  dtkComposerSceneNodeLeaf.h
  dtkComposerSceneNote.h
  dtkComposerScenePort.h
  dtkComposerSceneView.h
  dtkComposerSearchDialog.h
  dtkComposerStack.h
  dtkComposerStackCommand.h
  dtkComposerStackUtils.h
  dtkComposerStackView.h
  dtkComposerTransmitter.h
  dtkComposerTransmitter_p.h
  dtkComposerTransmitterEmitter.h
  dtkComposerTransmitterEmitter.tpp
  dtkComposerTransmitterHandler.h
  dtkComposerTransmitterHandler.tpp
  dtkComposerTransmitterProxy.h
  dtkComposerTransmitterProxyLoop.h
  dtkComposerTransmitterProxyLoop.tpp
  dtkComposerTransmitterReceiver.h
  dtkComposerTransmitterReceiver.tpp
  dtkComposerView.h
  dtkComposerReader.h
  dtkComposerWidget.h
  dtkComposerWriter.h)

set(${PROJECT_NAME}_SOURCES
  dtkComposer.cpp
  dtkComposerCompass.cpp
  dtkComposerControls.cpp
  dtkComposerControlsDelegate.cpp
  dtkComposerControlsListItem.cpp
  dtkComposerControlsListItemBoolean.cpp
  dtkComposerControlsListItemFactory.cpp
  dtkComposerControlsListItemFile.cpp
  dtkComposerControlsListItemInteger.cpp
  # dtkComposerControlsListItemLeafProcess.cpp
  dtkComposerControlsListItemReal.cpp
  dtkComposerControlsListItemString.cpp
  dtkComposerEvaluator.cpp
  dtkComposerGraph.cpp
  dtkComposerGraphEdge.cpp
  dtkComposerGraphLayouter.cpp
  dtkComposerGraphNodeBegin.cpp
  dtkComposerGraphNode.cpp
  dtkComposerGraphNodeEnd.cpp
  dtkComposerGraphNodeLeaf.cpp
  dtkComposerGraphNodeSelectBranch.cpp
  dtkComposerGraphNodeSetInputs.cpp
  dtkComposerGraphNodeSetOutputs.cpp
  dtkComposerGraphNodeSetVariables.cpp
  dtkComposerGraphView.cpp
  dtkComposerNode.cpp
  dtkComposerNodeFactory.cpp
  dtkComposerNodeFactoryView.cpp
  dtkComposerNodeBoolean.cpp
  dtkComposerNodeBooleanOperator.cpp
  dtkComposerNodeComposite.cpp
  dtkComposerNodeConstants.cpp
  dtkComposerNodeControl.cpp
  dtkComposerNodeControlCase.cpp
  dtkComposerNodeControlDoWhile.cpp
  dtkComposerNodeControlIf.cpp
  dtkComposerNodeControlFor.cpp
  dtkComposerNodeControlForEach.cpp
  dtkComposerNodeControlMap.cpp
  dtkComposerNodeControlWhile.cpp
  dtkComposerNodeFile.cpp
  dtkComposerNodeInteger.cpp
  dtkComposerNodeLeaf.cpp
  # dtkComposerNodeLeafData.cpp
  # dtkComposerNodeLeafProcess.cpp
  # dtkComposerNodeLeafView.cpp
  dtkComposerNodeLogger.cpp
  dtkComposerNodeNumberOperator.cpp
  dtkComposerNodeProxy.cpp
  dtkComposerNodeReal.cpp
  dtkComposerNodeRemote.cpp
  dtkComposerNodeString.cpp
  dtkComposerNodeStringOperator.cpp
  dtkComposerPath.cpp
  dtkComposerScene.cpp
  dtkComposerSceneEdge.cpp
  dtkComposerSceneModel.cpp
  dtkComposerSceneNode.cpp
  dtkComposerSceneNodeComposite.cpp
  dtkComposerSceneNodeControl.cpp
  dtkComposerSceneNodeHandle.cpp
  dtkComposerSceneNodeEditor.cpp
  dtkComposerSceneNodeLeaf.cpp
  dtkComposerSceneNote.cpp
  dtkComposerScenePort.cpp
  dtkComposerSceneView.cpp
  dtkComposerSearchDialog.cpp
  dtkComposerStack.cpp
  dtkComposerStackCommand.cpp
  dtkComposerStackUtils.cpp
  dtkComposerStackView.cpp
  dtkComposerTransmitter.cpp
  dtkComposerTransmitterEmitter.cpp
  dtkComposerTransmitterReceiver.cpp
  dtkComposerTransmitterProxy.cpp
  dtkComposerTransmitterProxyLoop.cpp
  dtkComposerView.cpp
  dtkComposerReader.cpp
  dtkComposerWidget.cpp
  dtkComposerWriter.cpp)

set(${PROJECT_NAME}_QRC dtkComposer.qrc)

## #################################################################
## Build rules
## #################################################################

qt5_add_resources(${PROJECT_NAME}_QRC ${PROJECT_NAME}_RCC)

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_RCC}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_RPATH 0)
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH    "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Concurrent)
qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Gui)
qt5_use_modules(${PROJECT_NAME} Network)
qt5_use_modules(${PROJECT_NAME} Widgets)
qt5_use_modules(${PROJECT_NAME} Xml)

target_link_libraries(${PROJECT_NAME} dtkLog)
target_link_libraries(${PROJECT_NAME} dtkCore)
target_link_libraries(${PROJECT_NAME} dtkWidgets)

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
    COMPONENT composer)

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT composer
         EXPORT dtkDepends)

######################################################################
### CMakeLists.txt ends here
