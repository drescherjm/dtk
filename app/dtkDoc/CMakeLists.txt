### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Fri Feb  8 16:49:52 2013 (+0100)
## Version: 
## Last-Updated: mer. avril  9 14:16:54 2014 (+0200)
##           By: Thibaud Kloczko
##     Update #: 58
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtkDoc)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  atom.h
  codeparser.h 
  cppcodeparser.h
  editdistance.h
  htmlgenerator.h
  node.h
  puredocparser.h
  qdoctagfiles.h
  qmlmarkupvisitor.h
  separator.h
  tree.h
  codechunk.h
  config.h
  ditaxmlgenerator.h
  generator.h
  jscodemarker.h
  openedlist.h
  qdocdatabase.h
  qmlcodemarker.h
  qmlvisitor.h
  text.h
  codemarker.h
  cppcodemarker.h
  doc.h
  helpprojectwriter.h
  location.h
  plaincodemarker.h
  qdocindexfiles.h
  qmlcodeparser.h
  quoter.h
  tokenizer.h    
  qqmljsast_p.h
  qqmljsastfwd_p.h
  qqmljsastvisitor_p.h
  qqmljsengine_p.h
  qqmljsgrammar_p.h
  qqmljslexer_p.h
  qqmljsmemorypool_p.h
  qqmljsparser_p.h
  qqmljsglobal_p.h
  qqmljskeywords_p.h)

set(${PROJECT_NAME}_SOURCES
  atom.cpp
  codeparser.cpp 
  cppcodeparser.cpp
  editdistance.cpp
  htmlgenerator.cpp
  node.cpp
  puredocparser.cpp
  qdoctagfiles.cpp
  qmlmarkupvisitor.cpp
  separator.cpp
  tree.cpp
  codechunk.cpp
  config.cpp
  ditaxmlgenerator.cpp
  generator.cpp
  jscodemarker.cpp
  openedlist.cpp
  qdocdatabase.cpp
  qmlcodemarker.cpp
  qmlvisitor.cpp
  text.cpp
  codemarker.cpp
  cppcodemarker.cpp
  doc.cpp
  helpprojectwriter.cpp
  location.cpp
  plaincodemarker.cpp
  qdocindexfiles.cpp
  qmlcodeparser.cpp
  quoter.cpp
  tokenizer.cpp
  yyindent.cpp    
  qqmljsast.cpp
  qqmljsastvisitor.cpp
  qqmljsengine_p.cpp
  qqmljsgrammar.cpp
  qqmljslexer.cpp
  qqmljsparser.cpp
  main.cpp)

## #################################################################
## Build rules
## #################################################################

add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Xml)

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT app)
