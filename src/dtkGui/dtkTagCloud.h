/* dtkTagCloud.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun May  3 10:42:01 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Feb 28 17:32:58 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 165
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
     dtkTag(const dtkTag& other);
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
    void onTagRemoved(void);

private:
    dtkTagScopePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkItem
// /////////////////////////////////////////////////////////////////

class dtkItemPrivate;

class DTKGUI_EXPORT dtkItem : public QListWidgetItem
{
public:
     dtkItem(QString name);
     dtkItem(QString name, QString description);
     dtkItem(QString name, QString description, QStringList tags);
     dtkItem(QString name, QString description, QStringList tags, QStringList types);
     dtkItem(const dtkItem& item);
    ~dtkItem(void);

    QString name(void) const;
    QString description(void) const;
    QStringList tags(void) const;
    QStringList types(void) const;

private:
    dtkItemPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkItemList
// /////////////////////////////////////////////////////////////////

class dtkItemListPrivate;

class DTKGUI_EXPORT dtkItemList : public QListWidget
{
    Q_OBJECT

public:
     dtkItemList(QWidget *parent = 0);
    ~dtkItemList(void);

    void addItem(QString name);
    void addItem(QString name, QString description);
    void addItem(QString name, QString description, QStringList tags);
    void addItem(QString name, QString description, QStringList tags, QStringList types);
    void addItem(dtkItem item);

    void clear(void);

signals:
    void itemClicked(const QString& description);

private slots:
    void onItemClicked(QListWidgetItem *item);

private:
    dtkItemListPrivate *d;

private:
    friend class dtkItemListDelegate;
};

// /////////////////////////////////////////////////////////////////
// dtkItemDesc
// /////////////////////////////////////////////////////////////////

class dtkItemDescPrivate;

class dtkItemDesc : public QFrame
{
    Q_OBJECT

public:
     dtkItemDesc(QWidget *parent = 0);
    ~dtkItemDesc(void);

signals:
    void back(void);

public slots:
    void clear(void);

public slots:
    void setDescription(const QString& description);

private:
    dtkItemDescPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkItemListDelegate
// /////////////////////////////////////////////////////////////////

class dtkItemListDelegate: public QStyledItemDelegate
{
public:
    dtkItemListDelegate(dtkItemList *list);

public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

public:
    virtual QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;

protected:
    dtkItemList *list;
};

// /////////////////////////////////////////////////////////////////
// dtkItemView
// /////////////////////////////////////////////////////////////////

class dtkItemViewPrivate;

class dtkItemView : public QStackedWidget
{
    Q_OBJECT

public:
    enum Direction {
        Left2Right,
        Right2Left,
        Top2Bottom,
        Bottom2Top,
        Automatic
    };
    
public:
     dtkItemView(QWidget *parent = 0);
    ~dtkItemView(void);

public:
    dtkItemList *list(void);
    dtkItemDesc *desc(void);
    
protected slots:
    void onItemClicked(const QString& description);

protected slots:
    void setSpeed(int speed);
    void setAnimation(QEasingCurve::Type type);
    void setVerticalMode(bool vertical = true);
    void setWrap(bool wrap);

protected slots:
    void slideInNext(void);
    void slideInPrev(void);
    void slideInIdx(int idx, Direction direction = Automatic);
    
signals:
    void animationFinished(void);

protected slots:
    void animationDoneSlot(void);

protected:
    void slideInWgt(QWidget *widget, Direction direction = Automatic);

protected:
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
    void remFilter(QString tag);
    void clear(void);

private:
    dtkTagControllerPrivate *d;
};

#endif // DTKTAGCLOUD_H
