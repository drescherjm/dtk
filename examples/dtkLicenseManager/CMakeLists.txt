### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Thu Jan  7 14:26:51 2010 (+0100)
## Version: $Id$
## Last-Updated: Tue Apr  6 09:19:15 2010 (+0200)
##           By: Julien Wintz
##     Update #: 6
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkLicenseManager)

## #################################################################
## Build rules
## #################################################################

if(OPENSSL_FOUND)

add_executable(${PROJECT_NAME}
  main.cpp)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCrypto)

endif(OPENSSL_FOUND)
