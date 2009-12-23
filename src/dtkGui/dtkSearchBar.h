#ifndef DTKSEARCHBAR_H
#define DTKSEARCHBAR_H

#include "dtkGuiExport.h"

#include <QtGui>

class dtkSearchBarItemPrivate;

class DTKGUI_EXPORT dtkSearchBarItem : public QFrame
{
    Q_OBJECT

public:
     dtkSearchBarItem(QWidget *parent);
    ~dtkSearchBarItem(void);

    void  addKey(const QString& key);

    QString key(void) const;
    QString value(void) const;

    QSortFilterProxyModel *proxy(void);

signals:
    void more(dtkSearchBarItem *item);
    void less(dtkSearchBarItem *item);

    void   keyChanged(QString);
    void valueChanged(QString);

public slots:
    void   setKey(const QString& key);
    void setValue(const QString& value);

protected slots:
    void onMoreClicked(void);
    void onLessClicked(void);

private slots:
    void setFilterKeyColumn(int column);

private:
    dtkSearchBarItemPrivate *d;
};

class dtkSearchBarPrivate;

class DTKGUI_EXPORT dtkSearchBar : public QWidget
{
    Q_OBJECT

public:
     dtkSearchBar(QWidget *parent = 0);
    ~dtkSearchBar(void);

    void        addKey(const QString& key);
    void setDefaultKey(const QString& key);

    void setModel(QAbstractItemModel *model);
    void setView(QAbstractItemView *view);

protected slots:
    void    addItem(dtkSearchBarItem *item);
    void removeItem(dtkSearchBarItem *item);

    void setup(QString value);

private slots:
    void filter(void);

private:
    dtkSearchBarPrivate *d;
};

#endif // DTKSEARCHBAR_H
