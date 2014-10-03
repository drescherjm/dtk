/* dtkWidgetsTagCloudScope.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr 15 12:33:21 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr 15 14:51:54 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtWidgets>

class dtkWidgetsTagCloudScopeItemPrivate;

class dtkWidgetsTagCloudScopeItem : public QWidget
{
    Q_OBJECT

public:
     dtkWidgetsTagCloudScopeItem(QWidget *parent = 0);
    ~dtkWidgetsTagCloudScopeItem(void);

signals:
    void clicked(void);

public:
    QSize sizeHint(void) const;

public:
    QString text(void);

public:
    void setDark(void);

public slots:
    void setText(const QString& text);
    void setCount(int count);

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

protected:
    void mouseReleaseEvent(QMouseEvent *);

protected:
    dtkWidgetsTagCloudScopeItemPrivate *d;
};
