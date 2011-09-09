### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Thu Sep  8 16:00:59 2011 (+0200)
## Version: $Id$
## Last-Updated: Thu Sep  8 16:54:41 2011 (+0200)
##           By: Julien Wintz
##     Update #: 22
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

file(GLOB dtk_HEADERS_LAYERS "*")

message(${dtk_HEADERS_LAYERS})

list(REMOVE_AT dtk_HEADERS_LAYERS 0)

message(${dtk_HEADERS_LAYERS})

install(FILES ${dtk_HEADERS_LAYERS} DESTINATION includes)
install(CODE "execute_process(COMMAND \${CMAKE_BINARY_DIR}/bin/dtkHeadersMover \${CMAKE_INSTALL_PREFIX})")
