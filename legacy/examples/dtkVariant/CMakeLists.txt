### CMakeLists.txt --- 
## 
## Author: Thibaud Kloczko, Inria.
## Created: 2012 Fri Oct 26 11:16:52 (+0200)
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkVariant)

## #################################################################
## Build rules
## #################################################################

set(${PROJECT_NAME}_SOURCE_MOC main.moc)

qt4_generate_moc(main.cpp ${CMAKE_CURRENT_BINARY_DIR}/main.moc)

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  main.cpp
  ${${PROJECT_NAME}_SOURCE_MOC})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkMath
  dtkContainer
  dtkGui)
  
