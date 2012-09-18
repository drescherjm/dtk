### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Thu Sep  8 16:00:59 2011 (+0200)
## Version: $Id$
## Last-Updated: Thu Jul  5 15:48:35 2012 (+0200)
##           By: Julien Wintz
##     Update #: 27
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

install(FILES ${dtk_HEADERS_LAYERS} DESTINATION include/dtk)
install(CODE "execute_process(COMMAND \${CMAKE_BINARY_DIR}/bin/dtkHeadersMover \${CMAKE_INSTALL_PREFIX})")
