/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 15:31:59 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jul  6 16:38:37 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 205
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstPlotCurveEcg.h"
#include "tstMainWindow.h"
#include "tstSidePane.h"

#include <dtkGui/dtkAnchoredBar.h>

#include <dtkPlot/dtkPlotView.h>
#include <dtkPlot/dtkPlotRenderer.h>

class tstMainWindowPrivate
{
public:
    dtkPlotView *view;
    tstSidePane *pane;

public:
    tstPlotCurveEcg *curve;
};

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent), d(new tstMainWindowPrivate)
{
    d->curve = NULL;

    d->view = new dtkPlotView(this);

    d->view->setAxisTitleX("X axis title");
    d->view->setAxisTitleY("Y axis title");
    d->view->setAxisScaleX(0.0, 13.0);
    d->view->setAxisScaleY(0.0, 0.03);

    tstSidePane *pane = new tstSidePane(this);
    pane->setStyleSheet(
        "QFrame { background: #dce4eb; border-right: 1px solid #b4b4b4; }"
        "QLabel { background: none; }"
        "QToolButton { margin: 0px; padding 0px; border: 1px solid #b4b4b4; border-radius: 10px; min-width: 50px; }");

    QAction *load_action = new QAction("Load", this);
    load_action->setShortcut(Qt::ControlModifier + Qt::Key_O);

    QAction *export_action = new QAction("Export", this);
    export_action->setShortcut(Qt::ControlModifier + Qt::ShiftModifier + Qt::Key_E);

    dtkAnchoredBar *anchoredBar = new dtkAnchoredBar(pane);
    anchoredBar->addAction(load_action);
    anchoredBar->addSeparator();
    anchoredBar->addAction(export_action);
    anchoredBar->addSeparator();

    QVBoxLayout *side_layout = new QVBoxLayout;
    side_layout->setContentsMargins(0, 0, 0, 0);
    side_layout->setSpacing(0);
    side_layout->addWidget(pane);
    side_layout->addWidget(anchoredBar);

    QFrame *side = new QFrame(this);
    side->setLayout(side_layout);
    side->setMinimumWidth(100);
    side->setMaximumWidth(300);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(side);
    layout->addWidget(d->view);

    QWidget *main = new QWidget(this);
    main->setLayout(layout);

    this->setCentralWidget(main);
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setWindowTitle("dtkPlotEcg example");

    connect(load_action, SIGNAL(triggered()), this, SLOT(onLoad()));
    connect(export_action, SIGNAL(triggered()), this, SLOT(onExport()));

    connect(pane, SIGNAL(backgroundColorChanged(const QColor&)), this, SLOT(onBackgroundColorChanged(const QColor&)));
    connect(pane, SIGNAL(foregroundColorChanged(const QColor&)), this, SLOT(onForegroundColorChanged(const QColor&)));

    connect(pane, SIGNAL(curveRenderModeChanged(int)), this, SLOT(onCurveRenderModeChanged(int)));
}

tstMainWindow::~tstMainWindow(void)
{
    delete d;

    d = NULL;
}

void tstMainWindow::onBackgroundColorChanged(const QColor& color)
{
    d->view->setBackgroundColor(color);
    d->view->update();
}

void tstMainWindow::onForegroundColorChanged(const QColor& color)
{
    if (d->curve)
        d->curve->setColor(color);

    d->view->update();
}

void tstMainWindow::onCurveRenderModeChanged(int mode)
{
    if (d->curve)
        d->curve->setAntialiased(mode);

    d->view->update();
}

void tstMainWindow::onLoad(void)
{
    if(d->curve)
        return;

    d->curve = new tstPlotCurveEcg("ECG");

    (*(d->view)) << d->curve;

    connect(d->curve, SIGNAL(updated()), d->view, SLOT(update()));

    d->curve->read(":dtkPlotEcg/data");
}

void tstMainWindow::onExport(void)
{
    QString fileName = "dtk_plot.pdf";

    const QList<QByteArray> imageFormats = QImageWriter::supportedImageFormats();

    QStringList filter;
    filter += "PDF Documents (*.pdf)";
#ifndef QWT_NO_SVG
    filter += "SVG Documents (*.svg)";
#endif
    filter += "Postscript Documents (*.ps)";

    if(imageFormats.size() > 0) {
        QString imageFilter("Images (");
        for(int i = 0; i < imageFormats.size(); i++) {
            if(i>0)
                imageFilter += " ";
            imageFilter += "*.";
            imageFilter += imageFormats[i];
        }
        imageFilter += ")";
        filter += imageFilter;
    }
    
    QFileDialog *dialog = new QFileDialog(this, "Export plot", QDir::homePath(), filter.join(";;"));
    dialog->setAcceptMode(QFileDialog::AcceptSave);
    dialog->setConfirmOverwrite(true);
    dialog->setFileMode(QFileDialog::AnyFile);
    dialog->open(this, SLOT(onExport(const QString&)));
}

void tstMainWindow::onExport(const QString& file)
{
    dtkPlotRenderer renderer;
    renderer.setView(d->view);
    renderer.setPath(file);
    renderer.setSize(QSize(300, 200));
    renderer.render();
}
