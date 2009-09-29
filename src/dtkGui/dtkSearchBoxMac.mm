/* dtkSearchBoxMac.mm --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 16 23:58:26 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Sep 28 08:59:47 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 172
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkGui/dtkSearchBox.h>
#include <dtkGui/dtkSearchBoxMac.h>

// /////////////////////////////////////////////////////////////////
// Objective-C/Carbon/Cocoa utils
// /////////////////////////////////////////////////////////////////

#include <Carbon/Carbon.h>
#include <Cocoa/Cocoa.h>

extern QString qStringfromCFString(CFStringRef cfs);
extern QString qStringfromNSString(NSString *nss);

// /////////////////////////////////////////////////////////////////
// Objective-C/Cocoa helper
// /////////////////////////////////////////////////////////////////

#include <Cocoa/Cocoa.h>

@interface cocoaSearchBox : NSView
{
    NSSearchField *search;

    dtkSearchBoxMac *parent;
}

- (void)setParent:(dtkSearchBoxMac *)widget;

@end

@implementation cocoaSearchBox

- (id)init
{
    if ((self = [super init])) {

	search = [[NSSearchField alloc] initWithFrame:NSMakeRect(0, 0, 190, 26)]; 
	
	[[search cell] setSendsWholeSearchString:NO];

	// [search setDelegate:self];
	
	[self addSubview:search];
    }

    return self;
}

- (void)controlTextDidChange:(NSNotification *)notification
{
    parent->onTextChanged(qStringfromNSString([[search cell] stringValue]));
}

- (void)setParent:(dtkSearchBoxMac *)widget
{
    self->parent = widget;
}

@end

// /////////////////////////////////////////////////////////////////
// dtkSearchBoxPrivate
// /////////////////////////////////////////////////////////////////

#include <Carbon/Carbon.h>

class dtkSearchBoxMacPrivate
{
public:
    cocoaSearchBox *search;

    HIViewRef ref;

    QMenu *menu;
};

dtkSearchBoxMac::dtkSearchBoxMac(QWidget *parent) : QWidget(parent), d(new dtkSearchBoxMacPrivate)
{
    d->search = [[cocoaSearchBox alloc] init];

    [d->search setParent:this];

    // HICocoaViewCreate(d->search, 0, &(d->ref));

    this->create(reinterpret_cast<WId>(d->ref));

    this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
}

dtkSearchBoxMac::~dtkSearchBoxMac(void)
{
    delete d;

    d = NULL;
}

QSize dtkSearchBoxMac::sizeHint(void) const
{
    return QSize(200, 26);
}

void dtkSearchBoxMac::setMenu(QMenu *menu)
{
    d->menu = menu;

    // NSMenu *nsMenu = menu->macMenu(0);
    // [[search cell] setSearchMenuTemplate:nsMenu];
}

void dtkSearchBoxMac::onTextChanged(const QString& text)
{
    QString attribute = "";

    // if(d->menu)
    //     foreach(QAction *action, d->menu->actions())
    //         if(action->isChecked())
    //     	attribute = action->text();
    
    emit(textChanged(text));
    // emit(textChanged(text, attribute));
}

// /////////////////////////////////////////////////////////////////
// dtkSearchBox
// /////////////////////////////////////////////////////////////////

class dtkSearchBoxPrivate
{
public:
    dtkSearchBoxMac *search;
};

dtkSearchBox::dtkSearchBox(QWidget *parent) : QWidget(parent), d(new dtkSearchBoxPrivate)
{
    d->search = new dtkSearchBoxMac(this);

    connect(d->search, SIGNAL(textChanged(const QString&, const QString&)), this, SIGNAL(textChanged(const QString&, const QString&)));
    connect(d->search, SIGNAL(textChanged(const QString&)),                 this, SIGNAL(textChanged(const QString&)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->search);
}

dtkSearchBox::~dtkSearchBox(void)
{
    delete d;

    d = NULL;
}

void dtkSearchBox::setMenu(QMenu *menu)
{
    d->search->setMenu(menu);
}

void dtkSearchBox::setFocus(void)
{
    d->search->setFocus();
}

// /////////////////////////////////////////////////////////////////
// dtkSearchBoxAction
// /////////////////////////////////////////////////////////////////

dtkSearchBoxAction::dtkSearchBoxAction(const QString& text, QObject *parent) : QWidgetAction(parent), widget(NULL)
{
    this->setText(text);
}

dtkSearchBoxAction::~dtkSearchBoxAction(void)
{

}

QWidget *dtkSearchBoxAction::createWidget(QWidget *parent)
{
    if(!widget)
	widget = new dtkSearchBox(parent);
    
    connect(widget, SIGNAL(textChanged(const QString&, const QString&)), this, SIGNAL(textChanged(const QString&, const QString&)));
    connect(widget, SIGNAL(textChanged(const QString&)),                 this, SIGNAL(textChanged(const QString&)));

    return widget;
}

void dtkSearchBoxAction::setFocus(void)
{
    if (widget)
	widget->setFocus();
}
