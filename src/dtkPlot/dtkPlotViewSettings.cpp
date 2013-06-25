/* dtkPlotViewSettings.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jun  8 12:55:56 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 25 16:46:14 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 494
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotViewSettings.h"

#include "dtkPlotView.h"
#include "dtkPlotCurve.h"

#include <dtkGui/dtkColorButton.h>

class dtkPlotViewSettingsPrivate
{
public:
    QLineEdit *mainTitle;
    QLineEdit *axisTitleX;
    QLineEdit *axisTitleY;

    QSpinBox *titleSize;
    QSpinBox *axesTitleSize;

    QGroupBox *legendGroup;
    QComboBox *legendPosition;

    dtkColorButton *gridColor;
    dtkColorButton *pickingColor;
    dtkColorButton *zoomColor;

    dtkColorButton *backgroundColor;
    dtkColorButton *foregroundColor;

    QList<QGroupBox *> groupBoxesList;

    QFormLayout *curvesNameLayout;
    QGroupBox *curvesNameGroup;

    QFormLayout *curvesColorLayout;
    QGroupBox *curvesColorGroup;

    dtkPlotView *view;

    QSignalMapper *mapperCurvesName;
    QSignalMapper *mapperCurvesColor;
};

dtkPlotViewSettings::dtkPlotViewSettings(QWidget *parent) : QFrame(), d(new dtkPlotViewSettingsPrivate())
{
    // View

    d->view = NULL;

    // Titles

    d->mainTitle = new QLineEdit;
    d->mainTitle->setAlignment(Qt::AlignLeft);
    d->axisTitleX = new QLineEdit;
    d->axisTitleX->setAlignment(Qt::AlignLeft);
    d->axisTitleY = new QLineEdit;
    d->axisTitleY->setAlignment(Qt::AlignLeft);

    QFormLayout *titlesLayout = new QFormLayout;
    titlesLayout->setContentsMargins(2, 15, 2, 0);
    titlesLayout->setSpacing(0);
    titlesLayout->addRow("Main", d->mainTitle);
    titlesLayout->addRow("X-axis", d->axisTitleX);
    titlesLayout->addRow("Y-axis", d->axisTitleY);

    QGroupBox *titlesGroup = new QGroupBox("Titles");
    titlesGroup->setLayout(titlesLayout);

    d->groupBoxesList << titlesGroup;

    // Sizes

    d->titleSize = new QSpinBox;
    d->titleSize->setRange(8, 25);
    d->titleSize->setValue(20);
    d->titleSize->setSuffix("px");
    d->titleSize->setFocusPolicy(Qt::StrongFocus);
    d->titleSize->setAlignment(Qt::AlignRight);
    d->titleSize->setAttribute(Qt::WA_MacShowFocusRect, false);

    d->axesTitleSize = new QSpinBox;
    d->axesTitleSize->setRange(8, 25);
    d->axesTitleSize->setValue(15);
    d->axesTitleSize->setSuffix("px");
    d->axesTitleSize->setFocusPolicy(Qt::StrongFocus);
    d->axesTitleSize->setAlignment(Qt::AlignRight);
    d->axesTitleSize->setAttribute(Qt::WA_MacShowFocusRect, false);

    QFormLayout *sizesLayout = new QFormLayout;
    sizesLayout->setContentsMargins(2, 15, 2, 0);
    sizesLayout->setSpacing(0);
    sizesLayout->addRow("Title", d->titleSize);
    sizesLayout->addRow("Axes title", d->axesTitleSize);

    QGroupBox *sizesGroup = new QGroupBox("Sizes");
    sizesGroup->setLayout(sizesLayout);

    d->groupBoxesList << sizesGroup;

    // Legend

    QStringList legendPositionList = QStringList() << "Left" << "Right" << "Bottom" << "Top";
    d->legendPosition = new QComboBox;
    d->legendPosition->addItems(legendPositionList);
    d->legendPosition->setCurrentIndex(1);
    d->legendPosition->setFocusPolicy(Qt::NoFocus);

    QFormLayout *legendLayout = new QFormLayout;
    legendLayout->setContentsMargins(2, 15, 2, 0);
    legendLayout->setSpacing(0);
    legendLayout->addRow("Position", d->legendPosition);

    d->legendGroup = new QGroupBox("Legend");
    d->legendGroup->setLayout(legendLayout);

    d->groupBoxesList << d->legendGroup;

    // Curves name

    d->curvesNameGroup = new QGroupBox("Curves name");

    d->groupBoxesList << d->curvesNameGroup;

    d->mapperCurvesName = new QSignalMapper;

    // Curves color

    d->curvesColorGroup = new QGroupBox("Curves color");

    d->groupBoxesList << d->curvesColorGroup;

    d->mapperCurvesColor = new QSignalMapper;

    // Colors

    d->gridColor = new dtkColorButton;

    d->pickingColor = new dtkColorButton;

    d->zoomColor = new dtkColorButton;

    d->backgroundColor = new dtkColorButton;
    d->foregroundColor = new dtkColorButton;

    QFormLayout *colorsLayout = new QFormLayout;
    colorsLayout->setContentsMargins(2, 15, 2, 0);
    colorsLayout->setSpacing(0);
    colorsLayout->addRow("Grid", d->gridColor);
    colorsLayout->addRow("Picking", d->pickingColor);
    colorsLayout->addRow("Zoom", d->zoomColor);
    colorsLayout->addRow("Background", d->backgroundColor);
    colorsLayout->addRow("Foreground", d->foregroundColor);

    QGroupBox *colorsGroup = new QGroupBox("Colors");
    colorsGroup->setLayout(colorsLayout);

    d->groupBoxesList << colorsGroup;

    // Data layout

    QFrame *frameData = new QFrame;
    QVBoxLayout *dataLayout = new QVBoxLayout(frameData);
    dataLayout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    dataLayout->setContentsMargins(2, 0, 2, 0);
    dataLayout->setSpacing(0);
    foreach(QGroupBox* groupBox, d->groupBoxesList) {
        dataLayout->addWidget(groupBox);
    }

    // Scroll Area

    QScrollArea *areaData = new QScrollArea;
    areaData->setAttribute(Qt::WA_MacShowFocusRect, false);
    areaData->setFrameShape(QFrame::NoFrame);
    areaData->setContentsMargins(0, 0, 0, 0);
    areaData->setWidgetResizable(true);
    areaData->setWidget(frameData);
    areaData->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    areaData->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Main layout

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(areaData);

    // Behaviour

    connect(d->mainTitle, SIGNAL(returnPressed()), this, SLOT(onMainTitleChanged()));
    connect(d->axisTitleX, SIGNAL(returnPressed()), this, SLOT(onAxisTitleXChanged()));
    connect(d->axisTitleY, SIGNAL(returnPressed()), this, SLOT(onAxisTitleYChanged()));

    connect(d->titleSize, SIGNAL(valueChanged(const int&)), this, SLOT(onTitleSizeChanged(const int&)));
    connect(d->axesTitleSize, SIGNAL(valueChanged(const int&)), this, SLOT(onAxesTitleSizeChanged(const int&)));

    connect(d->legendPosition, SIGNAL(currentIndexChanged(const int&)), this, SLOT(onLegendPositionChanged(const int&)));

    connect(d->mapperCurvesName, SIGNAL(mapped(int)), this, SLOT(updateCurveName(int)));
    connect(d->mapperCurvesColor, SIGNAL(mapped(int)), this, SLOT(updateCurveColor(int)));

    connect(d->gridColor, SIGNAL(colorChanged(const QColor&)), this, SLOT(onGridColorChanged(const QColor&)));
    connect(d->pickingColor, SIGNAL(colorChanged(const QColor&)), this, SLOT(onPickingColorChanged(const QColor&)));
    connect(d->zoomColor, SIGNAL(colorChanged(const QColor&)), this, SLOT(onZoomColorChanged(const QColor&)));

    connect(d->backgroundColor, SIGNAL(colorChanged(const QColor&)), this, SLOT(onBackgroundColorChanged(const QColor&)));
    connect(d->foregroundColor, SIGNAL(colorChanged(const QColor&)), this, SLOT(onForegroundColorChanged(const QColor&)));

    // General

    this->setStyleSheet(dtkReadFile(":dtkPlot/dtkPlotView.qss"));
}

dtkPlotViewSettings::~dtkPlotViewSettings(void)
{
    delete d;

    d = NULL;
}

void dtkPlotViewSettings::setView(dtkPlotView *view)
{
    d->view = view;

    connect(d->view, SIGNAL(updated()), this, SLOT(update()));

    this->update();
}

void dtkPlotViewSettings::onMainTitleChanged(void)
{
    d->view->setTitle(d->mainTitle->text());
}

void dtkPlotViewSettings::onAxisTitleXChanged(void)
{
    d->view->setAxisTitleX(d->axisTitleX->text());
}

void dtkPlotViewSettings::onAxisTitleYChanged(void)
{
    d->view->setAxisTitleY(d->axisTitleY->text());
}

void dtkPlotViewSettings::onTitleSizeChanged(const int& value)
{
    d->view->setTitleSize(value);
}

void dtkPlotViewSettings::onAxesTitleSizeChanged(const int& value)
{
    d->view->setAxisTitleSizeX(value);
    d->view->setAxisTitleSizeY(value);
}

void dtkPlotViewSettings::onLegendPositionChanged(const int& index)
{
    d->view->setLegendPosition((dtkPlotView::LegendPosition)index);
    d->view->update();
}

void dtkPlotViewSettings::onGridColorChanged(const QColor& color)
{
    d->view->setGridColor(d->gridColor->color());
    d->view->update();
}

void dtkPlotViewSettings::onPickingColorChanged(const QColor& color)
{
    d->view->setPickingColor(d->pickingColor->color());
    d->view->update();
}

void dtkPlotViewSettings::onZoomColorChanged(const QColor& color)
{
    d->view->setZoomColor(d->zoomColor->color());
    d->view->update();
}

void dtkPlotViewSettings::onBackgroundColorChanged(const QColor& color)
{
    d->view->setBackgroundColor(d->backgroundColor->color());
}

void dtkPlotViewSettings::onForegroundColorChanged(const QColor& color)
{
    d->view->setForegroundColor(d->foregroundColor->color());
}

void dtkPlotViewSettings::onRandomColorsClicked(void)
{
    int index = 0;
    foreach (dtkPlotCurve *curve, d->view->curves()) {

        QColor color = QColor::fromHsv(qrand() % 256, 255, 190);

        QLayoutItem *item = d->curvesColorLayout->itemAt(index+2, QFormLayout::FieldRole);

        dtkColorButton *button = dynamic_cast<dtkColorButton *>(item->widget());
        button->setColor(color);

        curve->setColor(color);

        index++;
    }

    this->onColorAreaChanged(d->view->alphaCurveArea());

    d->view->update();
}

void dtkPlotViewSettings::onColorAreaChanged(const int& value)
{
    d->view->fillCurveArea(value);
}

QColor dtkPlotViewSettings::gridColor(void) const
{
    return d->gridColor->color();
}

QColor dtkPlotViewSettings::pickingColor(void) const
{
    return d->pickingColor->color();
}

QColor dtkPlotViewSettings::zoomColor(void) const
{
    return d->zoomColor->color();
}

void dtkPlotViewSettings::update(void)
{
    if (!d->view)
        return;

    d->mainTitle->setText(d->view->title());
    d->axisTitleX->setText(d->view->axisTitleX());
    d->axisTitleY->setText(d->view->axisTitleY());

    d->titleSize->setValue(d->view->titleSize());
    d->axesTitleSize->setValue(d->view->axisTitleSizeX());

    d->gridColor->setColor(d->view->gridColor());
    d->pickingColor->setColor(d->view->pickingColor());
    d->zoomColor->setColor(d->view->zoomColor());
    d->backgroundColor->setColor(d->view->backgroundColor());
    d->foregroundColor->setColor(d->view->foregroundColor());

    this->updateCurves();
}

void dtkPlotViewSettings::updateCurves(void)
{
    QList<dtkPlotCurve *> curves = d->view->curves();

    int numberOfCurves = curves.count();

    if (numberOfCurves==0) {
        d->curvesNameGroup->setVisible(false);
        d->curvesColorGroup->setVisible(false);
        return;
    }

    d->curvesNameGroup->setVisible(true);
    d->curvesColorGroup->setVisible(true);

    if (d->curvesNameLayout && numberOfCurves==d->curvesNameLayout->rowCount()) {
        for (int i = 0; i<numberOfCurves; i++) {
            QLayoutItem *item = d->curvesNameLayout->itemAt(i, QFormLayout::FieldRole);
            QLineEdit *lineedit = dynamic_cast<QLineEdit *>(item->widget());
            lineedit->setText(curves[i]->name());

            item = d->curvesColorLayout->itemAt(i+2, QFormLayout::FieldRole);
            dtkColorButton *button = dynamic_cast<dtkColorButton *>(item->widget());
            button->setColor(curves[i]->color());
        }
        return;
    }

    if (d->curvesNameLayout)
        QWidget().setLayout(d->curvesNameLayout);
    d->curvesNameLayout = new QFormLayout;
    d->curvesNameLayout->setContentsMargins(2, 15, 2, 0);
    d->curvesNameLayout->setSpacing(0);
    d->curvesNameGroup->setLayout(d->curvesNameLayout);

    if (d->curvesColorLayout)
        QWidget().setLayout(d->curvesColorLayout);
    d->curvesColorLayout = new QFormLayout;
    d->curvesColorLayout->setContentsMargins(2, 15, 2, 0);
    d->curvesColorLayout->setSpacing(0);
    d->curvesColorGroup->setLayout(d->curvesColorLayout);

    QPushButton *random = new QPushButton("Apply");
    random->setFocusPolicy(Qt::NoFocus);
    d->curvesColorLayout->addRow("Random", random);

    QSpinBox *alphaCurveArea = new QSpinBox;
    alphaCurveArea->setRange(0, 255);
    alphaCurveArea->setValue(d->view->alphaCurveArea());
    alphaCurveArea->setFocusPolicy(Qt::StrongFocus);
    alphaCurveArea->setAlignment(Qt::AlignRight);
    alphaCurveArea->setAttribute(Qt::WA_MacShowFocusRect, false);
    d->curvesColorLayout->addRow("Alpha color area", alphaCurveArea);

    for (int i = 0; i<numberOfCurves; i++) {
        QString name = "Curve " + QString::number(i+1);
        dtkPlotCurve *curve = curves[i];

        QString title = curve->name();
        QLineEdit *entry = new QLineEdit(title);
        entry->setAlignment(Qt::AlignLeft);

        d->curvesNameLayout->addRow(name, entry);

        connect(entry, SIGNAL(editingFinished()), d->mapperCurvesName, SLOT(map()));
        d->mapperCurvesName->setMapping(entry, i);

        QColor color = curve->color();
        dtkColorButton *button = new dtkColorButton;
        button->setColor(color);
        d->curvesColorLayout->addRow(name, button);

        connect(button, SIGNAL(colorChanged(const QColor&)), d->mapperCurvesColor, SLOT(map()));
        d->mapperCurvesColor->setMapping(button, i);
    }

    connect(random, SIGNAL(clicked()), this, SLOT(onRandomColorsClicked()));
    connect(alphaCurveArea, SIGNAL(valueChanged(const int&)), this, SLOT(onColorAreaChanged(const int&)));
}

void dtkPlotViewSettings::updateCurveName(int index)
{
    QList<dtkPlotCurve *> curves = d->view->curves();

    QString name = "Curve " + QString::number(index+1);

    QLayoutItem *item = d->curvesNameLayout->itemAt(index, QFormLayout::FieldRole);

    QLineEdit *lineedit = dynamic_cast<QLineEdit *>(item->widget());

    curves[index]->setName(lineedit->text());

    d->view->update();
}

void dtkPlotViewSettings::updateCurveColor(int index)
{
    QList<dtkPlotCurve *> curves = d->view->curves();

    QLayoutItem *item = d->curvesColorLayout->itemAt(index+2, QFormLayout::FieldRole);

    dtkColorButton *button = dynamic_cast<dtkColorButton *>(item->widget());

    curves[index]->setColor(button->color());

    this->onColorAreaChanged(d->view->alphaCurveArea());

    d->view->update();
}

