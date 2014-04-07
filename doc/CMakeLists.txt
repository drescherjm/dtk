### CMakeLists.txt ---
## 
## Author: Thibaud Kloczko
## Created: lun. avril  7 11:14:31 2014 (+0200)
######################################################################

## ###################################################################
## dtkCore
## ###################################################################

configure_file(${CMAKE_SOURCE_DIR}/src/dtkCore/doc/dtkcore.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkcore.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkCore-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND /home/tkloczko/Development/qt/5.3/gcc_64/bin/qdoc -indexdir ${CMAKE_BINARY_DIR}/html dtkcore.qdocconf
  COMMAND /home/tkloczko/Development/qt/5.3/gcc_64/bin/qhelpgenerator ${CMAKE_BINARY_DIR}/html/dtkcore/dtkcore.qhp
  COMMENT "-- Generating dtkCore documentation")

## ###################################################################
## dtkDistributed
## ###################################################################

configure_file(${CMAKE_SOURCE_DIR}/src/dtkDistributed/doc/dtkdistributed.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkdistributed.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkDistributed-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND /home/tkloczko/Development/qt/5.3/gcc_64/bin/qdoc -indexdir ${CMAKE_BINARY_DIR}/html dtkdistributed.qdocconf
  COMMAND /home/tkloczko/Development/qt/5.3/gcc_64/bin/qhelpgenerator ${CMAKE_BINARY_DIR}/html/dtkdistributed/dtkdistributed.qhp  
  COMMENT "-- Generating dtkDistributed documentation")

add_dependencies(dtkDistributed-doc dtkCore-doc)

## ###################################################################
## dtkWidgets
## ###################################################################

configure_file(${CMAKE_SOURCE_DIR}/src/dtkWidgets/doc/dtkwidgets.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkwidgets.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkWidgets-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND /home/tkloczko/Development/qt/5.3/gcc_64/bin/qdoc -indexdir ${CMAKE_BINARY_DIR}/html dtkwidgets.qdocconf
  COMMAND /home/tkloczko/Development/qt/5.3/gcc_64/bin/qhelpgenerator ${CMAKE_BINARY_DIR}/html/dtkwidgets/dtkwidgets.qhp  
  COMMENT "-- Generating dtkWidgets documentation")

add_dependencies(dtkWidgets-doc dtkCore-doc)

## ###################################################################
## ALL
## ###################################################################

configure_file(dtk/dtk.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkdoc.qdocconf IMMEDIATE @ONLY)

add_custom_target(doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND /home/tkloczko/Development/qt/5.3/gcc_64/bin/qdoc -indexdir ${CMAKE_BINARY_DIR}/html dtkdoc.qdocconf
  COMMAND /home/tkloczko/Development/qt/5.3/gcc_64/bin/qdoc -indexdir ${CMAKE_BINARY_DIR}/html dtkcore.qdocconf
  COMMAND /home/tkloczko/Development/qt/5.3/gcc_64/bin/qdoc -indexdir ${CMAKE_BINARY_DIR}/html dtkdistributed.qdocconf
  COMMAND /home/tkloczko/Development/qt/5.3/gcc_64/bin/qdoc -indexdir ${CMAKE_BINARY_DIR}/html dtkwidgets.qdocconf
  COMMAND /home/tkloczko/Development/qt/5.3/gcc_64/bin/qhelpgenerator ${CMAKE_BINARY_DIR}/html/dtkdoc/dtkdoc.qhp  
  COMMENT "-- Generating dtk documentation")

add_dependencies(doc dtkWidgets-doc dtkDistributed-doc dtkCore-doc)