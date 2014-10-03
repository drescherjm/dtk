/* dtkWidgetsTagCloudDesc.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr 15 14:36:15 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr 15 14:43:47 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtWidgets>

class dtkWidgetsTagCloudDescPrivate;

class dtkWidgetsTagCloudDesc : public QFrame
{
    Q_OBJECT

public:
     dtkWidgetsTagCloudDesc(QWidget *parent = 0);
    ~dtkWidgetsTagCloudDesc(void);

signals:
    void back(void);

public slots:
    void clear(void);

public slots:
    void setDescription(const QString& description);

protected:
    dtkWidgetsTagCloudDescPrivate *d;
};
