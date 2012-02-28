/* dtkSplitter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Oct  7 23:24:59 2008 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Feb 28 18:23:44 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 89
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui>

#include <dtkGui/dtkSplitter.h>

// /////////////////////////////////////////////////////////////////
// dtkSplitterHandle
// /////////////////////////////////////////////////////////////////

class dtkSplitterHandle : public QSplitterHandle
{
public:
    dtkSplitterHandle(Qt::Orientation orientation, bool slim, bool hud, QSplitter *parent);
    
    void paintEvent(QPaintEvent * event);
    QSize sizeHint(void) const;

private:
    bool m_slim;
    bool m_hud;
};

dtkSplitterHandle::dtkSplitterHandle(Qt::Orientation orientation, bool slim, bool hud, QSplitter *parent) : QSplitterHandle(orientation, parent) 
{
    this->m_slim = slim;
    this->m_hud = hud;
}

void dtkSplitterHandle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    
    QColor topColor(145, 145, 145);
    QColor bottomColor(142, 142, 142);
    QColor gradientStart(252, 252, 252);
    QColor gradientStop(223, 223, 223);
    
    if(!m_hud) {
        topColor = QColor(145, 145, 145);
        bottomColor = QColor(142, 142, 142);
        gradientStart = QColor(252, 252, 252);
        gradientStop = QColor(223, 223, 223);
    } else {
        topColor = QColor(60, 60, 60);
        bottomColor = QColor(40, 40, 40);
        gradientStart = QColor(48, 48, 48);
        gradientStop = QColor(28, 28, 28);
    }

    if (orientation() == Qt::Vertical) {
	painter.setPen(topColor);
	painter.drawLine(0, 0, width(), 0);

	if(m_slim)
	    return;
	
	painter.setPen(bottomColor);
	painter.drawLine(0, height()-1, width(), height()-1);
	
	QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()-3));
	linearGrad.setColorAt(0, gradientStart);
	linearGrad.setColorAt(1, gradientStop);
	painter.fillRect(QRect(QPoint(0,1), size() - QSize(0, 2)), QBrush(linearGrad));

        if(!m_hud)
            return;

        painter.setPen(topColor);
        painter.setBrush(topColor);
        painter.drawEllipse(QRect(event->rect().width()/2-1, this->sizeHint().height()/2 - 2, 4, 4));

    } else {
	painter.setPen(QColor("#181818"));
	painter.drawLine(0, 0, 0, height());
    }
}

QSize dtkSplitterHandle::sizeHint(void) const
{
    QSize parent = QSplitterHandle::sizeHint();

    if (orientation() == Qt::Vertical) {
	return m_slim ? QSize(parent.width(), 1) : parent + QSize(0, 3);
    } else {
	return QSize(1, parent.height());
    }
}

// /////////////////////////////////////////////////////////////////
// dtkSplitterPrivate
// /////////////////////////////////////////////////////////////////

class dtkSplitterPrivate
{
public:
    bool slim;
    bool hud;
};

// /////////////////////////////////////////////////////////////////
// dtkSplitter
// /////////////////////////////////////////////////////////////////

dtkSplitter::dtkSplitter(QWidget *parent, bool slim, bool hud) : QSplitter(parent), d(new dtkSplitterPrivate)
{
    d->slim = slim;
    d->hud = hud;
}

dtkSplitter::~dtkSplitter(void)
{
    delete d;

    d = NULL;
}

QSplitterHandle *dtkSplitter::createHandle(void)
{
    return new dtkSplitterHandle(orientation(), d->slim, d->hud, this);
}
