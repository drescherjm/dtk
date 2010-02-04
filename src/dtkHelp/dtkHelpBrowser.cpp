/* dtkHelpBrowser.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb  3 15:56:38 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  3 17:52:56 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkHelpBrowser.h"
#include "dtkHelpController.h"

#include <dtkCore/dtkLog.h>

class dtkHelpBrowserPrivate
{
public:
};

dtkHelpBrowser::dtkHelpBrowser(QWidget *parent) : QTextBrowser(parent), d(new dtkHelpBrowserPrivate)
{

}

dtkHelpBrowser::~dtkHelpBrowser(void)
{
    delete d;

    d = NULL;
}

QVariant dtkHelpBrowser::loadResource(int type, const QUrl &url)
{
    if(!dtkHelpController::instance()->engine())
        dtkWarning() << "dtkHelp engine not set up correctly. Has dtkHelpController been initialized?";

    if (url.scheme() == "qthelp")
        return QVariant(dtkHelpController::instance()->engine()->fileData(url));
    else
        return QTextBrowser::loadResource(type, url);
}
