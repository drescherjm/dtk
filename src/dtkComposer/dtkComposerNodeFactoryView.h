/* dtkComposerNodeFactoryView.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Apr 11 10:38:29 2013 (+0200)
 * Version: 
 * Last-Updated: ven. janv.  9 10:13:20 2015 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 8
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
class dtkComposerSceneNode;
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

public slots:
    void onShowNodeDocumentation(dtkComposerSceneNode *node);

public:
    void addNote(void);

public:
    void setFactory(dtkComposerNodeFactory *factory);

public:
    void setDark(void);

public:
    dtkWidgetsTagCloud      *cloudView(void) const;
    dtkWidgetsTagCloudView   *itemView(void) const;
    dtkWidgetsTagCloudScope *scopeView(void) const;

private:
    dtkComposerNodeFactoryViewPrivate *d;
};
