/* dtk3DQuickItem.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr  3 14:57:36 2013 (+0200)
 * Version: 
 * Last-Updated: Thu Apr  4 10:07:25 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 22
 */

/* Change Log:
 * 
 */

#include "dtk3DQuickItem.h"

class dtk3DQuickItemPrivate
{
public:
    dtk3DItem *item;
};

dtk3DQuickItem::dtk3DQuickItem(QObject *parent) : QObject(parent), d(new dtk3DQuickItemPrivate)
{
    d->item = new dtk3DItem(this);
}

dtk3DQuickItem::~dtk3DQuickItem(void)
{

}

dtk3DItem *dtk3DQuickItem::item(void)
{
    return d->item;
}
