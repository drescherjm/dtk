/* dtkAbstractViewFactory.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:48:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Sep 11 13:34:25 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 96
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

    bool registerViewType          (const QString& type,                      dtkAbstractViewCreator           func);
    bool registerViewAnimatorType  (const QString& type, const QStringList& handled, dtkAbstractViewAnimatorCreator   func);
    bool registerViewNavigatorType (const QString& type, const QStringList& handled, dtkAbstractViewNavigatorCreator  func);
    bool registerViewInteractorType(const QString& type, const QStringList& handled, dtkAbstractViewInteractorCreator func);

    unsigned int size(const QString& type) const;

    dtkAbstractView *get(const QString& type, int index = 0);
    dtkAbstractView *get(const QString& type, const QString& name);

signals:
    void created(dtkAbstractView *view, const QString& type);

public slots:
    dtkAbstractView *create(const QString& type);

    dtkAbstractViewAnimator *animator(const QString& type);
    dtkAbstractViewNavigator *navigator(const QString& type);
    dtkAbstractViewInteractor *interactor(const QString& type);

protected:
     dtkAbstractViewFactory(void);
    ~dtkAbstractViewFactory(void);

private:    
    static dtkAbstractViewFactory *s_instance;

private:
    dtkAbstractViewFactoryPrivate *d;
};

#endif
