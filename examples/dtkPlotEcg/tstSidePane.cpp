/* tstSidePane.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  8 09:43:47 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Sun Jun 10 00:55:42 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 135
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
    QPushButton *zooming_back;
    QPushButton *zooming_forw;
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

    QFormLayout *panning_layout = new QFormLayout;

    QGroupBox *panning_group = new QGroupBox("Panning", this);
    panning_group->setCheckable(true);
    panning_group->setChecked(false);
    panning_group->setLayout(panning_layout);

    d->zooming_back = new QPushButton("Zoom backward", this);
    d->zooming_back->setEnabled(false);

    d->zooming_forw = new QPushButton("Zoom forward", this);
    d->zooming_forw->setEnabled(false);

    QFormLayout *zooming_layout = new QFormLayout;
    zooming_layout->addRow(d->zooming_back);
    zooming_layout->addRow(d->zooming_forw);

    QGroupBox *zooming_group = new QGroupBox("Zooming", this);
    zooming_group->setCheckable(true);
    zooming_group->setChecked(false);
    zooming_group->setLayout(zooming_layout);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(canvas_group);
    layout->addWidget(curve_group);
    layout->addWidget(panning_group);
    layout->addWidget(zooming_group);
    layout->addStretch(1);

    connect(bg_color_button, SIGNAL(colorChanged(const QColor&)), this, SIGNAL(backgroundColorChanged(const QColor&)));
    connect(fg_color_button, SIGNAL(colorChanged(const QColor&)), this, SIGNAL(foregroundColorChanged(const QColor&)));

    connect(curve_render_combo, SIGNAL(currentIndexChanged(int)), this, SIGNAL(curveRenderModeChanged(int)));

    connect(panning_group, SIGNAL(toggled(bool)), this, SIGNAL(activatePanning(bool)));
    connect(zooming_group, SIGNAL(toggled(bool)), this, SIGNAL(activateZooming(bool)));

    connect(d->zooming_forw, SIGNAL(clicked()), this, SIGNAL(zoomForward()));
    connect(d->zooming_back, SIGNAL(clicked()), this, SIGNAL(zoomBackward()));
}

tstSidePane::~tstSidePane(void)
{
    delete d;

    d = NULL;
}

void tstSidePane::setZoomForwardEnabled(bool enabled)
{
    d->zooming_forw->setEnabled(enabled);
}

void tstSidePane::setZoomBackwardEnabled(bool enabled)
{
    d->zooming_back->setEnabled(enabled);
}
