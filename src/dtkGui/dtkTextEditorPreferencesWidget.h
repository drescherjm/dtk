/* dtkTextEditorPreferencesWidget.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 10 09:24:10 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 20 15:46:07 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKTEXTEDITORPREFERENCESWIDGET_H
#define DTKTEXTEDITORPREFERENCESWIDGET_H

#include "dtkGuiExport.h"

#include <QWidget>

class dtkTextEditor;
class dtkTextEditorPreferencesWidgetPrivate;

class DTKGUI_EXPORT dtkTextEditorPreferencesWidget : public QWidget
{
    Q_OBJECT

public:
     dtkTextEditorPreferencesWidget(dtkTextEditor *editor, QWidget *parent);
    ~dtkTextEditorPreferencesWidget(void);

    void keyPressEvent(QKeyEvent *event);

signals:
    void accepted(void);
    void rejected(void);

public slots:
    void onFontChosen(QFont);
    void onSizeChosen(QString);

    void onNumbersCkeckBoxChanged(int);
    void onHighlightCkeckBoxChanged(int);
    void onRevisionsCkeckBoxChanged(int);

    void onOkButtonClicked(void);
    void onCancelButtonClicked(void);

private:
    dtkTextEditorPreferencesWidgetPrivate *d;
};

#endif // DTKTEXTEDITORPREFERENCESWIDGET_H
