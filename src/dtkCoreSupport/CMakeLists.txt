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

project(dtkCoreSupport)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkAbstractData.h
  dtkAbstractData_p.h
  dtkAbstractDataFactory.h
  dtkAbstractDataReader.h
  dtkAbstractDataReader_p.h
  dtkAbstractDataDeserializer.h
  dtkAbstractDataDeserializer_p.h
  dtkAbstractDataSerializer.h
  dtkAbstractDataSerializer_p.h
  dtkAbstractDataWriter.h
  dtkAbstractDataWriter_p.h
  dtkAbstractDataComposite.h
  dtkAbstractDataComposite.tpp
  dtkAbstractDataConverter.h
  dtkAbstractDataConverter_p.h
  dtkAbstractFactory.h
  dtkAbstractObject.h
  dtkAbstractObject_p.h
  dtkAbstractProcess.h
  dtkAbstractProcess_p.h
  dtkAbstractProcessController.h
  dtkAbstractProcessFactory.h
  dtkAbstractView.h
  dtkAbstractView_p.h
  dtkAbstractViewAnimator.h
  dtkAbstractViewAnimator_p.h
  dtkAbstractViewFactory.h
  dtkAbstractViewInteractor.h
  dtkAbstractViewInteractor_p.h
  dtkAbstractViewNavigator.h
  dtkAbstractViewNavigator_p.h
  dtkCpuid.h
  dtkGlobal.h
  dtkPlugin.h
  dtkPlugin_p.h
  dtkPluginManager.h
  dtkUpdater.h
  dtkUpdater_p.h
  dtkSignalBlocker.h
  dtkSingleton.h
  dtkSingletonDeclare.h
  dtkSmartPointer.h
  dtkTest.h)

set(${PROJECT_NAME}_SOURCES
  dtkAbstractDataFactory.cpp
  dtkAbstractData.cpp
  dtkAbstractDataReader.cpp
  dtkAbstractDataSerializer.cpp
  dtkAbstractDataDeserializer.cpp
  dtkAbstractDataWriter.cpp
  dtkAbstractDataComposite.cpp
  dtkAbstractDataConverter.cpp
  dtkAbstractFactory.cpp
  dtkAbstractObject.cpp
  dtkAbstractProcessFactory.cpp
  dtkAbstractProcess.cpp
  dtkAbstractProcessController.cpp
  dtkAbstractViewFactory.cpp
  dtkAbstractView.cpp
  dtkAbstractViewAnimator.cpp
  dtkAbstractViewInteractor.cpp
  dtkAbstractViewNavigator.cpp
  dtkCpuid.cpp
  dtkPlugin.cpp
  dtkPluginManager.cpp
  dtkSignalBlocker.h
  dtkSingleton.cpp
  dtkSingletonDeclare.cpp
  dtkSmartPointer.cpp
  dtkUpdater.cpp)

## #################################################################
## Wrapping
## #################################################################

set(${PROJECT_NAME}_SOURCES_WRAP)

if(DTK_BUILD_WRAPPERS AND SWIG_FOUND)

  set(${PROJECT_NAME}_WRAP_DEPENDS ${${PROJECT_NAME}_HEADERS})

  option(DTK_WRAPPING_PYTHON    "Build python wrapper" OFF)
  option(DTK_WRAPPING_TCL       "Build TCL wrapper" OFF)
  option(DTK_WRAPPING_CSHARP    "Build C# wrapper" OFF)

  if (DTK_WRAPPING_PYTHON)
    if (PYTHONLIBS_FOUND)
      dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP dtkcoresupport python ${PROJECT_SOURCE_DIR}/dtkCoreSupport.i ${${PROJECT_NAME}_WRAP_DEPENDS})
    endif()
  endif()

  if (DTK_WRAPPING_TCL)
    if (TCL_FOUND)
      dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP dtkcoresupport tcl ${PROJECT_SOURCE_DIR}/dtkCoreSupport.i ${${PROJECT_NAME}_WRAP_DEPENDS})
    endif()
  endif()

  if (DTK_WRAPPING_CSHARP)
    dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP dtkcoresupport csharp ${PROJECT_SOURCE_DIR}/dtkCoreSupport.i ${${PROJECT_NAME}_WRAP_DEPENDS})
  endif()
endif()

## #################################################################
## Build rules
## #################################################################

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_SOURCES_WRAP}
  ${${PROJECT_NAME}_HEADERS})

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Network)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

target_link_libraries(${PROJECT_NAME}
  dtkLog
  dtkMathSupport)

if(DTK_BUILD_WRAPPERS AND SWIG_FOUND)

 if (DTK_WRAPPING_TCL AND TCL_FOUND)
   target_link_libraries(${PROJECT_NAME} ${TCL_LIBRARY})
 endif()

  if(DTK_WRAPPING_PYTHON AND PYTHONLIBS_FOUND)
      target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
  endif()

endif(DTK_BUILD_WRAPPERS AND SWIG_FOUND)

## #################################################################
## Target properties
## #################################################################

set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_RPATH 0)
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH    "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")

## #################################################################
## Export header file
## #################################################################

add_compiler_export_flags()

generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME "${PROJECT_NAME}Export.h")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}"
  COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export")

## #################################################################
## Handling of generated script modules
## #################################################################

set(${PROJECT_NAME}_MODULES)

if(DTK_BUILD_WRAPPERS AND SWIG_FOUND)

  if(DTK_WRAPPING_PYTHON AND PYTHONLIBS_FOUND )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      DEPENDS ${PROJECT_SOURCE_DIR}/dtkCoreSupport.i
      COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/modules
      COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${${PROJECT_NAME}_BINARY_DIR}/dtkcoresupport.py ${CMAKE_BINARY_DIR}/modules
      COMMENT "-- Moving python modules to ${CMAKE_BINARY_DIR}/modules")

    set(${PROJECT_NAME}_MODULES ${CMAKE_BINARY_DIR}/modules/dtkcoresupport.py)

    if(APPLE)
      add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        DEPENDS ${PROJECT_SOURCE_DIR}/dtkCoreSupport.i
        COMMAND ln -sf ../lib/libdtkCoreSupport.dylib _dtkcoresupport.so
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/modules)

      set(${PROJECT_NAME}_MODULES ${${PROJECT_NAME}_MODULES} ${CMAKE_BINARY_DIR}/modules/_dtkcoresupport.so)
    endif(APPLE)

    if(UNIX AND NOT APPLE)
      add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        DEPENDS ${PROJECT_SOURCE_DIR}/dtkCoreSupport.i
        COMMAND ln -fs ../${CMAKE_INSTALL_LIBDIR}/libdtkCoreSupport.so _dtkcoresupport.so
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/modules)

      set(${PROJECT_NAME}_MODULES ${${PROJECT_NAME}_MODULES} ${CMAKE_BINARY_DIR}/modules/_dtkcoresupport.so)
    endif(UNIX AND NOT APPLE)

  endif(DTK_WRAPPING_PYTHON AND PYTHONLIBS_FOUND )

  if (DTK_WRAPPING_CSHARP)

    file(GLOB DTK_CSHARP_SOURCES "${${PROJECT_NAME}_BINARY_DIR}/*.cs")

    foreach(DTK_CSHARP_SOURCE ${DTK_CSHARP_SOURCES})
      add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        DEPENDS ${PROJECT_SOURCE_DIR}/dtkCoreSupport.i
        COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${DTK_CSHARP_SOURCE} ${CMAKE_BINARY_DIR}/modules
        COMMENT "-- Moving csharp ${DTK_CSHARP_SOURCE} source to ${CMAKE_BINARY_DIR}/modules")
    endforeach(DTK_CSHARP_SOURCE ${DTK_CSHARP_SOURCES})
  endif (DTK_WRAPPING_CSHARP)

endif(DTK_BUILD_WRAPPERS AND SWIG_FOUND)

## #################################################################
## Installation
## #################################################################

foreach(header ${${PROJECT_NAME}_HEADERS})
  string(REGEX REPLACE "(.*)\\.h\$" "\\1" h ${header})
  set(${PROJECT_NAME}_HEADERS_QTS "${${PROJECT_NAME}_HEADERS_QTS}" ${h})
endforeach(header)

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS}
 "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h")

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_HEADERS_QTS} DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_MODULES} DESTINATION modules)

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT coresupport
         EXPORT dtkDepends)

######################################################################
### CMakeLists.txt ends here
