### CMakeLists.txt --- 
## 
## Author: Thibaud Kloczko
## Created: lun. avril  7 19:17:05 2014 (+0200)
## Version: 
## Last-Updated: mer. avril  9 14:19:02 2014 (+0200)
##           By: Thibaud Kloczko
##     Update #: 104
######################################################################
## 
### Change Log:
## 
######################################################################

get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake LOCATION)

get_filename_component(QT5_BINARY_DIR ${QT5_QMAKE_EXECUTABLE} PATH)

message(STATUS "Using Qt5 binary dir:  ${QT5_BINARY_DIR}")
message(STATUS "Using Qt5 binary qdoc: ${QT5_QDOC_EXECUTABLE}")
message(STATUS "Using Qt5 binary qhgn: ${QT5_QHGN_EXECUTABLE}")

set(QT5_DOCUMENTATION_D "${QT5_BINARY_DIR}/../../../Docs/Qt-5.3")
set(QT5_QDOC_EXECUTABLE "${QT5_BINARY_DIR}/qdoc")
set(QT5_QHGN_EXECUTABLE "${QT5_BINARY_DIR}/qhelpgenerator")

set(DTK_QDOC_EXECUTABLE "${CMAKE_BINARY_DIR}/bin/dtkDoc")

## ###################################################################
## dtk
## ###################################################################

configure_file(dtk/dtk.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkdoc.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtk-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} -no-link-errors dtkdoc.qdocconf)

## ###################################################################
## dtkCore
## ###################################################################

configure_file(${CMAKE_SOURCE_DIR}/doc/dtkCore/dtkcore.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkcore.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkCore-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtkcore.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${CMAKE_BINARY_DIR}/html/dtkcore/dtkcore.qhp -o ${CMAKE_BINARY_DIR}/html/dtkcore.qch
  COMMENT "-- Generating dtkCore documentation")

add_dependencies(dtkCore-doc dtk-doc)

## ###################################################################
## dtkDistributed
## ###################################################################

configure_file(${CMAKE_SOURCE_DIR}/doc/dtkDistributed/dtkdistributed.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkdistributed.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkDistributed-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtkdistributed.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${CMAKE_BINARY_DIR}/html/dtkdistributed/dtkdistributed.qhp -o ${CMAKE_BINARY_DIR}/html/dtkdistributed.qch
  COMMENT "-- Generating dtkDistributed documentation")

add_dependencies(dtkDistributed-doc dtkCore-doc)

## ###################################################################
## dtkWidgets
## ###################################################################

configure_file(${CMAKE_SOURCE_DIR}/doc/dtkWidgets/dtkwidgets.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkwidgets.qdocconf IMMEDIATE @ONLY)

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

add_dependencies(doc dtkCore-doc dtkDistributed-doc dtkWidgets-doc)
