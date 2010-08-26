/* dtkFinder.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Jun 12 15:47:45 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 15 20:24:09 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 52
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkFinder.h"

#include <dtkCore/dtkGlobal.h>

#ifdef Q_WS_WIN
#include <qt_windows.h>
#endif

// /////////////////////////////////////////////////////////////////
// dtkFinderSideView
// /////////////////////////////////////////////////////////////////

class dtkFinderSideViewPrivate
{
public:
    QList<QTreeWidgetItem *> items;
};

dtkFinderSideView::dtkFinderSideView(QWidget *parent) : QTreeWidget(parent), d(new dtkFinderSideViewPrivate)
{
    this->header()->hide();
    this->setAcceptDrops(true);
    this->setDropIndicatorShown(true);
    this->setDragDropMode(QAbstractItemView::DropOnly);
    this->setIndentation(10);
    this->setFrameStyle(QFrame::NoFrame);
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setStyleSheet(dtkReadFile(":dtkGui/dtkFinder.qss"));
    this->setFocusPolicy(Qt::NoFocus);
    this->populate();

    connect(this, SIGNAL(itemClicked(QTreeWidgetItem *,int)), this, SLOT(onItemCicked(QTreeWidgetItem *, int)));
}

dtkFinderSideView::~dtkFinderSideView(void)
{
    delete d;

    d = NULL;
}

void dtkFinderSideView::populate(void)
{
    this->clear(); d->items.clear();

    QFont groupFont;
    groupFont.setPointSize(11);
    groupFont.setBold(true);
    groupFont.setCapitalization(QFont::AllUppercase);

    QBrush groupBrush;
    groupBrush.setColor(QColor("#758192"));

    QFont itemFont;
    itemFont.setPointSize(10);

    QFileIconProvider provider;

    QTreeWidgetItem *item1  = new QTreeWidgetItem(this, QStringList() << "Drives");
    item1->setFlags(Qt::ItemIsEnabled);
    item1->setData(0, Qt::FontRole, groupFont);
    item1->setData(0, Qt::ForegroundRole, groupBrush);

	QFileInfoList driveList;
#ifdef Q_WS_MAC
	QDir macDir("/Volumes");
	driveList = macDir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot);
#else
	driveList = QDir::drives();
#endif
	
    foreach(QFileInfo info, driveList) {

		QString dlabel = this->driveLabel( info.absoluteFilePath() );
        QTreeWidgetItem *item = new QTreeWidgetItem(item1, QStringList() << (dlabel.isEmpty() ? "HD" : dlabel));
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        item->setData(0, Qt::FontRole, itemFont);
        item->setData(0, Qt::UserRole, info.absoluteFilePath());
        item->setIcon(0, provider.icon(QFileIconProvider::Drive));

        d->items << item;
    }

    QTreeWidgetItem *item2  = new QTreeWidgetItem(this, QStringList() << "Places");
    item2->setFlags(Qt::ItemIsEnabled);
    item2->setData(0, Qt::FontRole, groupFont);
    item2->setData(0, Qt::ForegroundRole, groupBrush);

    QTreeWidgetItem *item21 = new QTreeWidgetItem(item2, QStringList() << "Desktop");
    item21->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item21->setData(0, Qt::FontRole, itemFont);
    item21->setData(0, Qt::UserRole, QDir::homePath() + "/Desktop");
    item21->setIcon(0, provider.icon(QFileInfo(QDir::homePath() + "/Desktop")));

    QTreeWidgetItem *item22 = new QTreeWidgetItem(item2, QStringList() << "Home");
    item22->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item22->setData(0, Qt::FontRole, itemFont);
    item22->setData(0, Qt::UserRole, QDir::homePath());
    item22->setIcon(0, provider.icon(QFileInfo(QDir::homePath())));

    QTreeWidgetItem *item23 = new QTreeWidgetItem(item2, QStringList() << "Downloads");
    item23->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item23->setData(0, Qt::FontRole, itemFont);
    item23->setData(0, Qt::UserRole, QDir::homePath() + "/Downloads");
    item23->setIcon(0, provider.icon(QFileInfo(QDir::homePath() + "/Downloads")));

    QTreeWidgetItem *item3  = new QTreeWidgetItem(this, QStringList() << "Bookmarks");
    item3->setFlags(Qt::ItemIsEnabled);
    item3->setData(0, Qt::FontRole, groupFont);
    item3->setData(0, Qt::ForegroundRole, groupBrush);

    QTreeWidgetItem *item31 = new QTreeWidgetItem(item3, QStringList() << "Home");
    item31->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item31->setData(0, Qt::FontRole, itemFont);
    item31->setData(0, Qt::UserRole, QDir::homePath());
    item31->setIcon(0, provider.icon(QFileInfo(QDir::homePath())));

    QSettings settings; QStringList bookmarks = settings.value("dtkFinderBookmarks").toStringList();

    foreach(QString path, bookmarks) {

        QFileInfo info(path);

        QTreeWidgetItem *item = new QTreeWidgetItem(item3, QStringList() << info.baseName());
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        item->setData(0, Qt::FontRole, itemFont);
        item->setData(0, Qt::UserRole, info.absoluteFilePath());
        item->setIcon(0, provider.icon(info));

        d->items << item;
    }

    this->expandItem(item1);
    this->expandItem(item2);
    this->expandItem(item3);

    d->items << item21 << item22 << item23;
}

void dtkFinderSideView::setPath(const QString& path)
{
    foreach(QTreeWidgetItem *item, d->items)
        if (item->data(0, Qt::UserRole).toString() == path)
            item->setSelected(true);
        else
            item->setSelected(false);
}

void dtkFinderSideView::addBookmark(const QString& path)
{
    QFileInfo info(path);

    if(!info.isDir())
        return;

    QSettings settings;
    QStringList bookmarks = settings.value("dtkFinderBookmarks").toStringList();
    bookmarks.removeAll(path);
    bookmarks.append(path);
    settings.setValue("dtkFinderBookmarks", bookmarks);

    this->populate();
}

void dtkFinderSideView::clearBookmarks(void)
{
    QSettings settings;
    settings.remove("dtkFinderBookmarks");

    this->populate();
}

void dtkFinderSideView::onItemCicked(QTreeWidgetItem *item, int)
{
    emit changed(item->data(0, Qt::UserRole).toString());
}

void dtkFinderSideView::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()) {

        QFileInfo info(event->mimeData()->urls().first().toLocalFile());

        if(!info.isDir()) {
            event->ignore();
            return;
        } else {
            event->accept();
            return;
        }
    }

    event->ignore();
}

void dtkFinderSideView::dragMoveEvent(QDragMoveEvent *event)
{
    if(event->mimeData()->hasUrls()) {

        QFileInfo info(event->mimeData()->urls().first().toLocalFile());

        if(!info.isDir()) {
            event->ignore();
            return;
        } else {
            event->accept();
            return;
        }
    }

    event->ignore();
}

void dtkFinderSideView::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasUrls()) {
        QFileInfo info(event->mimeData()->urls().first().toLocalFile());
        this->addBookmark(info.absoluteFilePath());
        event->accept();
        return;
    }

    event->ignore();
}

QString dtkFinderSideView::driveLabel(QString drive)
{
#ifdef Q_WS_WIN
	drive.replace("/", "\\");
	TCHAR  szVolumeName[256];
	TCHAR  szFileSystemName[256];
	DWORD dwSerialNumber = 0;
	DWORD dwMaxFileNameLength=256;
	DWORD dwFileSystemFlags=0;
	bool ret = GetVolumeInformation( drive.toAscii().constData(), 
									 szVolumeName, 256, 
									 &dwSerialNumber, &dwMaxFileNameLength,
									 &dwFileSystemFlags, szFileSystemName, 256);
	if(!ret) { 
		drive.remove("\\");
		QString decoratedDrive = "("+drive+")";
		return decoratedDrive;
	}
	
	QString vName = QString::fromAscii(szVolumeName) ;
	vName.trimmed();
	drive.remove("\\");
	vName += " ("+drive+")";
	return vName;
#endif

#ifdef Q_WS_MAC
	return drive.baseName();
#endif

	return drive;
}

// /////////////////////////////////////////////////////////////////
// dtkFinderPathBarItem
// /////////////////////////////////////////////////////////////////

class dtkFinderPathBarItem
{
public:
    QString text;
    QIcon icon;
    QRect rect;
    QDir dir;
};

// /////////////////////////////////////////////////////////////////
// dtkFinderPathBar
// /////////////////////////////////////////////////////////////////

class dtkFinderPathBarPrivate
{
public:
    QString path;

    QList<dtkFinderPathBarItem *> items;
};

dtkFinderPathBar::dtkFinderPathBar(QWidget *parent) : QFrame(parent), d(new dtkFinderPathBarPrivate)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(23);
    this->setStyleSheet("font: 11px; border-top: 1px solid #d4d4d4;");
}

dtkFinderPathBar::~dtkFinderPathBar(void)
{
    foreach(dtkFinderPathBarItem *item, d->items)
        delete item;

    delete d;

    d = NULL;
}

void dtkFinderPathBar::setPath(const QString &path)
{
    d->path = path;
    d->items.clear();

    QFileIconProvider provider;

    QDir dir(d->path); do {

        dtkFinderPathBarItem *item = new dtkFinderPathBarItem;
        item->text = dir.dirName().isEmpty() ? "/" : dir.dirName();
        if (!dir.entryInfoList(QStringList() << ".").isEmpty())
            item->icon = provider.icon(dir.entryInfoList(QStringList() << ".").first());
        item->dir = dir;
        d->items.prepend(item);

    } while(dir.cdUp());

    this->update();
}

void dtkFinderPathBar::mousePressEvent(QMouseEvent *event)
{
    foreach(dtkFinderPathBarItem *item, d->items) {
        if(item->rect.contains(event->x(), event->y())) {
            this->setPath(item->dir.absolutePath());
            emit changed(item->dir.absolutePath());
        }
    }
}

void dtkFinderPathBar::paintEvent(QPaintEvent *event)
{
    int x = 10;
    int y = 3;

    QPainter painter(this);

    foreach(dtkFinderPathBarItem *item, d->items) {
        painter.drawPixmap(x, y, item->icon.pixmap(16, 16));
        painter.drawText(x + 16 + 4, y + 14, item->text);

        int delta = 16 + 4 + painter.fontMetrics().width(item->text) + 10;

        item->rect = QRect(x, 0, delta, 23);

        x += delta;
    }

    if(d->items.last()->rect.right() >= this->width()) {
        QRect rect(this->width()-30, 0, 30, 23);
        painter.fillRect(rect, this->palette().background());
        painter.drawText(rect.left(), y+14, "...");
    }
}

// /////////////////////////////////////////////////////////////////
// dtkFinderListView
// /////////////////////////////////////////////////////////////////

class dtkFinderListViewPrivate
{
public:
    QMenu *menu;
};

dtkFinderListView::dtkFinderListView(QWidget *parent) : QListView(parent), d(new dtkFinderListViewPrivate)
{
    this->setViewMode(QListView::IconMode);
    this->setWordWrap(true);
    this->setWrapping(true);
    this->setIconSize(QSize(64, 64));
    this->setResizeMode(QListView::Adjust);
    this->setGridSize(QSize(128, 96));
    this->setFrameStyle(QFrame::NoFrame);
    this->setAttribute(Qt::WA_MacShowFocusRect, false);

    this->setContextMenuPolicy(Qt::CustomContextMenu);

    d->menu = new QMenu(this);
    d->menu->addAction("Bookmark", this, SLOT(onBookmarkContextMenuClicked()));

    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(updateContextMenu(const QPoint&)));
}

dtkFinderListView::~dtkFinderListView(void)
{
    delete d;

    d = NULL;
}

void dtkFinderListView::addContextMenuAction(QAction *action)
{
    d->menu->addAction(action);
}

QString dtkFinderListView::selectedPath(void) const
{
    if(!selectedIndexes().count())
        return QString();

    if(QFileSystemModel *model = qobject_cast<QFileSystemModel *>(this->model()))
        return model->filePath(selectedIndexes().first());

    return QString();
}

void dtkFinderListView::updateContextMenu(const QPoint& point)
{
    QModelIndex index = this->indexAt(point);

    if(!index.isValid())
        return;

    d->menu->exec(mapToGlobal(point));
}

void dtkFinderListView::onBookmarkContextMenuClicked(void)
{
    if(!selectedIndexes().count())
        return;

    if(QFileSystemModel *model = qobject_cast<QFileSystemModel *>(this->model()))
            emit bookmarked(model->filePath(selectedIndexes().first()));
}

void dtkFinderListView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up && (event->modifiers() & Qt::ControlModifier)) {
        if(QFileSystemModel *model = qobject_cast<QFileSystemModel *>(this->model())) {
            QDir dir = QDir(model->filePath(this->rootIndex()));
            dir.cdUp();
            this->setRootIndex(model->index(dir.absolutePath()));
            emit changed(dir.absolutePath());
            event->accept();
            return;
        }
    }

    if(event->key() == Qt::Key_Down && (event->modifiers() & Qt::ControlModifier)) {
        if(QFileSystemModel *model = qobject_cast<QFileSystemModel *>(this->model())) {

            if(!this->selectionModel()->selectedIndexes().count())
                return;

            QFileInfo selection = model->fileInfo(this->selectionModel()->selectedIndexes().first());

            if(selection.isDir()) {
                this->setRootIndex(model->index(selection.filePath()));
                emit changed(selection.absoluteFilePath());
                event->accept();
            }

            return;
        }
    }

    QListView::keyPressEvent(event);
}

void dtkFinderListView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(QFileSystemModel *model = qobject_cast<QFileSystemModel *>(this->model())) {

        QModelIndex index = indexAt(event->pos());
        
        if(!index.isValid())
            return;

        QFileInfo info = model->fileInfo(index);

        if(info.isDir())
            QListView::mouseDoubleClickEvent(event);
    }
}

void dtkFinderListView::startDrag(Qt::DropActions supportedActions)
{
    QModelIndexList indexes = selectedIndexes();

    if (indexes.count() > 0) {

        QMimeData *data = model()->mimeData(indexes);
        if (!data)
            return;

        QFileIconProvider provider;

        QPixmap pixmap = provider.icon(QFileInfo(data->urls().first().toLocalFile())).pixmap(64, 64);
        QDrag *drag = new QDrag(this);
        drag->setPixmap(pixmap);
        drag->setMimeData(data);
        drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
        drag->exec(supportedActions, Qt::IgnoreAction);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkFinderTreeView
// /////////////////////////////////////////////////////////////////

class dtkFinderTreeViewPrivate
{
public:
    QMenu *menu;
};

dtkFinderTreeView::dtkFinderTreeView(QWidget *parent) : QTreeView(parent), d(new dtkFinderTreeViewPrivate)
{
    this->setDragEnabled(true);
    this->setFrameStyle(QFrame::NoFrame);
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setSortingEnabled(true);
    this->sortByColumn(0, Qt::AscendingOrder);

    d->menu = new QMenu(this);
    d->menu->addAction("Bookmark", this, SLOT(onBookmarkContextMenuClicked()));

    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(updateContextMenu(const QPoint&)));
}

dtkFinderTreeView::~dtkFinderTreeView(void)
{
    delete d;

    d = NULL;
}

int dtkFinderTreeView::sizeHintForColumn(int column) const
{
    if(column == 1)
        return 400;

    return 100;
}

void dtkFinderTreeView::addContextMenuAction(QAction *action)
{
    d->menu->addAction(action);
}

QString dtkFinderTreeView::selectedPath(void) const
{
    if(!selectedIndexes().count())
        return QString();

    if(QFileSystemModel *model = qobject_cast<QFileSystemModel *>(this->model()))
        return model->filePath(selectedIndexes().first());

    return QString();
}

void dtkFinderTreeView::updateContextMenu(const QPoint& point)
{
    QModelIndex index = this->indexAt(point);

    if(!index.isValid())
        return;

    d->menu->exec(mapToGlobal(point));
}

void dtkFinderTreeView::onBookmarkContextMenuClicked(void)
{
    if(!selectedIndexes().count())
        return;

    if(QFileSystemModel *model = qobject_cast<QFileSystemModel *>(this->model()))
            emit bookmarked(model->filePath(selectedIndexes().first()));
}

void dtkFinderTreeView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up && (event->modifiers() & Qt::ControlModifier)) {
        if(QFileSystemModel *model = qobject_cast<QFileSystemModel *>(this->model())) {
            QDir dir = QDir(model->filePath(this->rootIndex()));
            dir.cdUp();
            this->setRootIndex(model->index(dir.absolutePath()));
            emit changed(dir.absolutePath());
            event->accept();
            return;
        }
    }

    if(event->key() == Qt::Key_Down && (event->modifiers() & Qt::ControlModifier)) {
        if(QFileSystemModel *model = qobject_cast<QFileSystemModel *>(this->model())) {

            if(!this->selectionModel()->selectedIndexes().count())
                return;

            QFileInfo selection = model->fileInfo(this->selectionModel()->selectedIndexes().first());

            if(selection.isDir()) {
                this->setRootIndex(model->index(selection.filePath()));
                emit changed(selection.absoluteFilePath());
                event->accept();
            }

            return;
        }
    }

    QTreeView::keyPressEvent(event);
}

void dtkFinderTreeView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(QFileSystemModel *model = qobject_cast<QFileSystemModel *>(this->model())) {

        QModelIndex index = indexAt(event->pos());
     
        if(!index.isValid())
            return;
   
        QFileInfo info = model->fileInfo(index);

        if(info.isDir())
            QTreeView::mouseDoubleClickEvent(event);
    }
}

void dtkFinderTreeView::startDrag(Qt::DropActions supportedActions)
{
    QModelIndexList indexes = selectedIndexes();

    if (indexes.count() > 0) {

        QMimeData *data = model()->mimeData(indexes);
        if (!data)
            return;

        QFileIconProvider provider;

        QPixmap pixmap = provider.icon(QFileInfo(data->urls().first().toLocalFile())).pixmap(64, 64);
        QDrag *drag = new QDrag(this);
        drag->setPixmap(pixmap);
        drag->setMimeData(data);
        drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
        drag->exec(supportedActions, Qt::IgnoreAction);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkFinder
// /////////////////////////////////////////////////////////////////

class dtkFinderPrivate
{
public:
    QFileSystemModel *model;

    dtkFinderListView *list;
    dtkFinderTreeView *tree;

    QStackedWidget *stack;
};

dtkFinder::dtkFinder(QWidget *parent) : QWidget(parent), d(new dtkFinderPrivate)
{
    d->model = new QFileSystemModel(this);
    d->model->setFilter(QDir::Hidden | QDir::AllEntries | QDir::NoDotAndDotDot);
    d->model->setRootPath(QDir::rootPath());

    d->list = new dtkFinderListView(this);
    d->list->setModel(d->model);
    d->list->setRootIndex(d->model->index(QDir::currentPath()));

    d->tree = new dtkFinderTreeView(this);
    d->tree->setModel(d->model);
    d->tree->setRootIndex(d->model->index(QDir::currentPath()));

    d->stack = new QStackedWidget(this);
    d->stack->addWidget(d->list);
    d->stack->addWidget(d->tree);
    d->stack->setCurrentIndex(0);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->stack);

    connect(d->list, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onIndexDoubleClicked(QModelIndex)));
    connect(d->tree, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onIndexDoubleClicked(QModelIndex)));

    connect(d->list, SIGNAL(changed(QString)), this, SLOT(setPath(QString)));
    connect(d->tree, SIGNAL(changed(QString)), this, SLOT(setPath(QString)));

    connect(d->list, SIGNAL(changed(QString)), this, SIGNAL(changed(QString)));
    connect(d->tree, SIGNAL(changed(QString)), this, SIGNAL(changed(QString)));

    connect(d->list, SIGNAL(bookmarked(QString)), this, SIGNAL(bookmarked(QString)));
    connect(d->tree, SIGNAL(bookmarked(QString)), this, SIGNAL(bookmarked(QString)));

    QAction *switchToListViewAction = new QAction(this);
    QAction *switchToTreeViewAction = new QAction(this);

    switchToListViewAction->setShortcut(Qt::ControlModifier + Qt::Key_1);
    switchToTreeViewAction->setShortcut(Qt::ControlModifier + Qt::Key_2);

    this->addAction(switchToListViewAction);
    this->addAction(switchToTreeViewAction);

    connect(switchToListViewAction, SIGNAL(triggered()), this, SLOT(switchToListView()));
    connect(switchToTreeViewAction, SIGNAL(triggered()), this, SLOT(switchToTreeView()));
}

dtkFinder::~dtkFinder(void)
{
    delete d;

    d = NULL;
}

void dtkFinder::addContextMenuAction(QAction *action)
{
    d->list->addContextMenuAction(action);
    d->tree->addContextMenuAction(action);
}

QString dtkFinder::selectedPath(void) const
{
    if(d->stack->currentIndex() == 0)
        return d->list->selectedPath();

    if(d->stack->currentIndex() == 1)
        return d->tree->selectedPath();

    return QString();
}

void dtkFinder::setPath(const QString& path)
{
    if(sender() != d->list)
        d->list->setRootIndex(d->model->index(path));

    if(sender() != d->tree)
        d->tree->setRootIndex(d->model->index(path));
}

void dtkFinder::switchToListView(void)
{
    d->stack->setCurrentIndex(0);
}

void dtkFinder::switchToTreeView(void)
{
    d->stack->setCurrentIndex(1);
}

void dtkFinder::onIndexDoubleClicked(QModelIndex index)
{
    QModelIndex idx = d->model->index(d->model->filePath(index));

    d->list->setRootIndex(idx);
    d->tree->setRootIndex(idx);

    QFileInfo selection = d->model->fileInfo(index);

    if(selection.isDir())
        emit changed(selection.absoluteFilePath());
}
