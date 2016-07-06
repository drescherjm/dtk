// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

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
    dtkWidgetsTagCloudView   *itemView(void) const;
    dtkWidgetsTagCloudScope *scopeView(void) const;

private:
    dtkComposerNodeFactoryViewPrivate *d;
};

//
// dtkComposerNodeFactoryView.h ends here
