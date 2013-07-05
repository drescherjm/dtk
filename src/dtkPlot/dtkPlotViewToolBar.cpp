/* dtkPlotViewToolBar.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:55:56 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jul  5 11:08:29 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 379
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotViewToolBar.h"

#include "dtkPlotView.h"
#include "dtkPlotRenderer.h"

#include <dtkGui/dtkSpacer.h>

class dtkPlotViewToolBarPrivate
{
public:
    QAction *defaultViewAction;
    QAction *pickingAction;
    QAction *zoomAction;
    QAction *gridAction;
    QAction *legendAction;
    QAction *exportAction;

    dtkPlotView *view;
};

dtkPlotViewToolBar::dtkPlotViewToolBar(dtkPlotView *parent) : QToolBar(), d(new dtkPlotViewToolBarPrivate())
{
    // View

    d->view = parent;

   // Default view

    d->defaultViewAction = new QAction("Default view",this);
    d->defaultViewAction->setToolTip("Show default view");
    d->defaultViewAction->setIcon(QPixmap(":dtkPlot/pixmaps/dtkAxis.png"));

    // Grid

    d->gridAction = new QAction("Grid",this);
    d->gridAction->setCheckable(true);
    d->gridAction->setChecked(false);
    d->gridAction->setToolTip("Draw grid coodinates");
    d->gridAction->setIcon(QPixmap(":dtkPlot/pixmaps/dtkGrid.png"));

    // Picking

    d->pickingAction = new QAction("Picking",this);
    d->pickingAction->setCheckable(true);
    d->pickingAction->setChecked(false);
    d->pickingAction->setToolTip("Activate picking");
    d->pickingAction->setIcon(QPixmap(":dtkPlot/pixmaps/dtkPicking.png"));

    // Zoom

    d->zoomAction = new QAction("Zoom",this);
    d->zoomAction->setCheckable(true);
    d->zoomAction->setChecked(false);
    d->zoomAction->setToolTip("Activate zoom");
    d->zoomAction->setIcon(QPixmap(":dtkPlot/pixmaps/dtkZoom.png"));

    // Legend

    d->legendAction = new QAction("Legend",this);
    d->legendAction->setCheckable(true);
    d->legendAction->setChecked(false);
    d->legendAction->setToolTip("Activate legend");
    d->legendAction->setIcon(QPixmap(":dtkPlot/pixmaps/dtkLegend.png"));

    // Export view

    d->exportAction = new QAction("Export...",this);
    d->exportAction->setToolTip("Export view");
    d->exportAction->setIcon(QPixmap(":dtkPlot/pixmaps/dtkExport.png"));

    // Actions

    this->addWidget(new dtkSpacer);
    this->addAction(d->defaultViewAction);
    this->addAction(d->zoomAction);
    this->addAction(d->gridAction);
    this->addAction(d->pickingAction);
    this->addAction(d->legendAction);
    this->addWidget(new dtkSpacer);
    this->addAction(d->exportAction);

    // Behaviour

    connect(d->defaultViewAction, SIGNAL(triggered(bool)), this, SLOT(onDefaultView()));
    connect(d->zoomAction, SIGNAL(triggered(bool)), this, SLOT(onZoomActivated(bool)));
    connect(d->gridAction, SIGNAL(triggered(bool)), this, SLOT(onGridActivated(bool)));
    connect(d->pickingAction, SIGNAL(triggered(bool)), this, SLOT(onPickingActivated(bool)));
    connect(d->legendAction, SIGNAL(triggered(bool)), this, SLOT(onLegendActivated(bool)));
    connect(d->exportAction, SIGNAL(triggered()), this, SLOT(onExport()));

    // General

    this->setFloatable(false);
    this->setIconSize(QSize(24, 24));
    this->setMovable(false);
    this->setOrientation(Qt::Horizontal);
    this->setFixedHeight(25);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

dtkPlotViewToolBar::~dtkPlotViewToolBar(void)
{
    delete d;

    d = NULL;
}

void dtkPlotViewToolBar::onDefaultView(void)
{
    d->view->updateAxes();
}

void dtkPlotViewToolBar::onPickingActivated(bool value)
{
    if (value) {
        d->view->activatePicking();
    } else {
        d->view->deactivatePicking();
    }
}

void dtkPlotViewToolBar::onZoomActivated(bool value)
{
    if (value) {
        d->view->activateZooming();
    } else {
        d->view->deactivateZooming();
    }
}

void dtkPlotViewToolBar::onGridActivated(bool value)
{
    if (value) {
        d->view->activateGrid();
    } else {
        d->view->deactivateGrid();
    }
}

void dtkPlotViewToolBar::onLegendActivated(bool value)
{
    if (value) {
        d->view->activateLegend();
    } else {
        d->view->deactivateLegend();
    }
}

void dtkPlotViewToolBar::onExport(void)
{
    const QList<QByteArray> imageFormats = QImageWriter::supportedImageFormats();

    QStringList filters;
    filters += "PDF Documents (*.pdf)";
#ifndef QWT_NO_SVG
    filters += "SVG Documents (*.svg)";
#endif
    filters += "Postscript Documents (*.ps)";

    for(int i = 0; i < imageFormats.size(); i++) {
        QString imageFilter;
        imageFilter += imageFormats[i].toUpper();
        imageFilter += " (*.";
        imageFilter += imageFormats[i];
        imageFilter += ")";
        filters += imageFilter;
    }

    QFileDialog *dialog = new QFileDialog(0, "Export plot", QDir::homePath(), filters.join(";;"));
    dialog->setStyleSheet("background-color: none ; color: none; background: none;");
    dialog->setAcceptMode(QFileDialog::AcceptSave);
    dialog->setConfirmOverwrite(true);
    dialog->setFileMode(QFileDialog::AnyFile);

    QRegExp filter_regex(QLatin1String("(?:^\\*\\.(?!.*\\()|\\(\\*\\.)(\\w+)"));
    if (dialog->exec() == QDialog::Accepted) {
        QString fileName = dialog->selectedFiles().first();
        QFileInfo info(fileName);
        if (info.suffix().isEmpty() && !dialog->selectedNameFilter().isEmpty()) {
            if (filter_regex.indexIn(dialog->selectedNameFilter()) != -1) {
                QString extension = filter_regex.cap(1);
                fileName += QLatin1String(".") + extension;
            }
        }
        this->onExport(fileName);
    }
}

void dtkPlotViewToolBar::onExport(const QString& file)
{
    dtkPlotRenderer renderer;
    renderer.setView(d->view);
    renderer.setPath(file);
    renderer.setSize(QSize(300, 200));
    renderer.render();
}

