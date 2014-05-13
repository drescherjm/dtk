### CMakeLists.txt --- 

project(dtkMeta)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkMeta
  dtkMeta.h
  dtkMeta.tpp
  dtkMetaContainerSequential_p.h
  dtkMetaContainerSequential_p.tpp
  dtkMetaContainerSequential.h
  dtkMetaContainerSequential.tpp)

set(${PROJECT_NAME}_SOURCES
  dtkMetaContainerSequential.cpp)

## #################################################################
## Build rules
## #################################################################

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Core)

## ###################################################################
## Install rules - files
## ###################################################################

install(FILES ${${PROJECT_NAME}_HEADERS}
  DESTINATION include/${PROJECT_NAME}
    COMPONENT meta)

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT meta
         EXPORT dtkDepends)
