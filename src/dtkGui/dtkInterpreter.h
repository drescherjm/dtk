/* dtkInterpreter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 10 15:29:01 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jan 10 14:45:13 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 92
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKINTERPRETER_H
#define DTKINTERPRETER_H

#include "dtkGuiExport.h"

#include <QtGui>

class dtkScriptInterpreter;
class dtkInterpreterPrivate;

class DTKGUI_EXPORT dtkInterpreter : public QPlainTextEdit
{
    Q_OBJECT

public:
     dtkInterpreter(QWidget *parent = 0);
    ~dtkInterpreter(void);

#pragma mark -
#pragma mark - Interpretation interface

    dtkScriptInterpreter *interpreter(void);

    void registerInterpreter(dtkScriptInterpreter *interpreter);

#pragma mark -
#pragma mark - Graphical interface

    void output(const QString& result);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

protected:
    void onKeyUpPressed(void);
    void onKeyDownPressed(void);
    void onKeyLeftPressed(void);
    void onKeyRightPressed(void);
    void onKeyEnterPressed(void);

protected:
    int currentLineNumber(void) const;
    QString currentLine(void) const;
    QString currentBlock(void) const;

private:
    dtkInterpreterPrivate *d;
};

#endif
