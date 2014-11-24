/* dtkWidgetsTagCloudList.h ---
 *
 * Author: Julien Wintz
 * Created: Mon Apr 15 14:12:29 2013 (+0200)
 */

/* Change Log:
 *
 */

#pragma once

#include "dtkWidgetsExport.h"
#include "dtkWidgetsTagCloudItem.h"

#include <QtWidgets>

class dtkWidgetsTagCloudListPrivate;

class DTKWIDGETS_EXPORT dtkWidgetsTagCloudList : public QListWidget
{
    Q_OBJECT

public:
     dtkWidgetsTagCloudList(QWidget *parent = 0);
    ~dtkWidgetsTagCloudList(void);

    void addItem(QString name);
    void addItem(QString name, QString description);
    void addItem(QString name, QString description, QStringList tags);
    void addItem(QString name, QString description, QStringList tags, QString kind, QString type);
    void addItem(dtkWidgetsTagCloudItem item);

    void clear(void);

public:
    void setDark(void);

signals:
    void itemClicked(const QString& description);

protected slots:
    void onItemClicked(QListWidgetItem *item);

protected:
     QMimeData *mimeData(const QList<QListWidgetItem *> items) const;
    QStringList mimeTypes(void) const;

protected:
    dtkWidgetsTagCloudListPrivate *d;

protected:
    friend class dtkWidgetsTagCloudListLightDelegate;
    friend class dtkWidgetsTagCloudListDarkDelegate;
};
