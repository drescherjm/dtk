/* dtkWidgetsTagCloudScope.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr 15 12:38:14 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr 15 14:50:57 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>
#include <QtWidgets>

class dtkWidgetsTagCloudScopePrivate;

class dtkWidgetsTagCloudScope : public QFrame
{
    Q_OBJECT

public:
     dtkWidgetsTagCloudScope(QWidget *parent = 0);
    ~dtkWidgetsTagCloudScope(void);

    QSize sizeHint(void) const;

    void render(void);

    void addTag(QString tag);
    void addTag(QString tag, int count);

    void setTags(const QStringList& tags);

    void setDark(void);

signals:
    void tagSet(QString tag);
    void tagAdded(QString tag);
    void tagRemoved(QString tag);
    void cleared(void);
    void unionMode(bool);

public slots:
    void clear(void);

public slots:
    void toggle(void);
		     
protected slots:
    void onTagAdded(void);
    void onTagRemoved(void);
    
protected:
    dtkWidgetsTagCloudScopePrivate *d;
};
