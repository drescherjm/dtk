### dtk-iOS-device.toolchain.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008-2011 - Julien Wintz, Inria.
## Created: Wed Nov 16 22:09:38 2011 (+0100)
## Version: $Id$
## Last-Updated: Thu Nov 17 00:11:08 2011 (+0100)
##           By: Julien Wintz
##     Update #: 12
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

include(CMakeForceCompiler)

set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_SYSTEM_NAME "Darwin")
set(CMAKE_SYSTEM_PROCESSOR "arm")

set(DTK_IOS_SDKVER "5.0")
set(DTK_IOS_DEVROOT "/Developer/Platforms/iPhoneOS.platform/Developer")
set(DTK_IOS_SDKROOT "/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS${DTK_IOS_SDKVER}.sdk")
set(DTK_IOS_CC  "${DTK_IOS_DEVROOT}/usr/bin/gcc")
set(DTK_IOS_CXX "${DTK_IOS_DEVROOT}/usr/bin/g++")

cmake_force_c_compiler  (${DTK_IOS_CC}  GNU)
cmake_force_cxx_compiler(${DTK_IOS_CXX} GNU)

set(CMAKE_FIND_ROOT_PATH "${DTK_IOS_SDKROOT}" "${DTK_IOS_DEVROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
