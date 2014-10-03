/* dtkWidgetsTag.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr 15 11:51:10 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr 15 11:56:48 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtWidgets>

class dtkWidgetsTagPrivate;

class dtkWidgetsTag
{
public:
     dtkWidgetsTag(void);
     dtkWidgetsTag(QString text, int instances);
     dtkWidgetsTag(QString text, int instances, QStringList items);
     dtkWidgetsTag(QString text, int instances, QStringList items, QString color);
     dtkWidgetsTag(const dtkWidgetsTag& other);
    ~dtkWidgetsTag(void);

    int count(void) const;
    QString text(void) const;
    QString color(void) const;
    QStringList items(void) const;

    void setCount(int count);
    void setText(QString text);
    void setColor(QString color);
    void setItems(QStringList items);

protected:
    dtkWidgetsTagPrivate *d;
};
