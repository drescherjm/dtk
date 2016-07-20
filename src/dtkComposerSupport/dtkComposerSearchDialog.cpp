/* dtkComposerSearchDialog.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Nov  5 16:41:00 2012 (+0100)
 * Version: $Id$
 * Last-Updated: ven. oct. 18 14:09:05 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 292
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNode.h"
#include "dtkComposerScene.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerSearchDialog.h"
#include "dtkComposerView.h"

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

class dtkComposerSearchDialogPrivate
{
public:
    void populate(dtkComposerSceneNode *node);
    void sortCombo(QComboBox *combo);

public:
    void update(void);

public:
    dtkComposerScene *scene;
    dtkComposerView *view;

public:
    QPushButton *find_button;
    QPushButton *next_button;
    QPushButton *more_button;

    QComboBox *node_combo;
    QComboBox *type_combo;

    QTextEdit *info;

public:
    QHash<QString, QSet<dtkComposerSceneNode *> > nodes;
    QHash<QString, QSet<dtkComposerSceneNode *> > types;

public:
    QList<dtkComposerSceneNode *> result;

public:
    int index;
};

void dtkComposerSearchDialogPrivate::populate(dtkComposerSceneNode *node)
{
    if (!node->title().isEmpty()) {
        this->node_combo->addItem(node->title());

        this->nodes[node->title()] << node;
        this->nodes["*"] << node;
    }

    if (node->wrapee()) {
        this->type_combo->addItem(node->wrapee()->type());

        this->types[node->wrapee()->type()] << node;
        this->types["*"] << node;
    }

    if (dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node))
        foreach (dtkComposerSceneNode *child, composite->nodes())
            this->populate(child);

    if (dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node))
        foreach (dtkComposerSceneNodeComposite *block, control->blocks())
            this->populate(block);
}

void dtkComposerSearchDialogPrivate::sortCombo(QComboBox *combo)
{
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(combo);
    proxy->setSourceModel(combo->model());
    combo->model()->setParent(proxy);
    combo->setModel(proxy);
    combo->model()->sort(0);
}


void dtkComposerSearchDialogPrivate::update(void)
{
    // dialog display

    QString contents = QString("Found %1 nodes satisfyng the following criteria:\n"
                               "- title: %2\n"
                               "- type: %3\n"
                               "\n"
                               "Currently highlighting node %4 over %1")
                       .arg(this->result.count())
                       .arg(this->node_combo->currentText())
                       .arg(this->type_combo->currentText())
                       .arg(this->index + 1);

    this->info->setText(contents);

    // scene display

    if (this->scene)
        this->scene->clearSelection();

    if (!this->result.count())
        return;

    dtkComposerSceneNode *node = this->result.at(this->index);

    if (!node)
        return;

    node->setSelected(true);

    // view display

    if (this->view)
        this->view->centerOn(node->pos());
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

dtkComposerSearchDialog::dtkComposerSearchDialog(dtkComposerView *parent) : QDialog(parent), d(new dtkComposerSearchDialogPrivate)
{
    d->scene = NULL;
    d->view = parent;

    d->node_combo = new QComboBox(this);
    d->node_combo->setEditable(true);

    d->type_combo = new QComboBox(this);
    d->type_combo->setEditable(true);

    d->info = new QTextEdit(this);
    d->info->setVisible(false);

    QDialogButtonBox *box = new QDialogButtonBox(this);

    d->find_button = box->addButton("Find", QDialogButtonBox::ActionRole);
    d->find_button->setDefault(true);

    d->next_button = box->addButton("Next", QDialogButtonBox::ActionRole);
    d->next_button->setDefault(false);
    d->next_button->setEnabled(false);

    d->more_button = box->addButton("More", QDialogButtonBox::ActionRole);
    d->more_button->setCheckable(true);

    QFormLayout *layout = new QFormLayout(this);
    layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    layout->addRow("Title", d->node_combo);
    layout->addRow("Type", d->type_combo);
    layout->addWidget(box);
    layout->addWidget(d->info);

    QAction *search_next_action = new QAction("Find next", this);
    search_next_action->setShortcut(QKeySequence::FindNext);

    this->addAction(search_next_action);

    this->setStyleSheet("background: none;");
    this->setWindowTitle("Search");

    connect(d->find_button, SIGNAL(clicked()), this, SLOT(find()));
    connect(d->next_button, SIGNAL(clicked()), this, SLOT(next()));
    connect(d->more_button, SIGNAL(clicked()), this, SLOT(more()));

    connect(d->node_combo, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(clear()));
    connect(d->node_combo, SIGNAL(editTextChanged(const QString&)), this, SLOT(clear()));

    connect(search_next_action, SIGNAL(triggered()), this, SLOT(next()));
}

dtkComposerSearchDialog::~dtkComposerSearchDialog(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSearchDialog::setScene(dtkComposerScene *scene)
{
    d->scene = scene;

    QString node = d->node_combo->currentText();
    QString type = d->type_combo->currentText();

    d->nodes.clear();
    d->types.clear();

    d->node_combo->clear(); d->node_combo->addItem("*");
    d->type_combo->clear(); d->type_combo->addItem("*");

    d->populate(scene->root());

    d->sortCombo(d->node_combo);
    d->sortCombo(d->type_combo);

    if (!node.isEmpty())
        d->node_combo->setEditText(node);

    if (!type.isEmpty())
        d->type_combo->setEditText(type);

    d->find_button->setDefault(true);
    d->next_button->setEnabled(false);
    d->next_button->setDefault(false);
}

void dtkComposerSearchDialog::find(void)
{
    d->result.clear();

    QString node = d->node_combo->currentText();
    QString type = d->type_combo->currentText();

    QSet<dtkComposerSceneNode *> result = d->nodes[node] & d->types[type];

    d->result = result.toList();

    d->index = 0;

    d->find_button->setDefault(false);
    d->find_button->setEnabled(false);
    d->next_button->setEnabled(true);
    d->next_button->setDefault(true);

    d->update();
}

void dtkComposerSearchDialog::next(void)
{
    if (!d->result.count())
        return;

    d->index = (d->index + 1) % d->result.count();

    d->update();
}

void dtkComposerSearchDialog::more(void)
{
    d->info->setVisible(!d->info->isVisible());
}

void dtkComposerSearchDialog::clear(void)
{
    d->find_button->setDefault(true);
    d->find_button->setEnabled(true);
    d->next_button->setEnabled(false);
    d->next_button->setDefault(false);
}
