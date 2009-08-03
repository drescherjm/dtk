/* dtkSearchBoxUnix.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 16 22:12:58 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Aug  2 15:18:18 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 77
 */

/* Commentary: 
 * See CREDITS at end of file.
 */

/* Change log:
 * 
 */

#include <QtDebug>

#include <dtkGui/dtkSearchBoxUnix.h>

// /////////////////////////////////////////////////////////////////
// SideWidget
// /////////////////////////////////////////////////////////////////

SideWidget::SideWidget(QWidget *parent) : QWidget(parent)
{

}

bool SideWidget::event(QEvent *event)
{
    if (event->type() == QEvent::LayoutRequest)
        emit sizeHintChanged();

    return QWidget::event(event);
}

// /////////////////////////////////////////////////////////////////
// LineEdit
// /////////////////////////////////////////////////////////////////

LineEdit::LineEdit(QWidget *parent)
    : QLineEdit(parent)
    , m_leftLayout(0)
    , m_rightLayout(0)
{
#if QT_VERSION < 0x040500
    setStyle(new LineEditStyle);
#endif
    init();
}

LineEdit::LineEdit(const QString &contents, QWidget *parent)
    : QLineEdit(contents, parent)
    , m_leftWidget(0)
    , m_rightWidget(0)
    , m_leftLayout(0)
    , m_rightLayout(0)
{
    init();
}

void LineEdit::init()
{
    m_leftWidget = new SideWidget(this);
    m_leftWidget->resize(0, 0);
    m_leftLayout = new QHBoxLayout(m_leftWidget);
    m_leftLayout->setContentsMargins(0, 0, 0, 0);
    if (isRightToLeft())
        m_leftLayout->setDirection(QBoxLayout::RightToLeft);
    else
        m_leftLayout->setDirection(QBoxLayout::LeftToRight);
    m_leftLayout->setSizeConstraint(QLayout::SetFixedSize);

    m_rightWidget = new SideWidget(this);
    m_rightWidget->resize(0, 0);
    m_rightLayout = new QHBoxLayout(m_rightWidget);
    if (isRightToLeft())
        m_rightLayout->setDirection(QBoxLayout::RightToLeft);
    else
        m_rightLayout->setDirection(QBoxLayout::LeftToRight);
    m_rightLayout->setContentsMargins(0, 0, 0, 0);

    QSpacerItem *horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_rightLayout->addItem(horizontalSpacer);

    setWidgetSpacing(3);

    connect(m_leftWidget, SIGNAL(sizeHintChanged()),
            this, SLOT(updateTextMargins()));
    connect(m_rightWidget, SIGNAL(sizeHintChanged()),
            this, SLOT(updateTextMargins()));
}

bool LineEdit::event(QEvent *event)
{
    if (event->type() == QEvent::LayoutDirectionChange) {
        if (isRightToLeft()) {
            m_leftLayout->setDirection(QBoxLayout::RightToLeft);
            m_rightLayout->setDirection(QBoxLayout::RightToLeft);
        } else {
            m_leftLayout->setDirection(QBoxLayout::LeftToRight);
            m_rightLayout->setDirection(QBoxLayout::LeftToRight);
        }
    }
    return QLineEdit::event(event);
}

void LineEdit::addWidget(QWidget *widget, WidgetPosition position)
{
    if (!widget)
        return;

    bool rtl = isRightToLeft();
    if (rtl)
        position = (position == LeftSide) ? RightSide : LeftSide;
    widget->show();
    if (position == LeftSide) {
        m_leftLayout->addWidget(widget);
    } else {
        m_rightLayout->insertWidget(1, widget);
    }
}

void LineEdit::removeWidget(QWidget *widget)
{
    if (!widget)
        return;

    m_leftLayout->removeWidget(widget);
    m_rightLayout->removeWidget(widget);
    widget->hide();
}

void LineEdit::setWidgetSpacing(int spacing)
{
    m_leftLayout->setSpacing(spacing);
    m_rightLayout->setSpacing(spacing);
    updateTextMargins();
}

int LineEdit::widgetSpacing() const
{
    return m_leftLayout->spacing();
}

int LineEdit::textMargin(WidgetPosition position) const
{
    int spacing = m_rightLayout->spacing();
    int w = 0;
    if (position == LeftSide)
        w = m_leftWidget->sizeHint().width();
    else
        w = m_rightWidget->sizeHint().width();
    if (w == 0)
        return 0;
    return w + spacing * 2;
}

void LineEdit::updateTextMargins()
{
#if QT_VERSION >= 0x040500
    int left = textMargin(LineEdit::LeftSide);
    int right = textMargin(LineEdit::RightSide);
    int top = 0;
    int bottom = 0;
    setTextMargins(left, top, right, bottom);
#else
    update();
#endif
    updateSideWidgetLocations();
}

void LineEdit::updateSideWidgetLocations()
{
    QStyleOptionFrameV2 opt;
    initStyleOption(&opt);
    QRect textRect = style()->subElementRect(QStyle::SE_LineEditContents, &opt, this);
    int spacing = m_rightLayout->spacing();
    textRect.adjust(spacing, 0, -spacing, 0);

    int left = textMargin(LineEdit::LeftSide);
#if QT_VERSION < 0x040500
    int right = textMargin(LineEdit::RightSide);
    textRect.adjust(-left, 1, right, 0);
#endif

    int midHeight = textRect.center().y();

    if (m_leftLayout->count() > 0) {
        int leftHeight = midHeight - m_leftWidget->height() / 2;
        int leftWidth = m_leftWidget->width();
        if (leftWidth == 0)
            leftHeight = midHeight - m_leftWidget->sizeHint().height() / 2;
        m_leftWidget->move(textRect.x(), leftHeight);
    }
    textRect.setX(left);
    textRect.setY(midHeight - m_rightWidget->sizeHint().height() / 2);
    textRect.setHeight(m_rightWidget->sizeHint().height());
    m_rightWidget->setGeometry(textRect);
}

void LineEdit::resizeEvent(QResizeEvent *event)
{
    updateSideWidgetLocations();
    QLineEdit::resizeEvent(event);
}

QString LineEdit::inactiveText() const
{
    return m_inactiveText;
}

void LineEdit::setInactiveText(const QString &text)
{
    m_inactiveText = text;
}

void LineEdit::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);
    if (text().isEmpty() && !m_inactiveText.isEmpty() && !hasFocus()) {
        QStyleOptionFrameV2 panel;
        initStyleOption(&panel);
        QRect textRect = style()->subElementRect(QStyle::SE_LineEditContents, &panel, this);
        int horizontalMargin = 2;
        textRect.adjust(horizontalMargin, 0, 0, 0);
#if QT_VERSION >= 0x040500
        int left = textMargin(LineEdit::LeftSide);
        int right = textMargin(LineEdit::RightSide);
        textRect.adjust(left, 0, -right, 0);
#endif
        QPainter painter(this);
        painter.setPen(palette().brush(QPalette::Disabled, QPalette::Text).color());
        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, m_inactiveText);
    }
}

// /////////////////////////////////////////////////////////////////
// SearchButton
// /////////////////////////////////////////////////////////////////

SearchButton::SearchButton(QWidget *parent)
    : QAbstractButton(parent)
    , m_menu(0)
{
    setObjectName(QLatin1String("SearchButton"));
    setCursor(Qt::ArrowCursor);
    setFocusPolicy(Qt::NoFocus);
}

void SearchButton::mousePressEvent(QMouseEvent *event)
{
    if (m_menu && event->button() == Qt::LeftButton) {
        QWidget *p = parentWidget();
        if (p) {
            QPoint r = p->mapToGlobal(QPoint(0, p->height()));
            m_menu->exec(QPoint(r.x() + height() / 2, r.y()));
        }
        event->accept();
    }
    QAbstractButton::mousePressEvent(event);
}

void SearchButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainterPath myPath;

    int radius = (height() / 5) * 2;
    QRect circle(height() / 3 - 1, height() / 4, radius, radius);
    myPath.addEllipse(circle);

    myPath.arcMoveTo(circle, 300);
    QPointF c = myPath.currentPosition();
    int diff = height() / 7;
    myPath.lineTo(qMin(width() - 2, (int)c.x() + diff), c.y() + diff);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::darkGray, 2));
    painter.drawPath(myPath);

    if (m_menu) {
        QPainterPath dropPath;
        dropPath.arcMoveTo(circle, 320);
        QPointF c = dropPath.currentPosition();
        c = QPointF(c.x() + 3.5, c.y() + 0.5);
        dropPath.moveTo(c);
        dropPath.lineTo(c.x() + 4, c.y());
        dropPath.lineTo(c.x() + 2, c.y() + 2);
        dropPath.closeSubpath();
        painter.setPen(Qt::darkGray);
        painter.setBrush(Qt::darkGray);
        painter.setRenderHint(QPainter::Antialiasing, false);
        painter.drawPath(dropPath);
    }
    painter.end();
}

// /////////////////////////////////////////////////////////////////
// ClearButton
// /////////////////////////////////////////////////////////////////

ClearButton::ClearButton(QWidget *parent)
    : QAbstractButton(parent)
{
    setCursor(Qt::ArrowCursor);
    setToolTip(tr("Clear"));
    setVisible(false);
    setFocusPolicy(Qt::NoFocus);
    setMinimumSize(22, 22);
}

void ClearButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    int height = this->height();

    painter.setRenderHint(QPainter::Antialiasing, true);
    QColor color = palette().color(QPalette::Mid);
    painter.setBrush(isDown()
                     ? palette().color(QPalette::Dark)
                     : palette().color(QPalette::Mid));
    painter.setPen(painter.brush().color());
    int size = width();
    int offset = size / 5;
    int radius = size - offset * 2;
    painter.drawEllipse(offset, offset, radius, radius);

    painter.setPen(palette().color(QPalette::Base));
    int border = offset * 2;
    painter.drawLine(border, border, width() - border, height - border);
    painter.drawLine(border, height - border, width() - border, border);
}

void ClearButton::textChanged(const QString &text)
{
    setVisible(!text.isEmpty());
}

// /////////////////////////////////////////////////////////////////
// SearchLineEdit
// /////////////////////////////////////////////////////////////////

SearchLineEdit::SearchLineEdit(QWidget *parent)
    : LineEdit(parent)
    , m_searchButton(0)
{
    setUpdatesEnabled(false);
    m_searchButton = new SearchButton(this);
    updateGeometries();
    addWidget(m_searchButton, LeftSide);
    setInactiveText(tr("Search"));

    QSizePolicy policy = sizePolicy();
    setSizePolicy(QSizePolicy::Preferred, policy.verticalPolicy());

    // clear button on the right
    ClearButton *m_clearButton = new ClearButton(this);
    connect(m_clearButton, SIGNAL(clicked()),
            this, SLOT(clear()));
    connect(this, SIGNAL(textChanged(const QString&)),
            m_clearButton, SLOT(textChanged(const QString&)));
    connect(this, SIGNAL(textChanged(const QString&)),
            this, SLOT(onTextChanged(const QString&)));

    addWidget(m_clearButton, RightSide);
    m_clearButton->hide();
    updateTextMargins();
    setUpdatesEnabled(true);
}

void SearchLineEdit::resizeEvent(QResizeEvent *event)
{
    updateGeometries();
    LineEdit::resizeEvent(event);
}

void SearchLineEdit::updateGeometries()
{
    int menuHeight = height();
    int menuWidth = menuHeight + 1;
    if (!m_searchButton->m_menu)
        menuWidth = (menuHeight / 5) * 4;
    m_searchButton->setMinimumSize(QSize(menuWidth, menuHeight));
    m_searchButton->resize(menuWidth, menuHeight);
    updateTextMargins();
}

void SearchLineEdit::setMenu(QMenu *menu)
{
    if (m_searchButton->m_menu)
        m_searchButton->m_menu->deleteLater();
    m_searchButton->m_menu = menu;
    updateGeometries();
}

QMenu *SearchLineEdit::menu() const
{
    if(!m_searchButton->m_menu) {
        m_searchButton->m_menu = new QMenu(m_searchButton);
        if (isVisible())
            (const_cast<SearchLineEdit*>(this))->updateGeometries();
    }
    return m_searchButton->m_menu;
}

void SearchLineEdit::onTextChanged(const QString& text)
{
    QString attribute;

    foreach(QAction *action, menu()->actions())
	if(action->isChecked())
	    attribute = action->text();

    emit(textChanged(text, attribute));
}

QSize SearchLineEdit::sizeHint(void) const
{
    return QSize(200, 26);
}

// /////////////////////////////////////////////////////////////////
// dtkSearchBox
// /////////////////////////////////////////////////////////////////

#include <dtkGui/dtkSearchBox.h>

class dtkSearchBoxPrivate
{
public:
    SearchLineEdit *search;
};

dtkSearchBox::dtkSearchBox(QWidget *parent) : QWidget(parent), d(new dtkSearchBoxPrivate)
{
    d->search = new SearchLineEdit(this);

    connect(d->search, SIGNAL(textChanged(const QString&, const QString&)), this, SIGNAL(textChanged(const QString&, const QString&)));
    connect(d->search, SIGNAL(textChanged(const QString&)),                 this, SIGNAL(textChanged(const QString&)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->search);
}

dtkSearchBox::~dtkSearchBox(void)
{
    delete d->search;
    delete d;

    d = NULL;
}

void dtkSearchBox::setMenu(QMenu *menu)
{
    d->search->setMenu(menu);
}

void dtkSearchBox::setFocus(void)
{
    d->search->setFocus();
}

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
