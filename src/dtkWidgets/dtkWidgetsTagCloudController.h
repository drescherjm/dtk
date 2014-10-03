/* dtkWidgetsTagCloudController.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr 15 12:14:03 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr 15 14:46:06 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 21
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>

class dtkWidgetsTagCloud;
class dtkWidgetsTagCloudView;
class dtkWidgetsTagCloudScope;
class dtkWidgetsTagCloudControllerPrivate;

class dtkWidgetsTagCloudController : public QObject
{
    Q_OBJECT

public:
     dtkWidgetsTagCloudController(void);
    ~dtkWidgetsTagCloudController(void);

    void attach(dtkWidgetsTagCloud *cloud);
    void attach(dtkWidgetsTagCloudView *view);
    void attach(dtkWidgetsTagCloudScope *scope);

    void addItem(QString name);
    void addItem(QString name, QString description);
    void addItem(QString name, QString description, QStringList tags);
    void addItem(QString name, QString description, QStringList tags, QString kind, QString type);

    void update(void);
    void render(void);

public slots:
    void onUnionMode(bool mode);
			       
protected slots:
    void addFilter(QString tag);
    void setFilter(QString tag);
    void remFilter(QString tag);
    void clear(void);
    
protected:
    dtkWidgetsTagCloudControllerPrivate *d;
};
