/* dtkRecentFilesMenu.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Jun  8 13:45:35 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun  8 13:47:27 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkRecentFilesMenu.h"

#include <QSettings>
#include <QFileInfo>

dtkRecentFilesMenu::dtkRecentFilesMenu(QWidget *parent) : QMenu(parent), m_maxCount(5)
{
    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(menuTriggered(QAction*)));

    setMaxCount(m_maxCount);
}

dtkRecentFilesMenu::dtkRecentFilesMenu(const QString &title, QWidget *parent) : QMenu(title, parent), m_maxCount(5)
{
    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(menuTriggered(QAction*)));

    setMaxCount(m_maxCount);
}

void dtkRecentFilesMenu::addRecentFile(const QString &fileName)
{
    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > maxCount())
        files.removeLast();

    settings.setValue("recentFileList", files);

    updateRecentFileActions();
}

void dtkRecentFilesMenu::clearMenu(void)
{
    QSettings settings;
    settings.remove("recentFileList");

    updateRecentFileActions();
}

int dtkRecentFilesMenu::maxCount(void) const
{
    return m_maxCount;
}

void dtkRecentFilesMenu::setMaxCount(int count)
{
    m_maxCount = count;

    updateRecentFileActions();
}

void dtkRecentFilesMenu::menuTriggered(QAction* action)
{
    if (action->data().isValid())
        emit recentFileTriggered(action->data().toString());
}

void dtkRecentFilesMenu::updateRecentFileActions(void)
{
    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();

    int numRecentFiles = qMin(files.size(), maxCount());

    clear();

    for (int i = 0; i < numRecentFiles; ++i) {
        QString strippedName = QFileInfo(files[i]).fileName();
        QString text = tr("&%1 %2").arg(i + 1).arg(strippedName);

        QAction* recentFileAct = addAction(text);
        recentFileAct->setData(files[i]);
        recentFileAct->setVisible(true);
    }
    addSeparator();
    addAction(tr("Clear Menu"), this, SLOT(clearMenu()));

    setEnabled(numRecentFiles > 0);
}
