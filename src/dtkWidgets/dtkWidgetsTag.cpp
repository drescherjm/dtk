/* dtkWidgetsTag.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr 15 11:52:23 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr 15 11:56:24 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Change Log:
 * 
 */

#include "dtkWidgetsTag.h"

class dtkWidgetsTagPrivate
{
public:
    int count;
    QString text;
    QString color;
    QStringList items;
};

dtkWidgetsTag::dtkWidgetsTag(void) : d(new dtkWidgetsTagPrivate)
{

}

dtkWidgetsTag::dtkWidgetsTag(QString text, int count) : d(new dtkWidgetsTagPrivate)
{
    d->text = text;
    d->count = count;
}

dtkWidgetsTag::dtkWidgetsTag(QString text, int count, QStringList items) : d(new dtkWidgetsTagPrivate)
{
    d->text = text;
    d->count = count;
    d->items = items;
}

dtkWidgetsTag::dtkWidgetsTag(QString text, int count, QStringList items, QString color) : d(new dtkWidgetsTagPrivate)
{
    d->text = text;
    d->count = count;
    d->items = items;
    d->color = color;
}

dtkWidgetsTag::dtkWidgetsTag(const dtkWidgetsTag& other) : d(new dtkWidgetsTagPrivate)
{
    d->text = other.d->text;
    d->count = other.d->count;
    d->items = other.d->items;
    d->color = other.d->color;
}

dtkWidgetsTag::~dtkWidgetsTag(void)
{
    delete d;

    d = NULL;
}

int dtkWidgetsTag::count(void) const
{
    return d->count;
}

QString dtkWidgetsTag::text(void) const
{
    return d->text;
}

QStringList dtkWidgetsTag::items(void) const
{
    return d->items;
}

QString dtkWidgetsTag::color(void) const
{
    return d->color;
}

void dtkWidgetsTag::setCount(int count)
{
    if (count > 0)
        d->count = count;
    else
        d->count = count;
}

void dtkWidgetsTag::setText(QString text)
{
    if (!text.isNull())
        d->text = text;
    else
        d->text = "";
}

void dtkWidgetsTag::setItems(QStringList items)
{
    if (!items.isEmpty())
        d->items = items;
    else
        d->items = QStringList();
}

void dtkWidgetsTag::setColor(QString color)
{
    if (!color.isNull())
        d->color = color;
    else
        d->color = "";
}
