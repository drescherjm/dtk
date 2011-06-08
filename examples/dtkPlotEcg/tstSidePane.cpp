/* tstSidePane.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  8 09:43:47 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun  8 12:20:46 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 52
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstSidePane.h"

#include <dtkGui/dtkColorButton.h>

#include <QtGui>

class tstSidePanePrivate
{
public:
};

tstSidePane::tstSidePane(QWidget *parent) : QFrame(parent), d(new tstSidePanePrivate)
{
    dtkColorButton *bg_color_button = new dtkColorButton(this);
    bg_color_button->setColor(Qt::white);

    dtkColorButton *fg_color_button = new dtkColorButton(this);
    fg_color_button->setColor(Qt::black);
    
    QComboBox *curve_render_combo = new QComboBox(this);
    curve_render_combo->addItem("Raw");
    curve_render_combo->addItem("Antialiased");
    curve_render_combo->setFocusPolicy(Qt::NoFocus);

    QFormLayout *canvas_layout = new QFormLayout;
    canvas_layout->addRow("Background color", bg_color_button);
    canvas_layout->addRow("Foreground color", fg_color_button);
    
    QGroupBox *canvas_group = new QGroupBox("Canvas", this);
    canvas_group->setLayout(canvas_layout);

    QFormLayout *curve_layout = new QFormLayout;
    curve_layout->addRow("Render hints", curve_render_combo);
    
    QGroupBox *curve_group = new QGroupBox("Curve", this);
    curve_group->setLayout(curve_layout);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(canvas_group);
    layout->addWidget(curve_group);
    layout->addStretch(1);

    connect(bg_color_button, SIGNAL(colorChanged(const QColor&)), this, SIGNAL(backgroundColorChanged(const QColor&)));
    connect(fg_color_button, SIGNAL(colorChanged(const QColor&)), this, SIGNAL(foregroundColorChanged(const QColor&)));

    connect(curve_render_combo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(curveRenderModeChanged(int)));
}

tstSidePane::~tstSidePane(void)
{
    delete d;

    d = NULL;
}
