### dtkInstall.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Thu Apr 22 14:31:53 2010 (+0200)
## Version: $Id$
## Last-Updated: Thu Apr 22 15:41:31 2010 (+0200)
##           By: Julien Wintz
##     Update #: 62
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

function(dtk_post_install application)

message(STATUS "post install ${QT_LIBRARIES}")

  if(APPLE)
    set(QT_LIBRARIES "")    
    set(QT_LIBRARIES "QtOpenGL" ${QT_LIBRARIES})
    set(QT_LIBRARIES "QtHelp" ${QT_LIBRARIES})
    set(QT_LIBRARIES "QtWebKit" ${QT_LIBRARIES})
    set(QT_LIBRARIES "QtGui" ${QT_LIBRARIES})
    set(QT_LIBRARIES "QtXml" ${QT_LIBRARIES})
    set(QT_LIBRARIES "QtXmlPatterns" ${QT_LIBRARIES})
    set(QT_LIBRARIES "QtSql" ${QT_LIBRARIES})
    set(QT_LIBRARIES "QtNetwork" ${QT_LIBRARIES})
    set(QT_LIBRARIES "QtCore" ${QT_LIBRARIES})

    foreach(DEPENDENCY ${QT_LIBRARIES})
      
      set(arguments "")
      set(arguments ${arguments} "-change")
      set(arguments ${arguments} "@executable_path/../Frameworks/${DEPENDENCY}.framework/Versions/4/${DEPENDENCY}")
      set(arguments ${arguments} "${CMAKE_INSTALL_PREFIX}/bin/${application}.app/Contents/MacOS/${application}")
      
      message(STATUS "${DEPENDENCY}" "${arguments}")

      execute_process(COMMAND install_name_tool ${arguments})
      
    endforeach()

  endif(APPLE)

endfunction(dtk_post_install)
