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

project(dtkConceptGenerator)

## #################################################################
## Sources
## #################################################################

set(CMAKE_AUTOMOC ON)

set(${PROJECT_NAME}_HEADERS
    dtkPluginGeneratorPage.h
    dtkConceptDefinitionPage.h
    dtkConceptGenerator.h
    dtkNewConceptPage.h
    dtkIntroPage.h
    generator.h)

set(${PROJECT_NAME}_SOURCES
    dtkPluginGeneratorPage.cpp
    dtkConceptDefinitionPage.cpp
    dtkConceptGenerator.cpp
    dtkNewConceptPage.cpp
    dtkIntroPage.cpp
    generator.cpp
    main.cpp)

set(${PROJECT_NAME}_UI
    dtkPluginGeneratorPage.ui
    dtkConceptDefinitionPage.ui
    dtkNewConceptPage.ui
    dtkIntroPage.ui)

set(${PROJECT_NAME}_RESOURCES
  templates.qrc)

## #################################################################
## Build rules
## #################################################################

qt5_add_resources(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_RESOURCES})

qt5_wrap_ui(${PROJECT_NAME}_UI_HEADERS ${${PROJECT_NAME}_UI})

add_executable(${PROJECT_NAME} MACOSX_BUNDLE WIN32
  ${${PROJECT_NAME}_UI_HEADERS}
  ${${PROJECT_NAME}_SOURCES_QRC}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

target_link_libraries(${PROJECT_NAME}
  dtkLog
  dtkCore)

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

## #################################################################
## Installation
## #################################################################

set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_RPATH 0)
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH    "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")

install(FILES ${${PROJECT_NAME}_MODULES} DESTINATION modules)
install(TARGETS ${PROJECT_NAME}
   BUNDLE DESTINATION bin
  RUNTIME DESTINATION bin)

######################################################################
### CMakeLists.txt ends here
