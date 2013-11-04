### FindFFmpeg.cmake ---
## 
## Author: Julien Wintz
## Created: Mon Oct 21 10:21:28 2013 (+0200)
## Version: 
## Last-Updated: Mon Nov  4 15:15:46 2013 (+0100)
##           By: Selim Kraria
##     Update #: 67
######################################################################
## 
### Change Log:
## 
######################################################################

# - Try to find ffmpeg
# Once done this will define
#
#  FFMPEG_FOUND - system has ffmpeg
#  FFMPEG_INCLUDE_DIRS - the ffmpeg include directory
#  FFMPEG_LIBRARIES - Link these to use ffmpeg
#  FFMPEG_DEFINITIONS - Compiler switches required for using ffmpeg
#
#  Copyright (c) 2008 Andreas Schneider <mail@cynapses.org>
#  Modified for other libraries by Lasse Kärkkäinen <tronic>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.

include(FindPackageHandleStandardArgs)
include(GetPrerequisites)

if(FFMPEG_LIBRARIES AND FFMPEG_INCLUDE_DIRS)
  set(FFMPEG_FOUND TRUE)
else(FFMPEG_LIBRARIES AND FFMPEG_INCLUDE_DIRS)
  find_package(PkgConfig)
  if(PKG_CONFIG_FOUND)
    pkg_check_modules(_FFMPEG_AVCODEC libavcodec QUIET)
    pkg_check_modules(_FFMPEG_AVDEVICE libavdevice QUIET)
    pkg_check_modules(_FFMPEG_AVFILTER libavfilter QUIET)
    pkg_check_modules(_FFMPEG_AVFORMAT libavformat QUIET)
    pkg_check_modules(_FFMPEG_AVUTIL libavutil QUIET)
    pkg_check_modules(_FFMPEG_SWRESAMPLE libswresample QUIET)
    pkg_check_modules(_FFMPEG_SWSCALE libswscale QUIET)
  endif(PKG_CONFIG_FOUND)

  find_path(FFMPEG_AVCODEC_INCLUDE_DIR
    NAMES avcodec.h
    PATHS $ENV{FFMPEG_DIR}/include ${_FFMPEG_AVCODEC_INCLUDE_DIRS} /usr/include /usr/local/include /opt/local/include
    PATH_SUFFIXES ffmpeg libavcodec)

  find_path(FFMPEG_AVDEVICE_INCLUDE_DIR
    NAMES avdevice.h
    PATHS $ENV{FFMPEG_DIR}/include ${_FFMPEG_AVDEVICE_INCLUDE_DIRS} /usr/include /usr/local/include /opt/local/include /sw/include
    PATH_SUFFIXES ffmpeg libavdevice)

  find_path(FFMPEG_AVFILTER_INCLUDE_DIR
    NAMES avfilter.h
    PATHS $ENV{FFMPEG_DIR}/include ${_FFMPEG_AVFILTER_INCLUDE_DIRS} /usr/include /usr/local/include /opt/local/include /sw/include
    PATH_SUFFIXES ffmpeg libavfilter)

  find_path(FFMPEG_AVFORMAT_INCLUDE_DIR
    NAMES avformat.h
    PATHS $ENV{FFMPEG_DIR}/include ${_FFMPEG_AVFORMAT_INCLUDE_DIRS} /usr/include /usr/local/include /opt/local/include /sw/include
    PATH_SUFFIXES ffmpeg libavformat)

  find_path(FFMPEG_AVUTIL_INCLUDE_DIR
    NAMES avutil.h
    PATHS $ENV{FFMPEG_DIR}/include ${_FFMPEG_AVUTIL_INCLUDE_DIRS} /usr/include /usr/local/include /opt/local/include /sw/include
    PATH_SUFFIXES ffmpeg libavutil)

  find_path(FFMPEG_SWRESAMPLE_INCLUDE_DIR
    NAMES swresample.h
    PATHS $ENV{FFMPEG_DIR}/include ${_FFMPEG_SWRESAMPLE_INCLUDE_DIRS} /usr/include /usr/local/include /opt/local/include /sw/include
    PATH_SUFFIXES ffmpeg libswresample)

  find_path(FFMPEG_SWSCALE_INCLUDE_DIR
    NAMES swscale.h
    PATHS $ENV{FFMPEG_DIR}/include ${_FFMPEG_SWSCALE_INCLUDE_DIRS} /usr/include /usr/local/include /opt/local/include /sw/include
    PATH_SUFFIXES ffmpeg libswscale)

  find_library(FFMPEG_AVCODEC_LIBRARY
    NAMES avcodec
    PATHS $ENV{FFMPEG_DIR}/lib NO_DEFAULT_PATH)
  find_library(FFMPEG_AVCODEC_LIBRARY
    NAMES avcodec
    PATHS ${_FFMPEG_AVCODEC_LIBRARY_DIRS} /usr/lib /usr/local/lib /opt/local/lib /sw/lib)

  find_library(FFMPEG_AVDEVICE_LIBRARY
    NAMES avdevice
    PATHS $ENV{FFMPEG_DIR}/lib NO_DEFAULT_PATH)
  find_library(FFMPEG_AVDEVICE_LIBRARY
    NAMES avdevice
    PATHS ${_FFMPEG_AVDEVICE_LIBRARY_DIRS} /usr/lib /usr/local/lib /opt/local/lib /sw/lib)

  find_library(FFMPEG_AVFILTER_LIBRARY
    NAMES avfilter
    PATHS $ENV{FFMPEG_DIR}/lib NO_DEFAULT_PATH)
  find_library(FFMPEG_AVFILTER_LIBRARY
    NAMES avfilter
    PATHS ${_FFMPEG_AVDEVICE_LIBRARY_DIRS}  /usr/lib /usr/local/lib /opt/local/lib /sw/lib)

  find_library(FFMPEG_AVFORMAT_LIBRARY
    NAMES avformat
    PATHS $ENV{FFMPEG_DIR}/lib NO_DEFAULT_PATH)
  find_library(FFMPEG_AVFORMAT_LIBRARY
    NAMES avformat
    PATHS ${_FFMPEG_AVFORMAT_LIBRARY_DIRS} /usr/lib /usr/local/lib /opt/local/lib /sw/lib)

  find_library(FFMPEG_AVUTIL_LIBRARY
    NAMES avutil
    PATHS $ENV{FFMPEG_DIR}/lib NO_DEFAULT_PATH)
  find_library(FFMPEG_AVUTIL_LIBRARY
    NAMES avutil
    PATHS ${_FFMPEG_AVUTIL_LIBRARY_DIRS} /usr/lib /usr/local/lib /opt/local/lib /sw/lib)

  find_library(FFMPEG_SWRESAMPLE_LIBRARY
    NAMES swresample
    PATHS $ENV{FFMPEG_DIR}/lib NO_DEFAULT_PATH)
  find_library(FFMPEG_SWRESAMPLE_LIBRARY
    NAMES swresample
    PATHS ${_FFMPEG_SWRESAMPLE_LIBRARY_DIRS} /usr/lib /usr/local/lib /opt/local/lib /sw/lib)

  find_library(FFMPEG_SWSCALE_LIBRARY
    NAMES swscale
    PATHS $ENV{FFMPEG_DIR}/lib NO_DEFAULT_PATH)
  find_library(FFMPEG_SWSCALE_LIBRARY
    NAMES swscale
    PATHS ${_FFMPEG_SWSCALE_LIBRARY_DIRS} /usr/lib /usr/local/lib /opt/local/lib /sw/lib)

  if(FFMPEG_AVCODEC_LIBRARY)
    set(FFMPEG_FOUND TRUE)
  endif(FFMPEG_AVCODEC_LIBRARY)

  if (FFMPEG_FOUND)
    get_filename_component(FFMPEG_INCLUDE_DIR ${FFMPEG_AVCODEC_INCLUDE_DIR} PATH)
    set(FFMPEG_INCLUDE_DIRS
      ${FFMPEG_INCLUDE_DIR}
      ${FFMPEG_AVCODEC_INCLUDE_DIR}
      ${FFMPEG_AVDEVICE_INCLUDE_DIR}
      ${FFMPEG_AVFILTER_INCLUDE_DIR}
      ${FFMPEG_AVFORMAT_INCLUDE_DIR}
      ${FFMPEG_SWRESAMPLE_INCLUDE_DIR}
      ${FFMPEG_SWSCALE_INCLUDE_DIR})
    set(FFMPEG_LIBRARIES
      ${FFMPEG_AVCODEC_LIBRARY}
      ${FFMPEG_AVDEVICE_LIBRARY}
      ${FFMPEG_AVFILTER_LIBRARY}
      ${FFMPEG_AVFORMAT_LIBRARY}
      ${FFMPEG_AVUTIL_LIBRARY}
      ${FFMPEG_SWSCALE_LIBRARY}
      ${FFMPEG_SWRESAMPLE_LIBRARY})
  endif (FFMPEG_FOUND)

  mark_as_advanced(FFMPEG_INCLUDE_DIRS FFMPEG_LIBRARIES)
  mark_as_advanced(
    FFMPEG_AVCODEC_INCLUDE_DIR
    FFMPEG_AVDEVICE_INCLUDE_DIR
    FFMPEG_AVFILTER_INCLUDE_DIR
    FFMPEG_AVFORMAT_INCLUDE_DIR
    FFMPEG_AVUTIL_INCLUDE_DIR
    FFMPEG_SWSCALE_INCLUDE_DIR 
    FFMPEG_SWRESAMPLE_INCLUDE_DIR)
  mark_as_advanced(
    FFMPEG_AVCODEC_LIBRARY
    FFMPEG_AVDEVICE_LIBRARY
    FFMPEG_AVFILTER_LIBRARY
    FFMPEG_AVFORMAT_LIBRARY
    FFMPEG_AVUTIL_LIBRARY
    FFMPEG_SWSCALE_LIBRARY 
    FFMPEG_SWRESAMPLE_LIBRARY)
endif (FFMPEG_LIBRARIES AND FFMPEG_INCLUDE_DIRS)
