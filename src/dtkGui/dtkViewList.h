/* dtkViewList.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:38:55 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri May 18 15:58:52 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVIEWLIST_H
#define DTKVIEWLIST_H

#include "dtkGuiExport.h"

#include <QtGui>

class dtkViewListPrivate;

class DTKGUI_EXPORT dtkViewList : public QListWidget
{
    Q_OBJECT

public:
     dtkViewList(QWidget *parent = 0);
    ~dtkViewList(void);

protected slots:
    void update(void);
    
protected:
    QMimeData *mimeData(const QList<QListWidgetItem *> items) const;
    QStringList mimeTypes(void) const;

private:
    dtkViewListPrivate *d;
};

#endif // DTKVIEWLIST_H
