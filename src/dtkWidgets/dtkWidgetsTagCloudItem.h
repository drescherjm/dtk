/* dtkWidgetsTagCloudItem.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr 15 14:02:19 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr 15 14:04:21 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtWidgets>

class dtkWidgetsTagCloudItemPrivate;

class dtkWidgetsTagCloudItem : public QListWidgetItem
{
public:
     dtkWidgetsTagCloudItem(QString name);
     dtkWidgetsTagCloudItem(QString name, QString description);
     dtkWidgetsTagCloudItem(QString name, QString description, QStringList tags);
     dtkWidgetsTagCloudItem(QString name, QString description, QStringList tags, QString kind, QString type);
     dtkWidgetsTagCloudItem(const dtkWidgetsTagCloudItem& item);
    ~dtkWidgetsTagCloudItem(void);

public:
    QString name(void) const;
    QString description(void) const;
    QStringList tags(void) const;
    QString kind(void) const;
    QString type(void) const;

protected:
    dtkWidgetsTagCloudItemPrivate *d;
};
