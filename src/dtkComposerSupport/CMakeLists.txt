### CMakeLists.txt ---
##
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
######################################################################
##
### Commentary:
##
######################################################################
##
### Change log:
##
######################################################################

project(dtkComposerSupport)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkComposer.h
  dtkComposer_p.h
  dtkComposerCompass.h
  dtkComposerControls.h
  dtkComposerControlsDelegate.h
  dtkComposerControlsListItem.h
  dtkComposerControlsListItemFactory.h
  dtkComposerControlsListItemBoolean.h
  dtkComposerControlsListItemFile.h
  dtkComposerControlsListItemInteger.h
  dtkComposerControlsListItemLeafProcess.h
  dtkComposerControlsListItemReal.h
  dtkComposerControlsListItemString.h
  dtkComposerEvaluator.h
  dtkComposerEvaluator_p.h
  dtkComposerFactory.h
  dtkComposerFactoryView.h
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
  dtkComposerMachine.h
  dtkComposerMachineState.h
  dtkComposerMetatype.h
  dtkComposerNode.h
  dtkComposerNodeArrayData.h
  dtkComposerNodeArrayDataExtractor.h
  dtkComposerNodeArrayDataOperatorModifier.h
  dtkComposerNodeArrayScalar.h
  dtkComposerNodeArrayScalarExtractor.h
  dtkComposerNodeArrayScalarOperatorModifier.h
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
  dtkComposerNodeData.h
  dtkComposerNodeFile.h
  dtkComposerNodeFile_p.h
  dtkComposerNodeInteger.h
  dtkComposerNodeLeaf.h
  dtkComposerNodeLeafActor.h
  dtkComposerNodeLeafData.h
  dtkComposerNodeLeafProcess.h
  dtkComposerNodeLeafView.h
  dtkComposerNodeLogger.h
  dtkComposerNodeMatrixSquareReal.h
  dtkComposerNodeMatrixSquareRealExtractor.h
  dtkComposerNodeMatrixSquareRealOperatorUnary.h
  dtkComposerNodeMatrixSquareRealOperatorBinary.h
  dtkComposerNodeMetaScalarArray.h
  dtkComposerNodeMetaScalarArrayAppend.h
  dtkComposerNodeMetaScalarArrayExtractor.h
  dtkComposerNodeMetaScalarArrayReplace.h
  dtkComposerNodeMetaVector3DArray.h
  dtkComposerNodeMetaVector3DArrayAppend.h
  dtkComposerNodeMetaVector3DArrayExtractor.h
  dtkComposerNodeNumberOperator.h
  dtkComposerNodePrint.h
  dtkComposerNodeProcess.h
  dtkComposerNodeProxy.h
  dtkComposerNodeQuaternion.h
  dtkComposerNodeQuaternionOperatorUnary.h
  dtkComposerNodeQuaternionOperatorBinary.h
  dtkComposerNodeReal.h
  dtkComposerNodeString.h
  dtkComposerNodeStringOperator.h
  dtkComposerNodeVector3D.h
  dtkComposerNodeVector3DOperatorUnary.h
  dtkComposerNodeVector3DOperatorBinary.h
  dtkComposerNodeVector3DOperatorTernary.h
  dtkComposerNodeVectorInteger.h
  dtkComposerNodeVectorIntegerExtractor.h
  dtkComposerNodeVectorIntegerOperatorModifier.h
  dtkComposerNodeVectorIntegerOperatorUnary.h
  dtkComposerNodeVectorIntegerOperatorBinary.h
  dtkComposerNodeVectorReal.h
  dtkComposerNodeVectorRealExtractor.h
  dtkComposerNodeVectorRealOperatorModifier.h
  dtkComposerNodeVectorRealOperatorUnary.h
  dtkComposerNodeVectorRealOperatorBinary.h
  dtkComposerNodeView.h
  dtkComposerPath.h
  dtkComposerScene.h
  dtkComposerSceneEdge.h
  dtkComposerSceneModel.h
  dtkComposerSceneNode.h
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
  dtkComposerTransmitterAbstractEmitter.h
  dtkComposerTransmitterAbstractReceiver.h
  dtkComposerTransmitterEmitter.h
  dtkComposerTransmitterEmitter.tpp
  dtkComposerTransmitterProxy.h
  dtkComposerTransmitterReceiver.h
  dtkComposerTransmitterReceiver.tpp
  dtkComposerTransmitterVariant.h
  dtkComposerTransmitterVariant_p.h
  dtkComposerTransmitterVariant.tpp
  dtkComposerView.h
  dtkComposerReader.h
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
  dtkComposerControlsListItemLeafProcess.cpp
  dtkComposerControlsListItemReal.cpp
  dtkComposerControlsListItemString.cpp
  dtkComposerEvaluator.cpp
  dtkComposerFactory.cpp
  dtkComposerFactoryView.cpp
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
  dtkComposerMachine.cpp
  dtkComposerMachineState.cpp
  dtkComposerNode.cpp
  dtkComposerNodeArrayData.cpp
  dtkComposerNodeArrayDataExtractor.cpp
  dtkComposerNodeArrayDataOperatorModifier.cpp
  dtkComposerNodeArrayScalar.cpp
  dtkComposerNodeArrayScalarExtractor.cpp
  dtkComposerNodeArrayScalarOperatorModifier.cpp
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
  dtkComposerNodeData.cpp
  dtkComposerNodeFile.cpp
  dtkComposerNodeInteger.cpp
  dtkComposerNodeLeaf.cpp
  dtkComposerNodeLeafActor.cpp
  dtkComposerNodeLeafData.cpp
  dtkComposerNodeLeafProcess.cpp
  dtkComposerNodeLeafView.cpp
  dtkComposerNodeLogger.cpp
  dtkComposerNodeMatrixSquareReal.cpp
  dtkComposerNodeMatrixSquareRealExtractor.cpp
  dtkComposerNodeMatrixSquareRealOperatorUnary.cpp
  dtkComposerNodeMatrixSquareRealOperatorBinary.cpp
  dtkComposerNodeMetaScalarArray.cpp
  dtkComposerNodeMetaScalarArrayAppend.cpp
  dtkComposerNodeMetaScalarArrayExtractor.cpp
  dtkComposerNodeMetaScalarArrayReplace.cpp
  dtkComposerNodeMetaVector3DArray.cpp
  dtkComposerNodeMetaVector3DArrayAppend.cpp
  dtkComposerNodeMetaVector3DArrayExtractor.cpp
  dtkComposerNodeNumberOperator.cpp
  dtkComposerNodePrint.cpp
  dtkComposerNodeProcess.cpp
  dtkComposerNodeProxy.cpp
  dtkComposerNodeQuaternion.cpp
  dtkComposerNodeQuaternionOperatorUnary.cpp
  dtkComposerNodeQuaternionOperatorBinary.cpp
  dtkComposerNodeReal.cpp
  dtkComposerNodeString.cpp
  dtkComposerNodeStringOperator.cpp
  dtkComposerNodeVector3D.cpp
  dtkComposerNodeVector3DOperatorUnary.cpp
  dtkComposerNodeVector3DOperatorBinary.cpp
  dtkComposerNodeVector3DOperatorTernary.cpp
  dtkComposerNodeVectorInteger.cpp
  dtkComposerNodeVectorIntegerExtractor.cpp
  dtkComposerNodeVectorIntegerOperatorModifier.cpp
  dtkComposerNodeVectorIntegerOperatorUnary.cpp
  dtkComposerNodeVectorIntegerOperatorBinary.cpp
  dtkComposerNodeVectorReal.cpp
  dtkComposerNodeVectorRealExtractor.cpp
  dtkComposerNodeVectorRealOperatorModifier.cpp
  dtkComposerNodeVectorRealOperatorUnary.cpp
  dtkComposerNodeVectorRealOperatorBinary.cpp
  dtkComposerNodeView.cpp
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
  dtkComposerStackUtils.cpp
  dtkComposerStackView.cpp
  dtkComposerStackCommand.cpp
  dtkComposerTransmitter.cpp
  dtkComposerTransmitterAbstractEmitter.cpp
  dtkComposerTransmitterAbstractReceiver.cpp
  dtkComposerTransmitterEmitter.cpp
  dtkComposerTransmitterProxy.cpp
  dtkComposerTransmitterVariant.cpp
  dtkComposerView.cpp
  dtkComposerView.cpp
  dtkComposerReader.cpp
  dtkComposerWriter.cpp)

set(${PROJECT_NAME}_RESOURCES dtkComposer.qrc)

## #################################################################
## 
## #################################################################

if(DTK_BUILD_DISTRIBUTED_SUPPORT)
  set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
   dtkComposerEvaluatorSlave.h
   dtkComposerNodeRemote.h
   dtkComposerNodeRemote_p.h
   dtkComposerNodeDistributed.h)
  set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
    dtkComposerNodeRemote.h)
  set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkComposerEvaluatorSlave.cpp
  dtkComposerNodeDistributed.cpp
  dtkComposerNodeRemote.cpp)
endif(DTK_BUILD_DISTRIBUTED_SUPPORT)

## #################################################################
## Video sources
## #################################################################

if(DTK_HAVE_FFMPEG AND DTK_BUILD_VIDEO)
  set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
    dtkComposerNodeMovieWriter.h)
  set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC})
  set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
    dtkComposerNodeMovieWriter.cpp)
endif(DTK_HAVE_FFMPEG AND DTK_BUILD_VIDEO)

## #################################################################
## Mpi sources
## #################################################################

if(DTK_HAVE_MPI AND DTK_BUILD_DISTRIBUTED_SUPPORT)
set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkComposerEvaluatorProcess.h
  dtkComposerNodeSpawn.h
  dtkComposerNodeSpawn_p.h
  dtkComposerNodeWorld.h)
set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
  dtkComposerEvaluatorProcess.h
  dtkComposerNodeSpawn.h)
set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkComposerEvaluatorProcess.cpp
  dtkComposerNodeSpawn.cpp
  dtkComposerNodeWorld.cpp)
endif(DTK_HAVE_MPI AND DTK_BUILD_DISTRIBUTED_SUPPORT)

## #################################################################
## Kinect sources
## #################################################################

if(DTK_HAVE_NITE AND DTK_BUILD_VR)
set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkComposerNodeTrackerKinect.h)
set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC})
set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkComposerNodeTrackerKinect.cpp)
endif(DTK_HAVE_NITE AND DTK_BUILD_VR)

## #################################################################
## Plot sources
## #################################################################

if(DTK_HAVE_PLOT AND DTK_BUILD_PLOT)
set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkComposerNodePlotCurve.h
  dtkComposerNodePlotCurveFile.h
  dtkComposerNodePlotCurveAppendPoint.h
  dtkComposerNodePlotView.h)
set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
  dtkComposerNodePlotCurve.h
  dtkComposerNodePlotCurveFile.h
  dtkComposerNodePlotCurveAppendPoint.h
  dtkComposerNodePlotView.h)
set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkComposerNodePlotCurve.cpp
  dtkComposerNodePlotCurveFile.cpp
  dtkComposerNodePlotCurveAppendPoint.cpp
  dtkComposerNodePlotView.cpp)
endif(DTK_HAVE_PLOT AND DTK_BUILD_PLOT)

## #################################################################
## Vrpn sources
## #################################################################

if(DTK_HAVE_VRPN AND DTK_BUILD_VR)
set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
  dtkComposerNodeTrackerVrpn.h)
set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC})
set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
  dtkComposerNodeTrackerVrpn.cpp)
endif(DTK_HAVE_VRPN AND DTK_BUILD_VR)


## #################################################################
## Build rules
## #################################################################

add_definitions(-DQSTATEMACHINE_DEBUG)


add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
)

target_link_libraries(${PROJECT_NAME}
  dtkMathSupport
  dtkContainerSupport
  dtkCoreSupport
  dtkGuiSupport
  dtkLog
  )

if(DTK_BUILD_DISTRIBUTED_SUPPORT)
  target_link_libraries(${PROJECT_NAME} dtkDistributedSupport)
endif(DTK_BUILD_DISTRIBUTED_SUPPORT)

if(DTK_HAVE_NITE OR DTK_HAVE_VRPN AND DTK_BUILD_VR)
  target_link_libraries(${PROJECT_NAME} dtkVr)
endif(DTK_HAVE_NITE OR DTK_HAVE_VRPN AND DTK_BUILD_VR)

if(DTK_BUILD_PLOT_SUPPORT)
  target_link_libraries(${PROJECT_NAME} dtkPlotSupport)
endif(DTK_BUILD_PLOT_SUPPORT)

if(DTK_HAVE_FFMPEG AND DTK_BUILD_VIDEO)
  target_link_libraries(${PROJECT_NAME} dtkVideo)
endif(DTK_HAVE_FFMPEG AND DTK_BUILD_VIDEO)

qt5_use_modules(${PROJECT_NAME} Concurrent)
qt5_use_modules(${PROJECT_NAME} Network)
qt5_use_modules(${PROJECT_NAME} Widgets)
qt5_use_modules(${PROJECT_NAME} Xml)

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
 "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export.h")

## #################################################################
## Installation
## #################################################################

foreach(header ${${PROJECT_NAME}_HEADERS})
  string(REGEX REPLACE "(.*)\\.h\$" "\\1" h ${header})
  set(${PROJECT_NAME}_HEADERS_QTS "${${PROJECT_NAME}_HEADERS_QTS}" ${h})
endforeach(header)

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_HEADERS_QTS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
