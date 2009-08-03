/* dtkAbstractViewFactory.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:48:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jul 31 23:42:35 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 92
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKABSTRACTVIEWERFACTORY_H
#define DTKABSTRACTVIEWERFACTORY_H

#include <dtkCore/dtkAbstractFactory.h>

class dtkAbstractView;
class dtkAbstractViewAnimator;
class dtkAbstractViewNavigator;
class dtkAbstractViewInteractor;
class dtkAbstractViewFactoryPrivate;

class DTKCORE_EXPORT dtkAbstractViewFactory : public dtkAbstractFactory
{
    Q_OBJECT

public:
    typedef dtkAbstractView           *(*dtkAbstractViewCreator)          (void);
    typedef dtkAbstractViewAnimator   *(*dtkAbstractViewAnimatorCreator)  (void);
    typedef dtkAbstractViewNavigator  *(*dtkAbstractViewNavigatorCreator) (void);
    typedef dtkAbstractViewInteractor *(*dtkAbstractViewInteractorCreator)(void);

    typedef QHash<               QString,      dtkAbstractViewCreator>           dtkAbstractViewCreatorHash;
    typedef QHash<QPair<QString, QStringList>, dtkAbstractViewAnimatorCreator>   dtkAbstractViewAnimatorCreatorHash;
    typedef QHash<QPair<QString, QStringList>, dtkAbstractViewNavigatorCreator>  dtkAbstractViewNavigatorCreatorHash;
    typedef QHash<QPair<QString, QStringList>, dtkAbstractViewInteractorCreator> dtkAbstractViewInteractorCreatorHash;

    typedef       QPair<QString, QStringList>  dtkAbstractViewTypeHandler;

public:
    static dtkAbstractViewFactory *instance(void);

    bool registerViewType          (QString type,                      dtkAbstractViewCreator           func);
    bool registerViewAnimatorType  (QString type, QStringList handled, dtkAbstractViewAnimatorCreator   func);
    bool registerViewNavigatorType (QString type, QStringList handled, dtkAbstractViewNavigatorCreator  func);
    bool registerViewInteractorType(QString type, QStringList handled, dtkAbstractViewInteractorCreator func);

    unsigned int size(QString type);

    dtkAbstractView *get(QString type, int index = 0);

public slots:
    dtkAbstractView *create(QString type);

    dtkAbstractViewAnimator *animator(QString type);
    dtkAbstractViewNavigator *navigator(QString type);
    dtkAbstractViewInteractor *interactor(QString type);

protected:
     dtkAbstractViewFactory(void);
    ~dtkAbstractViewFactory(void);

private:    
    static dtkAbstractViewFactory *s_instance;

private:
    dtkAbstractViewFactoryPrivate *d;
};

#endif
