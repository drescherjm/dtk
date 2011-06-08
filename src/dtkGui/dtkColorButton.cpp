/* dtkColorButton.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Mar 18 14:45:33 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jun  8 10:56:58 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 38
 */

/* Commentary: 
 * See credits at EOF
 */

/* Change log:
 * 
 */

#include "dtkColorButton.h"
#include "dtkColorGrid.h"
#include "dtkPopup.h"

#include <QtGui>

class dtkColorButtonPrivate
{
public:
    QColor color;

    dtkColorButton::PickMode modeLeft;
    dtkColorButton::PickMode modeRight;

    int cellSize;

    dtkColorList *colors;
};

dtkColorButton::dtkColorButton(QWidget *parent) : QToolButton(parent), d(new dtkColorButtonPrivate)
{
    d->modeLeft = PM_COLORGRID;
    d->modeRight = PM_NONE;
    d->cellSize = 12;
    d->colors = 0;

    setColor(Qt::white);
}

dtkColorButton::~dtkColorButton(void)
{
    delete d;

    d = NULL;
}

int dtkColorButton::cellSize(void) const
{
    return d->cellSize;
}

const QColor& dtkColorButton::color(void) const
{
    return d->color;
}

const dtkColorButton::PickMode& dtkColorButton::pickModeLeft(void) const
{
    return d->modeLeft;
}

const dtkColorButton::PickMode& dtkColorButton::pickModeRight(void) const
{
    return d->modeRight;
}

dtkColorList* dtkColorButton::scheme(void) const
{
    return d->colors;
}

void dtkColorButton::setColor(const QColor& color)
{
    d->color = color;

    int w = qMax(size().width(), size().height());
    QPixmap pm(w,w);
    drawColorItem(pm, color);
    setIcon(QIcon(pm));

    setText(color.name());
}

void dtkColorButton::drawColorItem(QPixmap &pm, const QColor& color)
{
    QPainter p(&pm);
    p.setBrush(color);
    p.setPen(palette().color(QPalette::Shadow));
    p.drawRect(pm.rect().adjusted(0,0,-1,-1));
}

void dtkColorButton::setPickModeLeft(const PickMode& mode)
{
    d->modeLeft = mode;
}

void dtkColorButton::setPickModeRight(const PickMode& mode)
{
    d->modeRight = mode;
}

void dtkColorButton::resizeEvent ( QResizeEvent * event )
{
    setColor(d->color);
}

void dtkColorButton::mousePressEvent ( QMouseEvent * event )
{
    QToolButton::mousePressEvent(event);

    event->accept();
    setDown(false);

    int mod;

    switch (event->button()) {
        case Qt::LeftButton:
            mod = d->modeLeft;
            break;
        case Qt::RightButton:
            mod = d->modeRight;
            break;
        default:
            return;
    }

    switch (mod)
    {
        case PM_COLORDIALOG:
        {
            QColor c = QColorDialog::getColor(d->color, this);
            if (c.isValid()) {
                setColor(c);
                emit colorChanged(c);
            }
        }
        break;

        case PM_COLORGRID:
        {
            dtkColorGrid *grid = new dtkColorGrid;
            grid->setPickByDrag(false);
            grid->setClickMode(dtkColorGrid::CM_RELEASE);
            grid->setAutoSize(true);
            grid->setScheme(d->colors);
            grid->setCellSize(d->cellSize);
            connect(grid, SIGNAL(picked(const QColor &)), this, SLOT(setColor(const QColor&)));
            connect(grid, SIGNAL(picked(const QColor &)), this, SIGNAL(colorChanged(const QColor&)));

            dtkPopup *popup = new dtkPopup;
            popup->setWidget(grid);
            popup->show(mapToGlobal(rect().bottomLeft()));

            connect(grid, SIGNAL(accepted()), popup, SLOT(close()));
        }
        break;

        default:;
    }
}

void dtkColorButton::setScheme(dtkColorList *scheme)
{
    d->colors = scheme;
}

void dtkColorButton::setCellSize(int size)
{
    d->cellSize = size;
}

// /////////////////////////////////////////////////////////////////
// Credits
// /////////////////////////////////////////////////////////////////

/* QSint library. */
