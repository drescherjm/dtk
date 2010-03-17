/* dtkInterpreter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 10 15:31:39 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Mar 17 09:10:59 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 394
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <iostream>

#include <QtDebug>
#include <QtCore>
#include <QtGui>

#include <dtkCore/dtkLog.h>

#include <dtkScript/dtkScriptInterpreter.h>
#include <dtkScript/dtkScriptInterpreterPython.h>
#include <dtkScript/dtkScriptInterpreterTcl.h>

#include <dtkGui/dtkTextEditorSyntaxHighlighterPython.h>
#include <dtkGui/dtkTextEditorSyntaxHighlighterTcl.h>
#include <dtkGui/dtkInterpreter.h>
#include <dtkGui/dtkInterpreterPreferencesWidget.h>

// /////////////////////////////////////////////////////////////////
// dtkInterpreterPrivate
// /////////////////////////////////////////////////////////////////

class dtkInterpreterPrivate
{
public:
    dtkScriptInterpreter *interpreter;
    dtkInterpreterPreferencesWidget *preferences;
    
    QTextCursor cursor;

    QStringList  history;
    unsigned int history_index;
    bool         history_dirty;
};

// /////////////////////////////////////////////////////////////////
// dtkInterpreter
// /////////////////////////////////////////////////////////////////

dtkInterpreter::dtkInterpreter(QWidget *parent) : dtkTextEditor(parent)
{
    d = new dtkInterpreterPrivate;
    d->interpreter = NULL;
    d->preferences = NULL;

    d->history_index = 0;
    d->history_dirty = false;

    this->setShowLineNumbers(false);
    this->setShowCurrentLine(false);
    this->setShowRevisions(false);
}

dtkInterpreter::~dtkInterpreter(void)
{
    delete d;
}

dtkScriptInterpreter *dtkInterpreter::interpreter(void)
{
    return d->interpreter;
}

void dtkInterpreter::keyPressEvent(QKeyEvent *event)
{
    QTextCursor cursor = textCursor();

    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {

        this->onKeyEnterPressed();

    } else if(event->key() == Qt::Key_Backspace) {

        if(cursor.columnNumber() > filter(d->interpreter->prompt()).size())
            dtkTextEditor::keyPressEvent(event);
        
        this->onKeyBackspacePressed();

    } else if(event->key() == Qt::Key_Up) {
        this->onKeyUpPressed();

    } else if(event->key() == Qt::Key_Down) {
        this->onKeyDownPressed();

    } else if(event->key() == Qt::Key_Left) {

        if(event->modifiers() & Qt::ControlModifier) {
            cursor.movePosition(QTextCursor::StartOfLine);
            cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, filter(d->interpreter->prompt()).size());

            this->setTextCursor(cursor);
        }
        
        else if(cursor.columnNumber() > filter(d->interpreter->prompt()).size())
            dtkTextEditor::keyPressEvent(event);
        
        this->onKeyLeftPressed();

    } else if(event->key() == Qt::Key_Right) {

        if(cursor.columnNumber() < currentLine().size())
            dtkTextEditor::keyPressEvent(event);

        this->onKeyRightPressed();

    } else
        dtkTextEditor::keyPressEvent(event);
}

void dtkInterpreter::mousePressEvent(QMouseEvent *event)
{
    d->cursor = this->textCursor();

    dtkTextEditor::mousePressEvent(event);
}

void dtkInterpreter::mouseReleaseEvent(QMouseEvent *event)
{
    dtkTextEditor::mouseReleaseEvent(event);

    if(d->cursor.blockNumber() +1 != currentLineNumber() && d->cursor.columnNumber() <= filter(d->interpreter->prompt()).size())
        this->setTextCursor(d->cursor);
}

void dtkInterpreter::readSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("interpreter");
    this->setFont(settings.value("font").value<QFont>());    
    this->setBackgroundColor(settings.value("backgroundcolor", Qt::darkGray).value<QColor>());
    this->setForegroundColor(settings.value("foregroundcolor", Qt::white).value<QColor>());
    settings.endGroup();
}

void dtkInterpreter::writeSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("interpreter");
    settings.setValue("font", this->font());    
    settings.setValue("backgroundcolor", this->backgroundColor());
    settings.setValue("foregroundcolor", this->foregroundColor());
    settings.endGroup();
}

void dtkInterpreter::registerAsHandler(dtkLog::Handler handler)
{
    dtkLog::registerHandler(handler);
}

void dtkInterpreter::registerInterpreter(dtkScriptInterpreter *interpreter)
{
    d->interpreter = interpreter;
    d->interpreter->setVerbose(false);

    connect(interpreter, SIGNAL(interpreted(const QString&, int *)), this, SLOT(output(const QString&, int *)));
    connect(this, SIGNAL(input(const QString&, int *)), interpreter,    SLOT(interpret(const QString&, int *)));
    connect(this, SIGNAL( load(const QString&)),        interpreter,    SLOT(     load(const QString&)));
    connect(this, SIGNAL( save(const QString&)),        interpreter,    SLOT(     save(const QString&)));
    connect(this, SIGNAL(stopped(void)),                interpreter,  SIGNAL(  stopped(void)));

    dtkTextEditorSyntaxHighlighter *highlighter;

    if(dynamic_cast<dtkScriptInterpreterPython *>(interpreter))
        highlighter = new dtkTextEditorSyntaxHighlighterPython(this);

    if(dynamic_cast<dtkScriptInterpreterTcl *>(interpreter))
        highlighter = new dtkTextEditorSyntaxHighlighterTcl(this);

    Q_UNUSED(highlighter);

    this->appendPlainText(filter(d->interpreter->prompt()));
}

dtkInterpreterPreferencesWidget *dtkInterpreter::preferencesWidget(QWidget *parent)
{
    if(!d->preferences)
        d->preferences = new dtkInterpreterPreferencesWidget(this, parent);

    return d->preferences;
}

void dtkInterpreter::onKeyUpPressed(void)
{
    if(d->history.size() == 0)
        return;

    if(d->history_index && d->history_index == (unsigned int)d->history.size()-1)
        return;

    if(d->history_index == 0 && !d->history_dirty) {
        QString line = currentLine();
        if(d->interpreter)
            line.remove(filter(d->interpreter->prompt()));
        
        d->history.push_front(line);
        d->history_dirty = true;
    }

    d->history_index++;

    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, filter(d->interpreter->prompt()).size());
    cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    cursor.insertText(d->history.at(d->history_index));
    cursor.movePosition(QTextCursor::EndOfLine);
    this->setTextCursor(cursor);
}

void dtkInterpreter::onKeyDownPressed(void)
{
    if(d->history_index == 0)
        return;

    d->history_index--;

    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, filter(d->interpreter->prompt()).size());
    cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    cursor.insertText(d->history.at(d->history_index));
    cursor.movePosition(QTextCursor::EndOfLine);
    this->setTextCursor(cursor);

    if(d->history_index == 0 && d->history_dirty) {
        d->history.pop_front();
        d->history_dirty = false;
    }
}

void dtkInterpreter::onKeyLeftPressed(void)
{
    // check cursor
}

void dtkInterpreter::onKeyRightPressed(void)
{
    // check cursor
}

void dtkInterpreter::onKeyEnterPressed(void)
{
    int stat;

    QString line = currentLine();

    if(d->interpreter)
        line.remove(filter(d->interpreter->prompt()));

    if (line == "bye" || line == "exit" || line == "quit")
        emit stopped();
    
    if(!line.isEmpty()) {
        if(d->history_index > 0 && d->history_dirty)
            d->history.removeFirst();

        d->history.push_front(line);
        d->history_index = 0;
        d->history_dirty = false;
    }
    
    if (line.startsWith(":load ")) {
        emit load(line.remove(":load "));
        
    } else if (line.startsWith(":save ")) {
        emit save(line.remove(":save "));
        
    } else if (line.startsWith(":emacs")) {
        std::cerr << "emacs bindings not supported in gui mode" << std::endl;
        
        emit input("", &stat);
        
    } else if (line.startsWith(":vi")) {
        std::cerr << "vi bindings not supported in gui mode" << std::endl;
        
        emit input("", &stat);
        
    } else if (line.startsWith(":help")) {
        std::cerr << "File manipulation:";
        std::cerr << " :load [file]        loads file and interprets its content" << std::endl;
        std::cerr << " :save [file]        saves interpreter history to file" << std::endl;
        std::cerr << "" << std::endl;
        
        emit input("", &stat);
        
    } else if (line.startsWith(":man ")) {
        
        emit input("", &stat);

    } else if(line.isEmpty()) {

        this->appendPlainText(filter(d->interpreter->prompt()));

    } else {

        emit input(line, &stat);

    }
}

void dtkInterpreter::onKeyBackspacePressed(void)
{

}

void dtkInterpreter::output(const QString& result,  int *stat)
{
    Q_UNUSED(stat);

    QString text(result);

    if(!text.simplified().isEmpty())
        this->appendPlainText(filter(text));

    this->appendPlainText(filter(d->interpreter->prompt()));
    
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::End);
    this->setTextCursor(cursor);
}

QString dtkInterpreter::filter(QString text)
{
    return text
        .remove(DTK_COLOR_FG_BLACK)
        .remove(DTK_COLOR_FG_RED)
        .remove(DTK_COLOR_FG_GREEN)
        .remove(DTK_COLOR_FG_YELLOW)
        .remove(DTK_COLOR_FG_BLUE)
        .remove(DTK_COLOR_FG_MAGENTA)
        .remove(DTK_COLOR_FG_CYAN)
        .remove(DTK_COLOR_FG_WHITE)
        
        .remove(DTK_COLOR_FG_LTBLACK)
        .remove(DTK_COLOR_FG_LTRED)
        .remove(DTK_COLOR_FG_LTGREEN)
        .remove(DTK_COLOR_FG_LTYELLOW)
        .remove(DTK_COLOR_FG_LTBLUE)
        .remove(DTK_COLOR_FG_LTMAGENTA)
        .remove(DTK_COLOR_FG_LTCYAN)
        .remove(DTK_COLOR_FG_LTWHITE)
        
        .remove(DTK_COLOR_BG_BLACK)
        .remove(DTK_COLOR_BG_RED)
        .remove(DTK_COLOR_BG_GREEN)
        .remove(DTK_COLOR_BG_YELLOW)
        .remove(DTK_COLOR_BG_BLUE)
        .remove(DTK_COLOR_BG_MAGENTA)
        .remove(DTK_COLOR_BG_CYAN)
        .remove(DTK_COLOR_BG_WHITE)

        .remove(DTK_COLOR_FG_BD)
        .remove(DTK_COLOR_FG_UL)
        .remove(DTK_NO_COLOR);
}

bool dtkInterpreter::eventFilter(QObject *object, QEvent *event)
{
    dtkLogEvent *log = dynamic_cast<dtkLogEvent *>(event);
    dtkInterpreter *interpreter = dynamic_cast<dtkInterpreter *>(object);

    if (log && interpreter) {
        int stat; interpreter->output(log->message(), &stat);
        return true;
    } else {
        return QObject::eventFilter(object, event);
    }
}
