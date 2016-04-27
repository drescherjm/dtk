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
## Config
## #################################################################

string(SUBSTRING ${Qt5Core_VERSION_STRING} 0 3 Qt5_VERSION)

set(QT5_DOCUMENTATION_D "${QT5_BINARY_DIR}/../../../Docs/Qt-${Qt5_VERSION}")
set(QT5_QDOC_EXECUTABLE "${QT5_BINARY_DIR}/qdoc")
set(QT5_QHGN_EXECUTABLE "${QT5_BINARY_DIR}/qhelpgenerator")
set(DTK_QDOC_EXECUTABLE "${QT5_BINARY_DIR}/qdoc")

message(STATUS "Using Qt5 binary dir: ${QT5_BINARY_DIR}")
message(STATUS "Using dtk binary doc: ${DTK_QDOC_EXECUTABLE}")
message(STATUS "Using Qt5 binary qhg: ${QT5_QDOC_EXECUTABLE}")

## #################################################################
## Subdirs
## #################################################################

add_subdirectory("slides")

## ###################################################################
## Build tree setup
## ###################################################################

file(COPY cfg DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

## ###################################################################
## dtk
## ###################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dtk/dtk.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtk.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtk-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} -no-link-errors dtk.qdocconf)

## ###################################################################
## dtkMeta
## ###################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dtkMeta/dtkmeta.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkmeta.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkMeta-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtkmeta.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${dtk_INSTALL_DOCS}/dtkmeta/dtkmeta.qhp -o ${dtk_INSTALL_DOCS}/dtkmeta.qch
  COMMENT "-- Generating dtkMeta documentation")

add_dependencies(dtkMeta-doc dtk-doc)

## ###################################################################
## dtkLog
## ###################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dtkLog/dtklog.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtklog.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkLog-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtklog.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${dtk_INSTALL_DOCS}/dtklog/dtklog.qhp -o ${dtk_INSTALL_DOCS}/dtklog.qch
  COMMENT "-- Generating dtkLog documentation")

add_dependencies(dtkLog-doc dtk-doc)

## ###################################################################
## dtkWidgets
## ###################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dtkWidgets/dtkwidgets.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkwidgets.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkWidgets-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtkwidgets.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${dtk_INSTALL_DOCS}/dtkwidgets/dtkwidgets.qhp -o ${dtk_INSTALL_DOCS}/dtkwidgets.qch
  COMMENT "-- Generating dtkWidgets documentation")

add_dependencies(dtkWidgets-doc dtk-widgets)

## ###################################################################
## dtkCore
## ###################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dtkCore/dtkcore.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkcore.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkCore-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtkcore.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${dtk_INSTALL_DOCS}/dtkcore/dtkcore.qhp -o ${dtk_INSTALL_DOCS}/dtkcore.qch
  COMMENT "-- Generating dtkCore documentation")

add_dependencies(dtkCore-doc dtkMeta-doc dtk-doc)

## ###################################################################
## dtkDistributed
## ###################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dtkDistributed/dtkdistributed.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkdistributed.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkDistributed-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtkdistributed.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${dtk_INSTALL_DOCS}/dtkdistributed/dtkdistributed.qhp -o ${dtk_INSTALL_DOCS}/dtkdistributed.qch
  COMMENT "-- Generating dtkDistributed documentation")

add_dependencies(dtkDistributed-doc dtkCore-doc)

## ###################################################################
## dtkComposer
## ###################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dtkComposer/dtkcomposer.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkcomposer.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkComposer-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtkcomposer.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${dtk_INSTALL_DOCS}/dtkcomposer/dtkcomposer.qhp -o ${dtk_INSTALL_DOCS}/dtkcomposer.qch
  COMMENT "-- Generating dtkComposer documentation")

add_dependencies(dtkComposer-doc dtkCore-doc)

## ###################################################################
## ALL
## ###################################################################

add_custom_target(doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtk.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${dtk_INSTALL_DOCS}/dtkdoc/dtkdoc.qhp -o ${dtk_INSTALL_DOCS}/dtkdoc.qch
  COMMENT "-- Generating dtk documentation")

add_dependencies(doc dtkMeta-doc dtkLog-doc dtkWidgets-doc dtkCore-doc dtkDistributed-doc dtkComposer-doc)

######################################################################
### CMakeLists.txt ends here
