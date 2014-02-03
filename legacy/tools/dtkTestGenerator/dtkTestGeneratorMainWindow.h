/* dtkTestGeneratorMainWindow.h ---
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Mar 10 00:11:13 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 16 09:45:03 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef dtkTestGeneratorMAINWINDOW_H
#define dtkTestGeneratorMAINWINDOW_H

#include <QtGui>

class dtkTestGeneratorMainWindowPrivate;

class dtkTestGeneratorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
     dtkTestGeneratorMainWindow(QWidget *parent = 0);
    ~dtkTestGeneratorMainWindow(void);

public slots:
    void generate(void);

public slots:
    void about(void);
    void onOutputPathClicked(void);
    void onOutputPathChanged(void);
    void onClassNameChanged(void);
    void update(void);

private:
    dtkTestGeneratorMainWindowPrivate *d;
};

#endif
