/* dtkInspectorScene.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Sep  9 19:08:46 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep 10 17:43:02 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 173
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkInspectorScene.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractObject.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractView.h>

// /////////////////////////////////////////////////////////////////
// dtkInspectorSceneItem
// /////////////////////////////////////////////////////////////////

class dtkInspectorSceneItem : public QTreeWidgetItem
{
public:
    dtkInspectorSceneItem(QTreeWidget *parent);
    dtkInspectorSceneItem(QTreeWidgetItem *parent);

    void setObject(dtkAbstractObject *object);

    dtkAbstractObject *object(void);

private:
    dtkAbstractObject *m_object;
};

dtkInspectorSceneItem::dtkInspectorSceneItem(QTreeWidget *parent) : QTreeWidgetItem(parent)
{
    m_object = NULL;
}

dtkInspectorSceneItem::dtkInspectorSceneItem(QTreeWidgetItem *parent) : QTreeWidgetItem(parent)
{
    m_object = NULL;
}

void dtkInspectorSceneItem::setObject(dtkAbstractObject *object)
{
    m_object = object;
}

dtkAbstractObject *dtkInspectorSceneItem::object(void)
{
    return m_object;
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkInspectorScenePrivate
{
public:
    QTreeWidget *tree;
    QTreeWidgetItem *root;

    QIcon icon_root;
    QIcon icon_data;
    QIcon icon_process;
    QIcon icon_view;
};

dtkInspectorScene::dtkInspectorScene(QWidget *parent) : QWidget(parent), d(new dtkInspectorScenePrivate)
{
    { // Drawing root icon
        
    QPixmap pixmap(16, 16); pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::gray);
    painter.drawEllipse(pixmap.rect().adjusted(2, 2, -2, -2));
    d->icon_root.addPixmap(pixmap);
        
    }

    { // Drawing data icon
        
    QPixmap pixmap(16, 16); pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::blue);
    painter.drawEllipse(pixmap.rect().adjusted(2, 2, -2, -2));
    d->icon_data.addPixmap(pixmap);
        
    }

    { // Drawing process icon
        
    QPixmap pixmap(16, 16); pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::red);
    painter.drawEllipse(pixmap.rect().adjusted(2, 2, -2, -2));
    d->icon_process.addPixmap(pixmap);
        
    }

    { // Drawing view icon
        
    QPixmap pixmap(16, 16); pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::green);
    painter.drawEllipse(pixmap.rect().adjusted(2, 2, -2, -2));
    d->icon_view.addPixmap(pixmap);
        
    }

    d->tree = new QTreeWidget(this);
    d->tree->setFrameStyle(QFrame::NoFrame);
    d->tree->setAttribute(Qt::WA_MacShowFocusRect, false);
    d->tree->setHeaderLabels(QStringList() << "Name" << "Type" << "");
    d->tree->setColumnCount(3);
    d->tree->setColumnWidth(2, 18);
    d->tree->setRootIsDecorated(false);

    d->root = new QTreeWidgetItem(d->tree);
    d->root->setText(0, "root");
    d->root->setIcon(0, d->icon_root);

    // QTreeWidgetItem *testitem1 = new QTreeWidgetItem(d->root);
    // testitem1->setText(0, "data");
    // testitem1->setText(1, "qglViewPoint");
    // testitem1->setIcon(0, d->icon_data);
    // d->root->addChild(testitem1);

    // QTreeWidgetItem *testitem2 = new QTreeWidgetItem(testitem1);
    // testitem2->setText(0, "process");
    // testitem2->setIcon(0, d->icon_process);
    // testitem1->addChild(testitem2);

    // QTreeWidgetItem *testitem3 = new QTreeWidgetItem(d->root);
    // testitem3->setText(0, "view");
    // testitem3->setIcon(0, d->icon_view);
    // d->root->addChild(testitem3);

    d->tree->addTopLevelItem(d->root);
    d->tree->expandAll();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->tree);

    connect(d->tree, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(onItemClicked(QTreeWidgetItem *, int)));
}

dtkInspectorScene::~dtkInspectorScene(void)
{
    delete d->tree;
    delete d;

    d = NULL;
}

void dtkInspectorScene::addData(dtkAbstractData *data, QString type)
{
    dtkInspectorSceneItem *item = new dtkInspectorSceneItem(d->root);
    item->setText(0, data->objectName());
    item->setText(1, type);
    item->setIcon(0, d->icon_data);
    item->setObject(data);
    d->root->addChild(item);
}

void dtkInspectorScene::addProcess(dtkAbstractProcess *process, QString type)
{
    dtkInspectorSceneItem *item = new dtkInspectorSceneItem(d->root);
    item->setText(0, process->objectName());
    item->setText(1, type);
    item->setIcon(0, d->icon_process);
    item->setObject(process);
    d->root->addChild(item);
}

void dtkInspectorScene::addView(dtkAbstractView *view, QString type)
{
    dtkInspectorSceneItem *item = new dtkInspectorSceneItem(d->root);
    item->setText(0, view->objectName());
    item->setText(1, type);
    item->setIcon(0, d->icon_view);
    item->setObject(view);
    d->root->addChild(item);
}

void dtkInspectorScene::onItemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    dtkInspectorSceneItem *scene_item = dynamic_cast<dtkInspectorSceneItem *>(item);

    if(!scene_item)
        return;

    if(dtkAbstractData *data = dynamic_cast<dtkAbstractData *>(scene_item->object()))
        emit dataSelected(data);

    if(dtkAbstractProcess *process = dynamic_cast<dtkAbstractProcess *>(scene_item->object()))
        emit processSelected(process);

    if(dtkAbstractView *view = dynamic_cast<dtkAbstractView *>(scene_item->object()))
        emit viewSelected(view);
}

void dtkInspectorScene::onDataSelected(dtkAbstractData *data)
{
    d->tree->clearSelection();

    foreach(QTreeWidgetItem *item, d->tree->findItems(data->name(), Qt::MatchExactly))
        item->setSelected(true);
}

void dtkInspectorScene::onProcessSelected(dtkAbstractProcess *process)
{
    d->tree->clearSelection();

    foreach(QTreeWidgetItem *item, d->tree->findItems(process->name(), Qt::MatchExactly))
        item->setSelected(true);
}

void dtkInspectorScene::onViewSelected(dtkAbstractView *view)
{
    d->tree->clearSelection();
    
    foreach(QTreeWidgetItem *item, d->tree->findItems(view->objectName(), Qt::MatchFixedString | Qt::MatchRecursive, 0))
        item->setSelected(true);
}
