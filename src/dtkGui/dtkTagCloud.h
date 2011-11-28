/* dtkTagCloud.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun May  3 10:42:01 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Nov 28 15:21:02 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 94
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKTAGCLOUD_H
#define DTKTAGCLOUD_H

#include <QtGui>

#include "dtkGuiExport.h"

// /////////////////////////////////////////////////////////////////
// dtkTag
// /////////////////////////////////////////////////////////////////

class dtkTagPrivate;

class DTKGUI_EXPORT dtkTag
{
public:
     dtkTag(void);
     dtkTag(QString text, int instances);
     dtkTag(QString text, int instances, QStringList items);
     dtkTag(QString text, int instances, QStringList items, QString color);
    ~dtkTag(void);

    int count(void) const;
    QString text(void) const;
    QString color(void) const;
    QStringList items(void) const;

    void setCount(int count);
    void setText(QString text);
    void setColor(QString color);
    void setItems(QStringList items);

private:
    dtkTagPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkTagCloud
// /////////////////////////////////////////////////////////////////

class dtkTagCloudPrivate;

class DTKGUI_EXPORT dtkTagCloud : public QTextBrowser
{
    Q_OBJECT

public:
     dtkTagCloud(QWidget *parent = 0);
    ~dtkTagCloud(void);

    enum SortingType {
        Alpha,
        Num
    };

    enum SortingOrder {
        Asc,
        Desc
    };

    void addTag(QString text, int instances);
    void addTag(QString text, int instances, QStringList items);
    void addTag(QString text, int instances, QStringList items, QString color);
    void addTag(dtkTag tag);

    void setFontSize(int size);
    void setFontRange(int range);

    void setSortingType(SortingType type);
    void setSortingOrder(SortingOrder order);

signals:
    void tagClicked(QString tag);
    void tagClicked(QString tag, QStringList items);

public slots:
    void sort(void);
    void clear(void);
    void render(void);

private slots:
    void onLinkClicked(const QUrl& item);

private:
    dtkTagCloudPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkTagScope
// /////////////////////////////////////////////////////////////////

class dtkTagScopePrivate;

class DTKGUI_EXPORT dtkTagScope : public QFrame
{
    Q_OBJECT

public:
     dtkTagScope(QWidget *parent = 0);
    ~dtkTagScope(void);

    QSize sizeHint(void) const;

    void render(void);

    void addTag(QString tag);

signals:
    void tagSet(QString tag);
    void tagAdded(QString tag);
    void tagRemoved(QString tag);
    void cleared(void);

public slots:
    void clear(void);

private slots:
    void onTagAdded(void);
    void onLinkClicked(const QUrl& item);

private:
    dtkTagScopePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkItem
// /////////////////////////////////////////////////////////////////

class dtkItemPrivate;

class DTKGUI_EXPORT dtkItem
{
public:
     dtkItem(QString name);
     dtkItem(QString name, QString description);
     dtkItem(QString name, QString description, QStringList tags);
     dtkItem(QString name, QString description, QStringList tags, QStringList types);
    ~dtkItem(void);

    QString name(void) const;
    QString description(void) const;
    QStringList tags(void) const;
    QStringList types(void) const;

private:
    dtkItemPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkItemView
// /////////////////////////////////////////////////////////////////

class dtkItemViewPrivate;

class DTKGUI_EXPORT dtkItemView : public QTextBrowser
{
    Q_OBJECT

public:
     dtkItemView(QWidget *parent = 0);
    ~dtkItemView(void);

    void addItem(QString name);
    void addItem(QString name, QString description);
    void addItem(QString name, QString description, QStringList tags);
    void addItem(QString name, QString description, QStringList tags, QStringList types);
    void addItem(dtkItem item);

    void clear(void);
    void render(void);

signals:
    void tagClicked(QString tag);
    void tagClicked(QString tag, QStringList items);

    void itemClicked(QString item);
    void itemClicked(QString item, QStringList tags);

    void typeClicked(QString type);
    void typeClicked(QString type, QStringList tags);

private slots:
    void onLinkClicked(const QUrl& item);

private:
    dtkItemViewPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkTagController
// /////////////////////////////////////////////////////////////////

class dtkTagControllerPrivate;

class DTKGUI_EXPORT dtkTagController : public QObject
{
    Q_OBJECT

public:
     dtkTagController(void);
    ~dtkTagController(void);

    void attach(dtkItemView *view);
    void attach(dtkTagCloud *cloud);
    void attach(dtkTagScope *scope);

    void addItem(QString name);
    void addItem(QString name, QString description);
    void addItem(QString name, QString description, QStringList tags);
    void addItem(QString name, QString description, QStringList tags, QStringList types);

    void update(void);
    void render(void);

private slots:
    void addFilter(QString tag);
    void setFilter(QString tag);
    void clear(void);

private:
    dtkTagControllerPrivate *d;
};

#endif // DTKTAGCLOUD_H
