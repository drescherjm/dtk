/* dtkSearchBoxUnix.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 16 22:38:07 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jul 22 21:19:10 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 28
 */

/* Commentary: 
 * See credits at end of file.
 */

/* Change log:
 * 
 */

#ifndef DTKSEARCHBOXUNIX_H
#define DTKSEARCHBOXUNIX_H

#include <QtGui>

#include <dtkGui/dtkGuiExport.h>

// /////////////////////////////////////////////////////////////////
// ProxyStyle
// /////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT ProxyStyle : public QStyle
{
    Q_OBJECT

public:
    explicit ProxyStyle(const QString &baseStyle) {
        style = QStyleFactory::create(baseStyle);
        if (!style)
            style = QStyleFactory::create(QLatin1String("windows"));
    }

    ~ProxyStyle(void) { 
	delete style; 
    }

    virtual void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget = 0) const
        { style->drawComplexControl(control, option, painter, widget); }
    virtual void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = 0) const
        { style->drawControl(element, option, painter, widget); }
    virtual void drawItemPixmap(QPainter *painter, const QRect &rectangle, int alignment, const QPixmap &pixmap) const
        { style->drawItemPixmap(painter, rectangle, alignment, pixmap); }
    virtual void drawItemText(QPainter *painter, const QRect &rectangle, int alignment, const QPalette &palette, bool enabled, const QString &text, QPalette::ColorRole textRole = QPalette::NoRole) const
        { style->drawItemText(painter, rectangle, alignment, palette, enabled, text, textRole); }
    virtual void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = 0) const
        { style->drawPrimitive(element, option, painter, widget); }
    virtual QPixmap generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap, const QStyleOption *option) const
        { return style->generatedIconPixmap(iconMode, pixmap, option); }
    virtual SubControl hitTestComplexControl(ComplexControl control, const QStyleOptionComplex *option, const QPoint &position, const QWidget *widget = 0) const
        { return style->hitTestComplexControl(control, option, position, widget); }
    virtual QRect itemPixmapRect(const QRect &rectangle, int alignment, const QPixmap &pixmap) const
        { return style->itemPixmapRect(rectangle, alignment, pixmap); }
    virtual QRect itemTextRect(const QFontMetrics &metrics, const QRect &rectangle, int alignment, bool enabled, const QString &text) const
        { return style->itemTextRect(metrics, rectangle, alignment, enabled, text); }
    virtual int pixelMetric(PixelMetric metric, const QStyleOption *option = 0, const QWidget *widget = 0) const
        { return style->pixelMetric(metric, option, widget); }
    virtual void polish(QWidget *widget)
        { style->polish(widget); }
    virtual void polish(QApplication *application)
        { style->polish(application); }
    virtual void polish(QPalette &palette)
        { style->polish(palette); }
    virtual QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &contentsSize, const QWidget *widget = 0) const
        { return style->sizeFromContents(type, option, contentsSize, widget); }
    virtual QPalette standardPalette () const
        { return style->standardPalette(); }
    virtual int styleHint(StyleHint hint, const QStyleOption *option = 0, const QWidget *widget = 0, QStyleHintReturn *returnData = 0) const
        { return style->styleHint(hint, option, widget, returnData); }
    virtual QRect subControlRect(ComplexControl control, const QStyleOptionComplex *option, SubControl subControl, const QWidget *widget = 0) const
        { return style->subControlRect(control, option, subControl, widget); }
    virtual void unpolish(QWidget *widget)
        { style->unpolish(widget); }
    virtual void unpolish(QApplication *application)
        { style->unpolish(application); }
    virtual QPixmap standardPixmap(StandardPixmap standardPixmap, const QStyleOption *opt = 0, const QWidget *widget = 0) const
        { return style->standardPixmap(standardPixmap, opt, widget); }
    virtual QRect subElementRect(SubElement element, const QStyleOption *option, const QWidget *widget = 0) const
        { return style->subElementRect(element, option, widget); }
    virtual bool event(QEvent *e)
        { return style->event(e); }
    virtual bool eventFilter(QObject *o, QEvent *e)
        { return style->eventFilter(o, e); }

protected slots:
    int layoutSpacingImplementation(QSizePolicy::ControlType control1, QSizePolicy::ControlType control2, Qt::Orientation orientation, const QStyleOption *option = 0, const QWidget *widget = 0) const
        { return style->layoutSpacing(control1, control2, orientation, option, widget); }

    QIcon standardIconImplementation(StandardPixmap standardIcon, const QStyleOption *option = 0, const QWidget *widget = 0) const
        { return style->standardIcon(standardIcon, option, widget); }

private:
    QStyle *style;

};

// /////////////////////////////////////////////////////////////////
// SideWidget
// /////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT SideWidget : public QWidget
{
    Q_OBJECT

signals:
    void sizeHintChanged();

public:
    SideWidget(QWidget *parent = 0);

protected:
    bool event(QEvent *event);

};

// /////////////////////////////////////////////////////////////////
// LineEdit
// /////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT LineEdit : public QLineEdit
{
    Q_OBJECT

public:
    enum WidgetPosition {
        LeftSide,
        RightSide
    };

    LineEdit(QWidget *parent = 0);
    LineEdit(const QString &contents, QWidget *parent = 0);

    void addWidget(QWidget *widget, WidgetPosition position);
    void removeWidget(QWidget *widget);
    void setWidgetSpacing(int spacing);
    int widgetSpacing() const;
    int textMargin(WidgetPosition position) const;
    QString inactiveText() const;
    void setInactiveText(const QString &text);

    void paintEvent(QPaintEvent *event);

protected:
    void resizeEvent(QResizeEvent *event);
    bool event(QEvent *event);

protected slots:
    void updateTextMargins();

private:
    void init();
    void updateSideWidgetLocations();

    SideWidget *m_leftWidget;
    SideWidget *m_rightWidget;
    QHBoxLayout *m_leftLayout;
    QHBoxLayout *m_rightLayout;
    QString m_inactiveText;
};

// /////////////////////////////////////////////////////////////////
// LineEditStyle
// /////////////////////////////////////////////////////////////////

#if QT_VERSION < 0x040500

class DTKGUI_EXPORT LineEditStyle : public ProxyStyle
{
public:
    explicit LineEditStyle() : ProxyStyle(QApplication::style()->objectName()) {
    }

    QRect subElementRect(SubElement element, const QStyleOption *option, const QWidget *widget = 0) const {
        QRect r = ProxyStyle::subElementRect(element, option, widget);
        if (element == SE_LineEditContents) {
            if (const LineEdit *le = qobject_cast<const LineEdit *>(widget)) {
                int left = le->textMargin(LineEdit::LeftSide);
                int right = le->textMargin(LineEdit::RightSide);
                r.adjust(left, 0, -right, 0);
            }
        }
        return r;
    }

};

#endif

// /////////////////////////////////////////////////////////////////
// SearchButton
// /////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT SearchButton : public QAbstractButton
{
public:
    SearchButton(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    QMenu *m_menu;

protected:
    void mousePressEvent(QMouseEvent *event);
};

// /////////////////////////////////////////////////////////////////
// ClearButton
// /////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT ClearButton : public QAbstractButton
{
    Q_OBJECT

public:
    ClearButton(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);

public slots:
    void textChanged(const QString &text);
};

// /////////////////////////////////////////////////////////////////
// SearchLineEdit
// /////////////////////////////////////////////////////////////////

class DTKGUI_EXPORT SearchLineEdit : public LineEdit
{
    Q_OBJECT
    Q_PROPERTY(QString inactiveText READ inactiveText WRITE setInactiveText)

public:
    SearchLineEdit(QWidget *parent = 0);

    QMenu *menu() const;

    void setMenu(QMenu *menu);

    QSize sizeHint(void) const;

signals:
    void textChanged(const QString& text, const QString& attribute);

public slots:
    void onTextChanged(const QString& text);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void updateGeometries();

    SearchButton *m_searchButton;
};

// /////////////////////////////////////////////////////////////////
// CREDITS
// /////////////////////////////////////////////////////////////////

/**
 * Copyright (c) 2008 - 2009, Benjamin C. Meyer  <ben@meyerhome.net>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Benjamin Meyer nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#endif
