/* dtkInterpreterPreferencesWidget.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 10 09:24:22 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Aug  6 10:24:27 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 54
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui>
#include <QtGui/QColorDialog>

#include <dtkGui/dtkInterpreter.h>
#include <dtkGui/dtkInterpreterPreferencesWidget.h>

#include "ui_dtkInterpreterPreferencesWidget.h"

class dtkInterpreterPreferencesWidgetPrivate
{
public:
    Ui::dtkInterpreterPreferencesWidget ui;

    dtkInterpreter *interpreter;

    QFont  font;
    QColor foregroundColor;
    QColor backgroundColor;
    int  backgroundOpacity;
};

dtkInterpreterPreferencesWidget::dtkInterpreterPreferencesWidget(dtkInterpreter *interpreter, QWidget *parent) : dtkPreferencesPage(parent)
{
    d = new dtkInterpreterPreferencesWidgetPrivate;
    d->interpreter     = interpreter;
    d->font            = interpreter->document()->defaultFont();
    d->foregroundColor = interpreter->foregroundColor();
    d->backgroundColor = interpreter->backgroundColor();
    d->backgroundOpacity = interpreter->backgroundOpacity();

    d->ui.setupUi(this);

    d->ui.fontComboBox->setFont(d->font);
    d->ui.sizeComboBox->setCurrentIndex(
            d->font.pointSize() ==  6 ? 0 :
            d->font.pointSize() ==  8 ? 1 :
            d->font.pointSize() ==  9 ? 2 :
            d->font.pointSize() == 10 ? 3 :
            d->font.pointSize() == 11 ? 4 :
            d->font.pointSize() == 12 ? 5 :
            d->font.pointSize() == 14 ? 6 :
            d->font.pointSize() == 16 ? 7 :
            d->font.pointSize() == 18 ? 8 : 5);

    { // -- Setting text color
    d->ui.textColorToolButton->setIconSize(d->ui.textColorToolButton->size());
    QPixmap pix(d->ui.textColorToolButton->minimumSize());
    pix.fill(d->foregroundColor);
    d->ui.textColorToolButton->setIcon(pix);
    } // -- Setting text color

    { // -- Setting background color
    d->ui.backgroundColorToolButton->setIconSize(d->ui.backgroundColorToolButton->size());
    QPixmap pix(d->ui.backgroundColorToolButton->minimumSize());
    pix.fill(d->backgroundColor);
    d->ui.backgroundColorToolButton->setIcon(pix);
    } // -- Setting background color

    { // -- Setting opacity
    d->ui.backgroundOpacitySlider->setValue(d->interpreter->backgroundOpacity());
    } // -- Setting opacity

    connect(d->ui.fontComboBox, SIGNAL(currentFontChanged(QFont)), this, SLOT(onFontChosen(QFont)));
    connect(d->ui.sizeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onSizeChosen(QString)));

    connect(d->ui.textColorToolButton, SIGNAL(clicked()), this, SLOT(onTextColorClicked()));
    connect(d->ui.backgroundColorToolButton, SIGNAL(clicked()), this, SLOT(onBackgroundColorClicked()));
    connect(d->ui.backgroundOpacitySlider, SIGNAL(valueChanged(int)), this, SLOT(onBackgroundOpacityChanged(int)));

    connect(d->ui.buttonBox, SIGNAL(accepted()), this, SLOT(onOkButtonClicked()));
    connect(d->ui.buttonBox, SIGNAL(rejected()), this, SLOT(onCancelButtonClicked()));
}

dtkInterpreterPreferencesWidget::~dtkInterpreterPreferencesWidget(void)
{

}

void dtkInterpreterPreferencesWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Escape:
        this->hide();
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        this->onOkButtonClicked();
        break;
    default:
        break;
    }
}

void dtkInterpreterPreferencesWidget::onFontChosen(QFont font)
{
    d->font = font;
}

void dtkInterpreterPreferencesWidget::onSizeChosen(QString size)
{
    d->font.setPointSize(size.toInt());
}

void dtkInterpreterPreferencesWidget::onTextColorClicked(void)
{
#if QT_VERSION >= 0x040500
    d->foregroundColor = QColorDialog::getColor(d->foregroundColor, this, "Choose text color");
#else
    d->foregroundColor = QColorDialog::getColor(d->foregroundColor, this);
#endif

    QPixmap pix(d->ui.textColorToolButton->size());
    pix.fill(d->foregroundColor);
    d->ui.textColorToolButton->setIcon(pix);
}

void dtkInterpreterPreferencesWidget::onBackgroundColorClicked(void)
{
#if QT_VERSION >= 0x040500
    d->backgroundColor = QColorDialog::getColor(d->backgroundColor, this, "Choose background color");
#else
    d->backgroundColor = QColorDialog::getColor(d->backgroundColor, this);
#endif

    QPixmap pix(d->ui.backgroundColorToolButton->size());
    pix.fill(d->backgroundColor);
    d->ui.backgroundColorToolButton->setIcon(pix);
}

void dtkInterpreterPreferencesWidget::onBackgroundOpacityChanged(int value)
{
    d->backgroundOpacity = value;
}

void dtkInterpreterPreferencesWidget::onOkButtonClicked(void)
{
    d->interpreter->setFont(d->font);
    d->interpreter->setBackgroundColor(d->backgroundColor);
    d->interpreter->setForegroundColor(d->foregroundColor);
    d->interpreter->setBackgroundOpacity(d->backgroundOpacity);

    this->hide();

    emit accepted();
}

void dtkInterpreterPreferencesWidget::onCancelButtonClicked(void)
{
    this->hide();

    emit rejected();
}
