### CMakeLists.txt ---
##
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Se
## Last-Updated: Sat Aug  4 00:33:05 2012 (+0200)
##           By: tkloczko
##     Update #: 583
######################################################################
##
### Commentary:
##
######################################################################
##
### Change log:
##
######################################################################

project(dtkComposer)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkComposer.h
  dtkComposerCompass.h
  dtkComposerEvaluator.h
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
  dtkComposerNodeContainerData.h
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
  dtkComposerNodeFileOperator.h
  dtkComposerNodeInteger.h
  dtkComposerNodeLeaf.h
  dtkComposerNodeLeafData.h
  dtkComposerNodeLeafProcess.h
  dtkComposerNodeLeafView.h
  dtkComposerNodeList.h
  dtkComposerNodeListOperator.h
  dtkComposerNodeLogger.h
  dtkComposerNodeMatrixSquareReal.h
  dtkComposerNodeMatrixSquareRealExtractor.h
  dtkComposerNodeMatrixSquareRealOperatorUnary.h
  dtkComposerNodeMatrixSquareRealOperatorBinary.h
  dtkComposerNodeNumberOperator.h
  dtkComposerNodeProcess.h
  dtkComposerNodeProxy.h
  dtkComposerNodeQuaternion.h
  dtkComposerNodeQuaternionOperatorUnary.h
  dtkComposerNodeQuaternionOperatorBinary.h
  dtkComposerNodeReal.h
  dtkComposerNodeRemote.h
  dtkComposerNodeString.h
  dtkComposerNodeStringOperator.h
  dtkComposerNodeVector.h
  dtkComposerNodeVectorOperator.h
  dtkComposerNodeVector3D.h
  dtkComposerNodeVector3DOperatorUnary.h
  dtkComposerNodeVector3DOperatorBinary.h
  dtkComposerNodeVector3DOperatorTernary.h
  dtkComposerNodeVectorReal.h
  dtkComposerNodeVectorRealExtractor.h
  dtkComposerNodeVectorRealOperatorModifier.h
  dtkComposerNodeVectorRealOperatorUnary.h
  dtkComposerNodeVectorRealOperatorBinary.h
  dtkComposerNodeView.h
  dtkComposerScene.h
  dtkComposerSceneEdge.h
  dtkComposerSceneModel.h
  dtkComposerSceneNode.h
  dtkComposerSceneNodeComposite.h
  dtkComposerSceneNodeControl.h
  dtkComposerSceneNodeEditor.h
  dtkComposerSceneNodeLeaf.h
  dtkComposerSceneNote.h
  dtkComposerScenePort.h
  dtkComposerSceneView.h
  dtkComposerStack.h
  dtkComposerStackCommand.h
  dtkComposerStackUtils.h
  dtkComposerStackView.h
  dtkComposerTransmitter.h
  dtkComposerTransmitter_p.h
  dtkComposerTransmitterEmitter.h
  dtkComposerTransmitterEmitter.tpp
  dtkComposerTransmitterProxy.h
  dtkComposerTransmitterReceiver.h
  dtkComposerTransmitterReceiver.tpp
  dtkComposerTransmitterVariant.h
  dtkComposerView.h
  dtkComposerReader.h
  dtkComposerWriter.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkComposer.h
  dtkComposer_p.h
  dtkComposerCompass.h
  dtkComposerEvaluator.h
  dtkComposerFactory.h
  dtkComposerFactoryView.h
  dtkComposerGraph.h
  dtkComposerGraphView.h
  dtkComposerMachine.h
  dtkComposerMachineState.h
  dtkComposerNodeRemote.h
  dtkComposerNodeView.h
  dtkComposerSceneModel.h
  dtkComposerScene.h
  dtkComposerSceneNodeEditor.h
  dtkComposerSceneNodeEditor_p.h
  dtkComposerSceneView.h
  dtkComposerStackView.h
  dtkComposerView.h)

set(${PROJECT_NAME}_SOURCES
  dtkComposer.cpp
  dtkComposerCompass.cpp
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
  # dtkComposerNodeArrayData.cpp
  # dtkComposerNodeArrayDataExtractor.cpp
  # dtkComposerNodeArrayDataOperatorModifier.cpp
  # dtkComposerNodeArrayScalar.cpp
  # dtkComposerNodeArrayScalarExtractor.cpp
  # dtkComposerNodeArrayScalarOperatorModifier.cpp
  dtkComposerNodeBoolean.cpp
  dtkComposerNodeBooleanOperator.cpp
  dtkComposerNodeComposite.cpp
  dtkComposerNodeConstants.cpp
  # dtkComposerNodeContainerData.cpp
  dtkComposerNodeControl.cpp
  dtkComposerNodeControlCase.cpp
  dtkComposerNodeControlDoWhile.cpp
  dtkComposerNodeControlIf.cpp
  dtkComposerNodeControlFor.cpp
  dtkComposerNodeControlForEach.cpp
  dtkComposerNodeControlMap.cpp
  dtkComposerNodeControlWhile.cpp
  # dtkComposerNodeData.cpp
  # dtkComposerNodeFile.cpp
  # dtkComposerNodeFileOperator.cpp
  dtkComposerNodeInteger.cpp
  dtkComposerNodeLeaf.cpp
  dtkComposerNodeLeafData.cpp
  dtkComposerNodeLeafProcess.cpp
  dtkComposerNodeLeafView.cpp
  # dtkComposerNodeList.cpp
  # dtkComposerNodeListOperator.cpp
  dtkComposerNodeLogger.cpp
  # dtkComposerNodeMatrixSquareReal.cpp
  # dtkComposerNodeMatrixSquareRealExtractor.cpp
  # dtkComposerNodeMatrixSquareRealOperatorUnary.cpp
  # dtkComposerNodeMatrixSquareRealOperatorBinary.cpp
  dtkComposerNodeNumberOperator.cpp
  # dtkComposerNodeProcess.cpp
  dtkComposerNodeProxy.cpp
  # dtkComposerNodeQuaternion.cpp
  # dtkComposerNodeQuaternionOperatorUnary.cpp
  # dtkComposerNodeQuaternionOperatorBinary.cpp
  dtkComposerNodeReal.cpp
  dtkComposerNodeRemote.cpp
  dtkComposerNodeString.cpp
  dtkComposerNodeStringOperator.cpp
  # dtkComposerNodeVector.cpp
  # dtkComposerNodeVectorOperator.cpp
  # dtkComposerNodeVector3D.cpp
  # dtkComposerNodeVector3DOperatorUnary.cpp
  # dtkComposerNodeVector3DOperatorBinary.cpp
  # dtkComposerNodeVector3DOperatorTernary.cpp
  # dtkComposerNodeVectorReal.cpp
  # dtkComposerNodeVectorRealExtractor.cpp
  # dtkComposerNodeVectorRealOperatorModifier.cpp
  # dtkComposerNodeVectorRealOperatorUnary.cpp
  # dtkComposerNodeVectorRealOperatorBinary.cpp
  dtkComposerNodeView.cpp
  dtkComposerScene.cpp
  dtkComposerSceneEdge.cpp
  dtkComposerSceneModel.cpp
  dtkComposerSceneNode.cpp
  dtkComposerSceneNodeComposite.cpp
  dtkComposerSceneNodeControl.cpp
  dtkComposerSceneNodeEditor.cpp
  dtkComposerSceneNodeLeaf.cpp
  dtkComposerSceneNote.cpp
  dtkComposerScenePort.cpp
  dtkComposerSceneView.cpp
  dtkComposerStack.cpp
  dtkComposerStackUtils.cpp
  dtkComposerStackView.cpp
  dtkComposerStackCommand.cpp
  dtkComposerTransmitter.cpp
  dtkComposerTransmitterProxy.cpp
  dtkComposerTransmitterVariant.cpp
  dtkComposerView.cpp
  dtkComposerView.cpp
  dtkComposerReader.cpp
  dtkComposerWriter.cpp)

set(${PROJECT_NAME}_RESOURCES dtkComposer.qrc)

# ## #################################################################
# ## Mpi sources
# ## #################################################################

# if(DTK_HAVE_MPI)
# set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
#   dtkComposerNodeDistributed.h
#   dtkComposerNodeWorld.h)
# set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC})
# set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
#   dtkComposerNodeDistributed.cpp
#   dtkComposerNodeWorld.cpp)
# endif(DTK_HAVE_MPI)

# ## #################################################################
# ## Kinect sources
# ## #################################################################

# if(DTK_HAVE_NITE)
# set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
#   dtkComposerNodeTrackerKinect.h)
# set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC})
# set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
#   dtkComposerNodeTrackerKinect.cpp)
# endif(DTK_HAVE_NITE)

# ## #################################################################
# ## Plot sources
# ## #################################################################

# if(DTK_HAVE_PLOT)
# set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
#   dtkComposerNodePlotCurve.h
#   dtkComposerNodePlotView.h)
# set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC}
#   dtkComposerNodePlotCurve.h
#   dtkComposerNodePlotView.h)
# set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
#   dtkComposerNodePlotCurve.cpp
#   dtkComposerNodePlotView.cpp)
# endif(DTK_HAVE_PLOT)

# ## #################################################################
# ## Vrpn sources
# ## #################################################################

# if(DTK_HAVE_VRPN)
# set(${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
#   dtkComposerNodeTrackerVrpn.h)
# set(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS_MOC})
# set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES}
#   dtkComposerNodeTrackerVrpn.cpp)
# endif()

## #################################################################
## Build rules
## #################################################################

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
if(NOT MSVC)
  add_definitions(-DQT_NO_DEBUG)
endif(NOT MSVC)

add_definitions(-DQSTATEMACHINE_DEBUG)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})
qt4_add_RESOURCES(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_RESOURCES})

if(DTK_USE_PRECOMPILED_HEADERS)
  add_precompiled_header(${PROJECT_NAME}_SOURCES_PCH 
    "dtkPch/dtkPch.h" "../dtkPch/dtkPch.cpp" 
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_SOURCES_MOC}
    ${${PROJECT_NAME}_SOURCES_QRC})
endif(DTK_USE_PRECOMPILED_HEADERS)

if(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_PCH}
  ${${PROJECT_NAME}_SOURCES_QRC})

else(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} STATIC
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_PCH}
  ${${PROJECT_NAME}_SOURCES_QRC})

endif(BUILD_SHARED_LIBS)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkMath
  dtkContainer
  dtkCore
  dtkGui
  dtkLog
  dtkNotification
  dtkDistributed)

if(DTK_HAVE_NITE OR DTK_HAVE_VRPN)
target_link_libraries(${PROJECT_NAME} dtkVr)
endif(DTK_HAVE_NITE OR DTK_HAVE_VRPN)

if(DTK_HAVE_PLOT)
target_link_libraries(${PROJECT_NAME} dtkPlot)
endif(DTK_HAVE_PLOT)

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
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_MOC})

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
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
