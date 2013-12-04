### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Thu Sep  8 16:00:59 2011 (+0200)
## Version: $Id$
## Last-Updated: mer. déc.  4 14:02:49 2013 (+0100)
##           By: Nicolas Niclausse
##     Update #: 144
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

## #################################################################
## Installation
## #################################################################

file(GLOB dtk_HEADERS_LAYERS "dtk*")

list(REMOVE_AT dtk_HEADERS_LAYERS 0)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/headers)

foreach (headerFile ${dtk_HEADERS_LAYERS})
  FILE(READ ${headerFile} FILE_CONTENT)
  get_filename_component(Header ${headerFile} NAME)
  STRING(REGEX REPLACE "../src" ".."
    MODIFIED_FILE_CONTENT "${FILE_CONTENT}")
  FILE(WRITE  ${CMAKE_BINARY_DIR}/headers/${Header} "${MODIFIED_FILE_CONTENT}")
endforeach (headerFile)

file(GLOB dtk_HEADERS_LAYERS_MODIFIED "${CMAKE_BINARY_DIR}/headers/dtk*")

install(FILES ${dtk_HEADERS_LAYERS_MODIFIED} DESTINATION include/dtk)


