/* dtkWidgetsTagCloudScope.h ---
 *
 * Author: Julien Wintz
 * Created: Mon Apr 15 12:38:14 2013 (+0200)
 */

/* Change Log:
 *
 */

#pragma once

#include "dtkWidgetsExport.h"

#include <QtCore>
#include <QtWidgets>

class dtkWidgetsTagCloudScopePrivate;

class DTKWIDGETS_EXPORT dtkWidgetsTagCloudScope : public QFrame
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
