/* dtkInterpreterPreferencesWidget.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 10 09:24:10 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Aug  6 10:21:27 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKINTERPRETERPREFERENCESWIDGET_H
#define DTKINTERPRETERPREFERENCESWIDGET_H

#include <dtkGui/dtkPreferencesWidget.h>

class dtkInterpreter;
class dtkInterpreterPreferencesWidgetPrivate;

class dtkInterpreterPreferencesWidget : public dtkPreferencesPage
{
    Q_OBJECT

public:
     dtkInterpreterPreferencesWidget(dtkInterpreter *editor, QWidget *parent);
    ~dtkInterpreterPreferencesWidget(void);

    void keyPressEvent(QKeyEvent *event);

signals:
    void accepted(void);
    void rejected(void);

public slots:
    void onFontChosen(QFont);
    void onSizeChosen(QString);

    void onTextColorClicked(void);
    void onBackgroundColorClicked(void);
    void onBackgroundOpacityChanged(int value);

    void onOkButtonClicked(void);
    void onCancelButtonClicked(void);

private:
    dtkInterpreterPreferencesWidgetPrivate *d;
};

#endif // DTKINTERPRETERPREFERENCESWIDGET_H
