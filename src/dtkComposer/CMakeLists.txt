### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Wed Mar 20 12:26:15 2013 (+0100)
## Version: 
## Last-Updated: Thu Mar 28 16:42:08 2013 (+0100)
##           By: Thibaud Kloczko
##     Update #: 112
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtkComposer)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  # dtkComposer.h
  # dtkComposerCompass.h
  # dtkComposerControls.h
  # dtkComposerControlsDelegate.h
  # dtkComposerEvaluator.h
  # dtkComposerFactory.h
  # dtkComposerFactoryView.h
  # dtkComposerGraph.h
  # dtkComposerGraphEdge.h
  # dtkComposerGraphLayouter.h
  # dtkComposerGraphNode.h
  # dtkComposerGraphNodeBegin.h
  # dtkComposerGraphNodeEnd.h
  # dtkComposerGraphNode.h
  # dtkComposerGraphNodeLeaf.h
  # dtkComposerGraphNodeSelectBranch.h
  # dtkComposerGraphNodeSetInputs.h
  # dtkComposerGraphNodeSetOutputs.h
  # dtkComposerGraphNodeSetVariables.h
  # dtkComposerGraphView.h
  # dtkComposerMachine.h
  # dtkComposerMachineState.h
  dtkComposerNode.h
  # dtkComposerNodeArrayData.h
  # dtkComposerNodeArrayDataExtractor.h
  # dtkComposerNodeArrayDataOperatorModifier.h
  # dtkComposerNodeArrayScalar.h
  # dtkComposerNodeArrayScalarExtractor.h
  # dtkComposerNodeArrayScalarOperatorModifier.h
  # dtkComposerNodeBoolean.h
  # dtkComposerNodeBooleanOperator.h
  dtkComposerNodeComposite.h
  # dtkComposerNodeConstants.h
  dtkComposerNodeControl.h
  # dtkComposerNodeControlCase.h
  # dtkComposerNodeControlDoWhile.h
  # dtkComposerNodeControlIf.h
  # dtkComposerNodeControlFor.h
  # dtkComposerNodeControlForEach.h
  # dtkComposerNodeControlMap.h
  # dtkComposerNodeControlWhile.h
  # dtkComposerNodeData.h
  # dtkComposerNodeFile.h
  # dtkComposerNodeInteger.h
  dtkComposerNodeLeaf.h
  # dtkComposerNodeLeafData.h
  # dtkComposerNodeLeafProcess.h
  # dtkComposerNodeLeafView.h
  # dtkComposerNodeLogger.h
  # dtkComposerNodeMatrixSquareReal.h
  # dtkComposerNodeMatrixSquareRealExtractor.h
  # dtkComposerNodeMatrixSquareRealOperatorUnary.h
  # dtkComposerNodeMatrixSquareRealOperatorBinary.h
  # dtkComposerNodeMetaScalarArray.h
  # dtkComposerNodeMetaScalarArrayAppend.h
  # dtkComposerNodeMetaScalarArrayExtractor.h
  # dtkComposerNodeMetaScalarArrayReplace.h
  # dtkComposerNodeMetaVector3DArray.h
  # dtkComposerNodeMetaVector3DArrayAppend.h
  # dtkComposerNodeMetaVector3DArrayExtractor.h
  # dtkComposerNodeNumberOperator.h
  # dtkComposerNodeProcess.h
  # dtkComposerNodeProxy.h
  # dtkComposerNodeQuaternion.h
  # dtkComposerNodeQuaternionOperatorUnary.h
  # dtkComposerNodeQuaternionOperatorBinary.h
  # dtkComposerNodeReal.h
  # dtkComposerNodeString.h
  # dtkComposerNodeStringOperator.h
  # dtkComposerNodeVector3D.h
  # dtkComposerNodeVector3DOperatorUnary.h
  # dtkComposerNodeVector3DOperatorBinary.h
  # dtkComposerNodeVector3DOperatorTernary.h
  # dtkComposerNodeVectorInteger.h
  # dtkComposerNodeVectorIntegerExtractor.h
  # dtkComposerNodeVectorIntegerOperatorModifier.h
  # dtkComposerNodeVectorIntegerOperatorUnary.h
  # dtkComposerNodeVectorIntegerOperatorBinary.h
  # dtkComposerNodeVectorReal.h
  # dtkComposerNodeVectorRealExtractor.h
  # dtkComposerNodeVectorRealOperatorModifier.h
  # dtkComposerNodeVectorRealOperatorUnary.h
  # dtkComposerNodeVectorRealOperatorBinary.h
  # dtkComposerNodeView.h
  # dtkComposerPath.h
  # dtkComposerScene.h
  # dtkComposerSceneEdge.h
  # dtkComposerSceneModel.h
  # dtkComposerSceneNode.h
  # dtkComposerSceneNodeComposite.h
  # dtkComposerSceneNodeControl.h
  # dtkComposerSceneNodeHandle.h
  # dtkComposerSceneNodeEditor.h
  # dtkComposerSceneNodeLeaf.h
  # dtkComposerSceneNote.h
  # dtkComposerScenePort.h
  # dtkComposerSceneView.h
  # dtkComposerSearchDialog.h
  # dtkComposerStack.h
  # dtkComposerStackCommand.h
  # dtkComposerStackUtils.h
  # dtkComposerStackView.h
  dtkComposerTransmitter.h
  dtkComposerTransmitter_p.h
  dtkComposerTransmitterEmitter.h
  dtkComposerTransmitterEmitter.tpp
  dtkComposerTransmitterHandler.h
  dtkComposerTransmitterHandler.tpp
  dtkComposerTransmitterProxy.h
  dtkComposerTransmitterReceiver.h
  dtkComposerTransmitterReceiver.tpp
  # dtkComposerTransmitterVariant.h
  # dtkComposerType.h
  # dtkComposerVariant.h
  # dtkComposerView.h
  # dtkComposerReader.h
  # dtkComposerWriter.h
)

set(${PROJECT_NAME}_SOURCES
  # dtkComposer.cpp
  # dtkComposerCompass.cpp
  # dtkComposerControls.cpp
  # dtkComposerControlsDelegate.cpp
  # dtkComposerEvaluator.cpp
  # dtkComposerFactory.cpp
  # dtkComposerFactoryView.cpp
  # dtkComposerGraph.cpp
  # dtkComposerGraphEdge.cpp
  # dtkComposerGraphLayouter.cpp
  # dtkComposerGraphNodeBegin.cpp
  # dtkComposerGraphNode.cpp
  # dtkComposerGraphNodeEnd.cpp
  # dtkComposerGraphNodeLeaf.cpp
  # dtkComposerGraphNodeSelectBranch.cpp
  # dtkComposerGraphNodeSetInputs.cpp
  # dtkComposerGraphNodeSetOutputs.cpp
  # dtkComposerGraphNodeSetVariables.cpp
  # dtkComposerGraphView.cpp
  # dtkComposerMachine.cpp
  # dtkComposerMachineState.cpp
  dtkComposerNode.cpp
  # dtkComposerNodeArrayData.cpp
  # dtkComposerNodeArrayDataExtractor.cpp
  # dtkComposerNodeArrayDataOperatorModifier.cpp
  # dtkComposerNodeArrayScalar.cpp
  # dtkComposerNodeArrayScalarExtractor.cpp
  # dtkComposerNodeArrayScalarOperatorModifier.cpp
  # dtkComposerNodeBoolean.cpp
  # dtkComposerNodeBooleanOperator.cpp
  dtkComposerNodeComposite.cpp
  # dtkComposerNodeConstants.cpp
  dtkComposerNodeControl.cpp
  # dtkComposerNodeControlCase.cpp
  # dtkComposerNodeControlDoWhile.cpp
  # dtkComposerNodeControlIf.cpp
  # dtkComposerNodeControlFor.cpp
  # dtkComposerNodeControlForEach.cpp
  # dtkComposerNodeControlMap.cpp
  # dtkComposerNodeControlWhile.cpp
  # dtkComposerNodeData.cpp
  # dtkComposerNodeFile.cpp
  # dtkComposerNodeInteger.cpp
  dtkComposerNodeLeaf.cpp
  # dtkComposerNodeLeafData.cpp
  # dtkComposerNodeLeafProcess.cpp
  # dtkComposerNodeLeafView.cpp
  # dtkComposerNodeLogger.cpp
  # dtkComposerNodeMatrixSquareReal.cpp
  # dtkComposerNodeMatrixSquareRealExtractor.cpp
  # dtkComposerNodeMatrixSquareRealOperatorUnary.cpp
  # dtkComposerNodeMatrixSquareRealOperatorBinary.cpp
  # dtkComposerNodeMetaScalarArray.cpp
  # dtkComposerNodeMetaScalarArrayAppend.cpp
  # dtkComposerNodeMetaScalarArrayExtractor.cpp
  # dtkComposerNodeMetaScalarArrayReplace.cpp
  # dtkComposerNodeMetaVector3DArray.cpp
  # dtkComposerNodeMetaVector3DArrayAppend.cpp
  # dtkComposerNodeMetaVector3DArrayExtractor.cpp
  # dtkComposerNodeNumberOperator.cpp
  # dtkComposerNodeProcess.cpp
  # dtkComposerNodeProxy.cpp
  # dtkComposerNodeQuaternion.cpp
  # dtkComposerNodeQuaternionOperatorUnary.cpp
  # dtkComposerNodeQuaternionOperatorBinary.cpp
  # dtkComposerNodeReal.cpp
  # dtkComposerNodeString.cpp
  # dtkComposerNodeStringOperator.cpp
  # dtkComposerNodeVector3D.cpp
  # dtkComposerNodeVector3DOperatorUnary.cpp
  # dtkComposerNodeVector3DOperatorBinary.cpp
  # dtkComposerNodeVector3DOperatorTernary.cpp
  # dtkComposerNodeVectorInteger.cpp
  # dtkComposerNodeVectorIntegerExtractor.cpp
  # dtkComposerNodeVectorIntegerOperatorModifier.cpp
  # dtkComposerNodeVectorIntegerOperatorUnary.cpp
  # dtkComposerNodeVectorIntegerOperatorBinary.cpp
  # dtkComposerNodeVectorReal.cpp
  # dtkComposerNodeVectorRealExtractor.cpp
  # dtkComposerNodeVectorRealOperatorModifier.cpp
  # dtkComposerNodeVectorRealOperatorUnary.cpp
  # dtkComposerNodeVectorRealOperatorBinary.cpp
  # dtkComposerNodeView.cpp
  # dtkComposerPath.cpp
  # dtkComposerScene.cpp
  # dtkComposerSceneEdge.cpp
  # dtkComposerSceneModel.cpp
  # dtkComposerSceneNode.cpp
  # dtkComposerSceneNodeComposite.cpp
  # dtkComposerSceneNodeControl.cpp
  # dtkComposerSceneNodeHandle.cpp
  # dtkComposerSceneNodeEditor.cpp
  # dtkComposerSceneNodeLeaf.cpp
  # dtkComposerSceneNote.cpp
  # dtkComposerScenePort.cpp
  # dtkComposerSceneView.cpp
  # dtkComposerSearchDialog.cpp
  # dtkComposerStack.cpp
  # dtkComposerStackUtils.cpp
  # dtkComposerStackView.cpp
  # dtkComposerStackCommand.cpp
  dtkComposerTransmitter.cpp
  dtkComposerTransmitterEmitter.cpp
  dtkComposerTransmitterReceiver.cpp
  dtkComposerTransmitterProxy.cpp
  # dtkComposerTransmitterVariant.cpp
  # dtkComposerView.cpp
  # dtkComposerView.cpp
  # dtkComposerReader.cpp
  # dtkComposerWriter.cpp
  )

set(${PROJECT_NAME}_QRC dtkComposer.qrc)

## #################################################################
## Build rules
## #################################################################

qt5_add_resources(${PROJECT_NAME}_QRC ${PROJECT_NAME}_RCC)

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_RCC}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Concurrent)
qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Gui)
qt5_use_modules(${PROJECT_NAME} Network)
qt5_use_modules(${PROJECT_NAME} Widgets)
qt5_use_modules(${PROJECT_NAME} Xml)

target_link_libraries(${PROJECT_NAME} dtkCore)

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
    DESTINATION lib
      COMPONENT composer
         EXPORT dtkDepends)
