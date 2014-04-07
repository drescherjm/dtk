### CMakeLists.txt ---
## 
## Author: Thibaud Kloczko
## Created: lun. avril  7 11:14:31 2014 (+0200)
######################################################################

get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake LOCATION)
get_filename_component(QT5_BINARY_DIR ${QT5_QMAKE_EXECUTABLE} DIRECTORY)

message(STATUS "Using Qt5 binary dir:  ${QT5_BINARY_DIR}")

set(QT5_QDOC_EXECUTABLE "${QT5_BINARY_DIR}/qdoc")
set(QT5_QHGN_EXECUTABLE "${QT5_BINARY_DIR}/qhelpgenerator")

message(STATUS "Using Qt5 binary qdoc: ${QT5_QDOC_EXECUTABLE}")
message(STATUS "Using Qt5 binary qhgn: ${QT5_QHGN_EXECUTABLE}")

## ###################################################################
## dtk
## ###################################################################

configure_file(dtk/dtk.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkdoc.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtk-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${QT5_QDOC_EXECUTABLE} -indexdir ${CMAKE_BINARY_DIR}/html dtkdoc.qdocconf
)

## ###################################################################
## dtkCore
## ###################################################################

configure_file(${CMAKE_SOURCE_DIR}/src/dtkCore/doc/dtkcore.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkcore.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkCore-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${QT5_QDOC_EXECUTABLE} -indexdir ${CMAKE_BINARY_DIR}/html dtkcore.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${CMAKE_BINARY_DIR}/html/dtkcore/dtkcore.qhp
  COMMENT "-- Generating dtkCore documentation")

add_dependencies(dtkCore-doc dtk-doc)

## ###################################################################
## dtkDistributed
## ###################################################################

configure_file(${CMAKE_SOURCE_DIR}/src/dtkDistributed/doc/dtkdistributed.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkdistributed.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkDistributed-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${QT5_QDOC_EXECUTABLE} -indexdir ${CMAKE_BINARY_DIR}/html dtkdistributed.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${CMAKE_BINARY_DIR}/html/dtkdistributed/dtkdistributed.qhp  
  COMMENT "-- Generating dtkDistributed documentation")

add_dependencies(dtkDistributed-doc dtkCore-doc)

## ###################################################################
## dtkWidgets
## ###################################################################

configure_file(${CMAKE_SOURCE_DIR}/src/dtkWidgets/doc/dtkwidgets.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkwidgets.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkWidgets-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${QT5_QDOC_EXECUTABLE} -indexdir ${CMAKE_BINARY_DIR}/html dtkwidgets.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${CMAKE_BINARY_DIR}/html/dtkwidgets/dtkwidgets.qhp  
  COMMENT "-- Generating dtkWidgets documentation")

add_dependencies(dtkWidgets-doc dtkCore-doc)

## ###################################################################
## ALL
## ###################################################################

add_custom_target(doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${QT5_QDOC_EXECUTABLE} -indexdir ${CMAKE_BINARY_DIR}/html dtkdoc.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${CMAKE_BINARY_DIR}/html/dtkdoc/dtkdoc.qhp  
  COMMENT "-- Generating dtk documentation")

add_dependencies(doc dtkWidgets-doc dtkDistributed-doc dtkCore-doc)
