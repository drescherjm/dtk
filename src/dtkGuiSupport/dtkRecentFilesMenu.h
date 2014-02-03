/* dtkRecentFilesMenu.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Jun  8 13:38:19 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun  8 14:01:54 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKRECENTFILESMENU_H
#define DTKRECENTFILESMENU_H

#include <QMenu>

#include "dtkGuiSupportExport.h"

class DTKGUISUPPORT_EXPORT dtkRecentFilesMenu : public QMenu
{
    Q_OBJECT
    Q_PROPERTY(int maxCount READ maxCount WRITE setMaxCount)

public:
    dtkRecentFilesMenu(QWidget *parent = 0);
    dtkRecentFilesMenu(const QString &title, QWidget *parent = 0);

    int maxCount(void) const;

public slots:
    void addRecentFile(const QString &fileName);
    void clearMenu(void);
    void setMaxCount(int);

signals:
    void recentFileTriggered(const QString &filename);

private slots:
    void menuTriggered(QAction *action);
    void updateRecentFileActions(void);

private:
    int m_maxCount;
};

#endif // DTKRECENTFILEMENU_H
