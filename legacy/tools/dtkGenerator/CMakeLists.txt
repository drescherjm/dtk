project(dtkGenerator)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
    anyoption.h
    ${PROJECT_NAME}.h
    ${PROJECT_NAME}Wizard.h)

set(${PROJECT_NAME}_HEADERS_MOC
    ${PROJECT_NAME}Wizard.h)

set(${PROJECT_NAME}_SOURCES
    anyoption.cpp
    ${PROJECT_NAME}.cpp
    ${PROJECT_NAME}Wizard.cpp
    main.cpp)

set(${PROJECT_NAME}_RESOURCES
    ${PROJECT_NAME}.qrc)

## #################################################################
## Build rules
## #################################################################

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})
qt4_add_RESOURCES(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_RESOURCES})

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
    ${${PROJECT_NAME}_SOURCES_MOC}
    ${${PROJECT_NAME}_SOURCES_QRC}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS})

target_link_libraries(${PROJECT_NAME}
    ${QT_LIBRARIES})

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_MOC} ${${PROJECT_NAME}_SOURCES_QRC})

## #################################################################
## Bundle setup
## #################################################################

if(APPLE)
    set(MACOSX_BUNDLE_ICON_FILE ${PROJECT_NAME}.icns)
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING 0.0.1)
    set(MACOSX_BUNDLE_VERSION 0.0.1)
    set(MACOSX_BUNDLE_LONG_VERSION_STRING Version 0.0.1)
    set(${PROJECT_NAME}_RESOURCE_DIR ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.app/Contents/Resources)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${${PROJECT_NAME}_RESOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/images/${PROJECT_NAME}.icns ${${PROJECT_NAME}_RESOURCE_DIR})
endif(APPLE)

## #################################################################
## Installation
## #################################################################

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION bin
    RUNTIME DESTINATION bin)

