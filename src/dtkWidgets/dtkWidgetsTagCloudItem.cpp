/* dtkWidgetsTagCloudItem.cpp ---
 *
 * Author: Julien Wintz
 * Created: Mon Apr 15 14:10:33 2013 (+0200)
 * Version:
 * Last-Updated: Mon Apr 15 14:12:03 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Change Log:
 *
 */

#include "dtkWidgetsTagCloudItem.h"

class dtkWidgetsTagCloudItemPrivate
{
public:
    QString name;
    QString description;
    QStringList tags;
    QString kind;
    QString type;
};

dtkWidgetsTagCloudItem::dtkWidgetsTagCloudItem(QString name) : QListWidgetItem(name)
{
    d = new dtkWidgetsTagCloudItemPrivate;
    d->name = name;
}

dtkWidgetsTagCloudItem::dtkWidgetsTagCloudItem(QString name, QString description) : QListWidgetItem(name)
{
    d = new dtkWidgetsTagCloudItemPrivate;
    d->name = name;
    d->description = description;
}

dtkWidgetsTagCloudItem::dtkWidgetsTagCloudItem(QString name, QString description, QStringList tags) : QListWidgetItem(name)
{
    d = new dtkWidgetsTagCloudItemPrivate;
    d->name = name;
    d->description = description;
    d->tags = tags;
}

dtkWidgetsTagCloudItem::dtkWidgetsTagCloudItem(QString name, QString description, QStringList tags, QString kind, QString type) : QListWidgetItem(name)
{
    d = new dtkWidgetsTagCloudItemPrivate;
    d->name = name;
    d->description = description;
    d->tags = tags;
    d->kind = kind;
    d->type = type;
}

dtkWidgetsTagCloudItem::dtkWidgetsTagCloudItem(const dtkWidgetsTagCloudItem& item) : QListWidgetItem(item.name())
{
    d = new dtkWidgetsTagCloudItemPrivate;
    d->name = item.d->name;
    d->description = item.d->description;
    d->tags = item.d->tags;
    d->kind = item.d->kind;
    d->type = item.d->type;
}

dtkWidgetsTagCloudItem::~dtkWidgetsTagCloudItem(void)
{
    delete d;
}

QString dtkWidgetsTagCloudItem::name(void) const
{
    return d->name;
}

QString dtkWidgetsTagCloudItem::description(void) const
{
    return d->description;
}

QStringList dtkWidgetsTagCloudItem::tags(void) const
{
    return d->tags;
}

QString dtkWidgetsTagCloudItem::kind(void) const
{
    return d->kind;
}

QString dtkWidgetsTagCloudItem::type(void) const
{
    return d->type;
}
