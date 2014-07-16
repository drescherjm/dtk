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

get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake LOCATION)

get_filename_component(QT5_BINARY_DIR ${QT5_QMAKE_EXECUTABLE} PATH)

set(QT5_QDOC_EXECUTABLE "${QT5_BINARY_DIR}/qdoc")
set(QT5_QHGN_EXECUTABLE "${QT5_BINARY_DIR}/qhelpgenerator")
set(DTK_QDOC_EXECUTABLE "${CMAKE_BINARY_DIR}/bin/dtkDoc")

message(STATUS "Using Qt5 binary dir: ${QT5_BINARY_DIR}")
message(STATUS "Using dtk binary doc: ${DTK_QDOC_EXECUTABLE}")
message(STATUS "Using Qt5 binary qhg: ${QT5_QDOC_EXECUTABLE}")

## ###################################################################
## dtk
## ###################################################################

configure_file(dtk/dtk.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkdoc.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtk-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} -no-link-errors dtkdoc.qdocconf)

## ###################################################################
## dtkMeta
## ###################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dtkMeta/dtkmeta.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkmeta.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkMeta-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtkmeta.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${CMAKE_BINARY_DIR}/html/dtkmeta/dtkmeta.qhp -o ${CMAKE_BINARY_DIR}/html/dtkmeta.qch
  COMMENT "-- Generating dtkMeta documentation")

add_dependencies(dtkMeta-doc dtk-doc)

## ###################################################################
## dtkCore
## ###################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dtkCore/dtkcore.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkcore.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkCore-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtkcore.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${CMAKE_BINARY_DIR}/html/dtkcore/dtkcore.qhp -o ${CMAKE_BINARY_DIR}/html/dtkcore.qch
  COMMENT "-- Generating dtkCore documentation")

add_dependencies(dtkCore-doc dtkMeta dtk-doc)

## ###################################################################
## dtkDistributed
## ###################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dtkDistributed/dtkdistributed.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkdistributed.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkDistributed-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtkdistributed.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${CMAKE_BINARY_DIR}/html/dtkdistributed/dtkdistributed.qhp -o ${CMAKE_BINARY_DIR}/html/dtkdistributed.qch
  COMMENT "-- Generating dtkDistributed documentation")

add_dependencies(dtkDistributed-doc dtkCore-doc)

## ###################################################################
## dtkWidgets
## ###################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dtkWidgets/dtkwidgets.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkwidgets.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkWidgets-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtkwidgets.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${CMAKE_BINARY_DIR}/html/dtkwidgets/dtkwidgets.qhp -o ${CMAKE_BINARY_DIR}/html/dtkwidgets.qch
  COMMENT "-- Generating dtkWidgets documentation")

add_dependencies(dtkWidgets-doc dtkCore-doc)

## ###################################################################
## ALL
## ###################################################################

add_custom_target(doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtkdoc.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${CMAKE_BINARY_DIR}/html/dtkdoc/dtkdoc.qhp -o ${CMAKE_BINARY_DIR}/html/dtkdoc.qch
  COMMENT "-- Generating dtk documentation")

add_dependencies(doc dtkMeta-doc dtkCore-doc dtkDistributed-doc dtkWidgets-doc)

######################################################################
### CMakeLists.txt ends here
