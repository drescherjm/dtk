/* dtkComposerNodeFactoryView.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Apr 11 10:38:29 2013 (+0200)
 * Version: 
 * Last-Updated: lun. janv.  5 13:48:34 2015 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 7
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include <QtCore>
#include <QtWidgets>

class dtkComposerFactory;
class dtkComposerNodeFactoryViewPrivate;
class dtkWidgetsItemView;
class dtkWidgetsTagCloud;
class dtkWidgetsTagCloudScope;
class dtkWidgetsTagCloudView;

class DTKCOMPOSER_EXPORT dtkComposerNodeFactoryView : public QWidget
{
    Q_OBJECT

public:
     dtkComposerNodeFactoryView(QWidget *parent = 0);
    ~dtkComposerNodeFactoryView(void);

public:
    void setFactory(dtkComposerFactory *factory);

public:
    void setDark(void);

public:
    dtkWidgetsTagCloud      *cloudView(void) const;
    dtkWidgetsTagCloudView   *itemView(void) const;
    dtkWidgetsTagCloudScope *scopeView(void) const;

private:
    dtkComposerNodeFactoryViewPrivate *d;
};
