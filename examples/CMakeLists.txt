### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Mar  9 21:06:43 2009 (+0100)
## Version: $Id$
## Last-Updated: Fri Mar  2 15:20:31 2012 (+0100)
##           By: Julien Wintz
##     Update #: 81
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
## dtkLog examples
## #################################################################

add_subdirectory(dtkLogger)
add_subdirectory(dtkLogView)

## #################################################################
## dtkCrypto examples
## #################################################################

add_subdirectory(dtkLicenseManager)

## #################################################################
## dtkCore examples
## #################################################################

add_subdirectory(dtkAbstractDataComposite)
add_subdirectory(dtkReferenceCounting)
add_subdirectory(dtkUpdater)

## #################################################################
## dtkGui examples
## #################################################################

add_subdirectory(dtkInterpreter)
add_subdirectory(dtkTagCloud)
add_subdirectory(dtkTextEditor)
add_subdirectory(dtkSettingsEditor)
add_subdirectory(dtkFinder)
add_subdirectory(dtkAboutPlugin)
add_subdirectory(dtkFlowLayout)

## #################################################################
## dtkVr examples
## #################################################################

add_subdirectory(dtkVrGestureRecognizer)

## #################################################################
## dtkPlot examples
## #################################################################

add_subdirectory(dtkPlotEcg)

## #################################################################
## dtkComposer examples
## #################################################################

add_subdirectory(dtkComposerTransmitter)
