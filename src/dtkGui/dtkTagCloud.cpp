/* dtkTagCloud.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun May  3 10:42:27 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Mar 14 20:55:18 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 649
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkTagCloud.h"

// /////////////////////////////////////////////////////////////////
// helper functions
// /////////////////////////////////////////////////////////////////

bool dtkTagAlphaLessThan(const dtkTag &t1, const dtkTag &t2) {
    return t1.text() < t2.text();
}

bool dtkTagNumLessThan(const dtkTag &t1, const dtkTag &t2) {
    return t1.count() < t2.count();
}

bool dtkTagAlphaMoreThan(const dtkTag &t1, const dtkTag &t2) {
    return t1.text() >= t2.text();
}

bool dtkTagNumMoreThan(const dtkTag &t1, const dtkTag &t2) {
    return t1.count() >= t2.count();
}

// /////////////////////////////////////////////////////////////////
// dtkTagCloudHasher
// /////////////////////////////////////////////////////////////////

class dtkTagCloudHasher
{
public:
    dtkTagCloudHasher(int buckets, int min, int max) {
        if (buckets < 1)
            qDebug() << "dtkTagCloudHasher: Must have at least one bucket.";

        this->buckets = buckets;
        this->min = min;
        this->max = max+1;

        this->width = ((double)(this->max-this->min))/((double)(this->buckets));
    }

    int bucket(dtkTag tag) {
        return ((float)(tag.count()-this->min))/((float)(this->width));
    }

private:
    int min, max, buckets;
    double width;
};

// /////////////////////////////////////////////////////////////////
// dtkTagPrivate
// /////////////////////////////////////////////////////////////////

class dtkTagPrivate
{
public:
    int count;
    QString text;
    QString color;
    QStringList items;
};

// /////////////////////////////////////////////////////////////////
// dtkTag
// /////////////////////////////////////////////////////////////////

dtkTag::dtkTag(void)
{
    d = new dtkTagPrivate;
}

dtkTag::dtkTag(QString text, int count)
{
    d = new dtkTagPrivate;
    d->text = text;
    d->count = count;
}

dtkTag::dtkTag(QString text, int count, QStringList items)
{
    d = new dtkTagPrivate;
    d->text = text;
    d->count = count;
    d->items = items;
}

dtkTag::dtkTag(QString text, int count, QStringList items, QString color)
{
    d = new dtkTagPrivate;
    d->text = text;
    d->count = count;
    d->items = items;
    d->color = color;
}

dtkTag::~dtkTag(void)
{
    // delete d;
}

int dtkTag::count(void) const
{
    return d->count;
}

QString dtkTag::text(void) const
{
    return d->text;
}

QStringList dtkTag::items(void) const
{
    return d->items;
}

QString dtkTag::color(void) const
{
    return d->color;
}

void dtkTag::setCount(int count)
{
    if (count > 0)
        d->count = count;
    else
        d->count = count;
}

void dtkTag::setText(QString text)
{
    if (!text.isNull())
        d->text = text;
    else
        d->text = "";
}

void dtkTag::setItems(QStringList items)
{
    if (!items.isEmpty())
        d->items = items;
    else
        d->items = QStringList();
}

void dtkTag::setColor(QString color)
{
    if (!color.isNull())
        d->color = color;
    else
        d->color = "";
}

// /////////////////////////////////////////////////////////////////
// dtkTagCloudPrivate
// /////////////////////////////////////////////////////////////////

class dtkTagCloudPrivate
{
public:
    QList<dtkTag> tags;

    int averageFontSize;
    int fontSizeRange;
    int mincount;
    int maxcount;
    int tagCount;

    QString stylesheet;

    dtkTagCloud::SortingType  sortingType;
    dtkTagCloud::SortingOrder sortingOrder;
};

// /////////////////////////////////////////////////////////////////
// dtkTagCloud
// /////////////////////////////////////////////////////////////////

dtkTagCloud::dtkTagCloud(QWidget *parent) : QWebView(parent)
{
    d = new dtkTagCloudPrivate;

    d->averageFontSize = 0;
    d->fontSizeRange   = 0;

    d->sortingType  = Alpha;
    d->sortingOrder = Asc;

    this->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    connect(this->page(), SIGNAL(linkClicked(const QUrl&)), this, SLOT(onLinkClicked(const QUrl&)));
}

dtkTagCloud::~dtkTagCloud(void)
{
    // delete d;
}

void dtkTagCloud::addTag(QString text, int count)
{
    d->tags << dtkTag(text, count);
}

void dtkTagCloud::addTag(QString text, int count, QStringList items)
{
    d->tags << dtkTag(text, count, items);
}

void dtkTagCloud::addTag(QString text, int count, QStringList items, QString color)
{
    d->tags << dtkTag(text, count, items, color);
}

void dtkTagCloud::addTag(dtkTag tag)
{
    d->tags << tag;
}

void dtkTagCloud::setFontSize(int size)
{
    d->averageFontSize = (size > 0) ? size : 0;
}

void dtkTagCloud::setFontRange(int range)
{
    d->fontSizeRange = (range > 0) ? range: 0;
}

void dtkTagCloud::setSortingType(SortingType type)
{
    d->sortingType = type;
}

void dtkTagCloud::setSortingOrder(SortingOrder order)
{
    d->sortingOrder = order;
}

void dtkTagCloud::setStyleSheet(QString stylesheet)
{
    d->stylesheet.clear();

    d->stylesheet += "<style type=\"text/css\">";
    d->stylesheet += stylesheet;
    d->stylesheet += "</style>";
}

void dtkTagCloud::sort(void)
{
    if(d->sortingType == Alpha && d->sortingOrder == Asc)
        qSort(d->tags.begin(), d->tags.end(), dtkTagAlphaLessThan);

    if(d->sortingType == Alpha && d->sortingOrder == Desc)
        qSort(d->tags.begin(), d->tags.end(), dtkTagAlphaMoreThan);

    if(d->sortingType == Num && d->sortingOrder == Asc)
        qSort(d->tags.begin(), d->tags.end(), dtkTagNumLessThan);

    if(d->sortingType == Num && d->sortingOrder == Desc)
        qSort(d->tags.begin(), d->tags.end(), dtkTagNumMoreThan);
}

void dtkTagCloud::clear(void)
{
    d->tags.clear();

    this->render();
}

void dtkTagCloud::render(void)
{
    if (d->averageFontSize <= 0)
        qDebug() << "AverageFontSize must be non-zero and non-negative.";

    if (d->fontSizeRange <= 0)
        qDebug() << "FontSizeRange must be non-zero and non-negative.";

    if (d->tags.isEmpty())
        return;

    d->mincount = 100000000;
    d->maxcount = 0;
    d->tagCount = 0;

    foreach (dtkTag tag, d->tags) {

        if (tag.count() < d->mincount)
            d->mincount = tag.count();

        if (tag.count() > d->maxcount)
            d->maxcount = tag.count();

        d->tagCount++;
    }

    dtkTagCloudHasher hasher(d->fontSizeRange, d->mincount, d->maxcount);

    int baseFontSize = d->averageFontSize - ((double)(d->fontSizeRange-1)/2);

    QString cloud; cloud.append(QString("<div align=\"justify\">\n"));

    foreach (dtkTag tag, d->tags) {

        int fontSize = baseFontSize + hasher.bucket(tag);

        QString color = "";

        if (!tag.color().isEmpty()) {
            color  = "color: ";
            color += (!tag.color().startsWith("#")) ? "#" : "";
            color += tag.color();
        }

        QString count = QString::number(tag.count()) + " item" + ((tag.count() != 1) ? "s" : "");

        cloud.append(QString("<a href=\"tag://%1\" title=\"%2\" style=\"font-size: %4px; %5\" item=\"%3\">%1</a> ")
                        .arg(tag.text())
                        .arg(count)
                        .arg(tag.items().first())
                        .arg(fontSize)
                        .arg(color));
    }
    cloud.append("</div>\n");

    this->setHtml(d->stylesheet + cloud);
}

void dtkTagCloud::onLinkClicked(const QUrl& url)
{
    emit tagClicked(url.host());
}

// /////////////////////////////////////////////////////////////////
// dtkTagScope
// /////////////////////////////////////////////////////////////////

class dtkTagScopePrivate
{
public:
    QStringList filters;

    QString stylesheet;
};

dtkTagScope::dtkTagScope(QWidget *parent) : QWebView(parent)
{
    d = new dtkTagScopePrivate;

    this->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setStyleSheet("");

    connect(this->page(), SIGNAL(linkClicked(const QUrl&)), this, SLOT(onLinkClicked(const QUrl&)));
}

dtkTagScope::~dtkTagScope(void)
{
    // delete d;
}

QSize dtkTagScope::sizeHint(void) const
{
    return QSize(100, 32);
}

static QString scope_stylesheet = 
"body       { margin: 0px; padding: 3px; background: rgb(%1, %2, %3); font-size: 90%; color: rgb(100, 100, 100); }"
"form       { padding-left: 5px; display: inline; height: 16px; } "
"input.text { border: 1px solid #cccccc; color: rgb(140, 140, 140); font-size: 80%; width: 100px; }"
"a          { text-decoration: none; color: rgb(140, 140, 140); float: right;}";

void dtkTagScope::setStyleSheet(QString user_stylesheet)
{
    d->stylesheet.clear();

    d->stylesheet += "<style type=\"text/css\">";
    d->stylesheet += scope_stylesheet;
    d->stylesheet +=  user_stylesheet;
    d->stylesheet += "</style>";
}

void dtkTagScope::clear(void)
{
    d->filters.clear();
}

void dtkTagScope::render(void)
{
    QString scope = "";
    scope += "<form name=\"scope\">";
    scope += "<strong>scope</strong> > ";
    foreach(QString filter, d->filters) {
    scope += "  " + filter + " > ";
    }
    scope += "<input type=\"text\" class=\"text\" name=\"tag\" value=\"Type a tag\" onFocus=\"document.scope.tag.value=''\"/>";
    scope += "<a href=\"action://clear\">clear</a>";
    scope += "</form>";

    this->setHtml(d->stylesheet + scope);
}

void dtkTagScope::addTag(QString tag)
{
    d->filters << tag;

    this->render();
}

void dtkTagScope::keyPressEvent(QKeyEvent *event)
{
    QString tag;

    switch(event->key()) {
    case Qt::Key_Return:
        tag = this->page()->currentFrame()->evaluateJavaScript("document.forms['scope'].elements['tag'].value;").toString();
        if(!tag.isEmpty())
            if(tag == "!") emit cleared();
            else           emit tagAdded(tag);
        break;
    default:
        QWebView::keyPressEvent(event);
        break;
    };
}

void dtkTagScope::onLinkClicked(const QUrl& url)
{
    if(url.scheme() == "action")
        if(url.host() == "clear")
            emit cleared();
}

// /////////////////////////////////////////////////////////////////
// dtkItem
// /////////////////////////////////////////////////////////////////

class dtkItemPrivate
{
public:
    QString name;
    QString description;
    QStringList tags;
    QStringList types;
};

dtkItem::dtkItem(QString name)
{
    d = new dtkItemPrivate;
    d->name = name;
    d->description = QString();
    d->tags = QStringList();
    d->types = QStringList();
}

dtkItem::dtkItem(QString name, QString description)
{
    d = new dtkItemPrivate;
    d->name = name;
    d->description = description;
    d->tags = QStringList();
    d->types = QStringList();
}

dtkItem::dtkItem(QString name, QString description, QStringList tags)
{
    d = new dtkItemPrivate;
    d->name = name;
    d->description = description;
    d->tags = tags;
    d->types = QStringList();
}

dtkItem::dtkItem(QString name, QString description, QStringList tags, QStringList types)
{
    d = new dtkItemPrivate;
    d->name = name;
    d->description = description;
    d->tags = tags;
    d->types = types;
}

dtkItem::~dtkItem(void)
{
    // delete d;
}

QString dtkItem::name(void) const
{
    return d->name;
}

QString dtkItem::description(void) const
{
    return d->description;
}

QStringList dtkItem::tags(void) const
{
    return d->tags;
}

QStringList dtkItem::types(void) const
{
    return d->types;
}

// /////////////////////////////////////////////////////////////////
// dtkItemView
// /////////////////////////////////////////////////////////////////

class dtkItemViewPrivate
{
public:
    QList<dtkItem> items;

    QString stylesheet;
};

dtkItemView::dtkItemView(QWidget *parent) : QWebView(parent)
{
    d = new dtkItemViewPrivate;
    
    this->setStyleSheet("");

    this->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    connect(this->page(), SIGNAL(linkClicked(const QUrl&)), this, SLOT(onLinkClicked(const QUrl&)));
}

dtkItemView::~dtkItemView(void)
{
    // delete d;
}

void dtkItemView::addItem(QString name)
{
    d->items << dtkItem(name, QString(), QStringList());
}

void dtkItemView::addItem(QString name, QString description)
{
    d->items << dtkItem(name, description, QStringList());
}

void dtkItemView::addItem(QString name, QString description, QStringList tags)
{
    d->items << dtkItem(name, description, tags);
}

void dtkItemView::addItem(QString name, QString description, QStringList tags, QStringList types)
{
    d->items << dtkItem(name, description, tags, types);
}

void dtkItemView::addItem(dtkItem item)
{
    d->items << item;
}

void dtkItemView::clear(void)
{
    d->items.clear();

    this->render();
}

void dtkItemView::render(void)
{
    QString list;

    list += "<ul>\n";
    foreach(dtkItem item, d->items) {
    list += "  <li>\n";
    list += "    <div class=\"name\">" + item.name() + "</div><br/>";
    list += "    Description: <div class=\"desc\">" + item.description() + "</div><br/>\n";
    list += "    Types: <div class=\"types\">\n";
    foreach(QString type, item.types()) {
        list += "        <a href=\"type:" + type + "\">" + type + "</a>";
    list += ((type == item.types().last()) ? QString("\n") : QString(" - \n"));
    }
    list += "    </div><br/>\n";
    list += "    <div class=\"tags\" align=\"right\">\n";
    foreach(QString tag, item.tags()) {
    list += "        <a href=\"tag:" + tag + "\"><b>" + tag + "</b></a>";
    list += ((tag == item.tags().last()) ? QString("\n") : QString(" > \n"));
    }
    list += "    </div>\n";
    list += "  </li>\n";
    list += "  <hr/>\n";
    }
    list += "</ul>\n";

    this->setHtml(d->stylesheet + list);
}

static QString view_stylesheet =
"ul            { margin: 0px; padding: 0px; }\n"
"li            { list-style: none; }\n"
".name         { font-size: 130%; color: rgb(18,  89, 199); }\n"
".desc         { display: inline; font-size: 100%; color: rgb(153, 153, 153); }\n"
".types        { display: inline; font-size: 100%; color: rgb( 18,  89, 199); }\n"
".types a      { color: rgb( 18,  89, 199); text-decoration: none; }\n"
".tags         { font-size: 100%; color: gray; }\n"
".tags a       { color: gray;  text-decoration: none; }\n"
".tags a:hover { color: rgb( 18,  89, 199); text-decoration: none; }\n"
"hr            { border: 0; width: 100%; color: rgb(200, 200, 200); background-color: rgb(200, 200, 200); height: 1px; }";

void dtkItemView::setStyleSheet(QString user_stylesheet)
{
    d->stylesheet.clear();

    d->stylesheet += "<style type=\"text/css\">\n";
    d->stylesheet += view_stylesheet;
    d->stylesheet += user_stylesheet;
    d->stylesheet += "</style>\n";
}

void dtkItemView::onLinkClicked(const QUrl& url)
{
    if (url.scheme() == "tag")
        emit tagClicked(url.path());

    if (url.scheme() == "item")
        emit itemClicked(url.path());

    if (url.scheme() == "type")
        emit typeClicked(url.path());
}

// /////////////////////////////////////////////////////////////////
// dtkTagController
// /////////////////////////////////////////////////////////////////

class dtkTagControllerPrivate
{
public:
    dtkItemView *view;
    dtkTagCloud *cloud;
    dtkTagScope *scope;

    QList<dtkTag>  tags;
    QList<dtkItem> items;
    QStringList    filters;
};

dtkTagController::dtkTagController(void) : QObject()
{
    d = new dtkTagControllerPrivate;
    d->view = NULL;
    d->cloud = NULL;
    d->scope = NULL;
}

dtkTagController::~dtkTagController(void)
{
    // delete d->view;
    // delete d->cloud;
    // delete d->scope;
    // delete d;
    // d = NULL;
}

void dtkTagController::attach(dtkItemView *view)
{
    d->view = view;

    connect(d->view,  SIGNAL(tagClicked(QString)), this, SLOT(setFilter(QString)));
}

void dtkTagController::attach(dtkTagCloud *cloud)
{
    d->cloud = cloud;

    connect(d->cloud, SIGNAL(tagClicked(QString)), this, SLOT(setFilter(QString)));
}

void dtkTagController::attach(dtkTagScope *scope)
{
    d->scope = scope;

    connect(d->scope, SIGNAL(tagSet(QString)),   this, SLOT(setFilter(QString)));
    connect(d->scope, SIGNAL(tagAdded(QString)), this, SLOT(addFilter(QString)));
    connect(d->scope, SIGNAL(cleared(void)), this, SLOT(clear()));
}

void dtkTagController::addItem(QString name)
{
    d->items << dtkItem(name, "", QStringList());

    this->update();
    this->render();
}

void dtkTagController::addItem(QString name, QString description)
{
    d->items << dtkItem(name, description, QStringList());

    this->update();
    this->render();
}

void dtkTagController::addItem(QString name, QString description, QStringList tags)
{
    d->items << dtkItem(name, description, tags);

    this->update();
    this->render();
}

void dtkTagController::addItem(QString name, QString description, QStringList tags, QStringList types)
{
    d->items << dtkItem(name, description, tags, types);

    this->update();
    this->render();
}

void dtkTagController::update(void)
{
    d->tags.clear();

    QHash<QString, QStringList> tags;
    
    foreach(dtkItem item, d->items)
        foreach(QString tag, item.tags())
            tags[tag] << item.name();

    foreach(QString tag, tags.keys())
        d->tags << dtkTag(tag, tags[tag].count(), tags[tag]);
}

static bool filter(QStringList l1, QStringList l2) {
    bool pass = true;
    foreach(QString s, l1) if(!l2.contains(s)) pass = false;
    return pass;
}

void dtkTagController::clear(void)
{
    d->filters.clear();
    
    this->render();
}

void dtkTagController::render(void)
{
    if (d->view) {
        d->view->clear();
        foreach(dtkItem item, d->items)
            if(filter(d->filters, item.tags()))
                d->view->addItem(item);
        d->view->render();
    }

    if (d->cloud) {
        d->cloud->clear();
        foreach(dtkTag tag, d->tags)
            d->cloud->addTag(tag);
        d->cloud->render();
    }

    if (d->scope) {
        d->scope->clear();
        foreach(QString filter, d->filters)
            d->scope->addTag(filter);
        d->scope->render();
    }
}

void dtkTagController::addFilter(QString filter)
{
    d->filters << filter;

    this->render();
}

void dtkTagController::setFilter(QString filter)
{
    d->filters.clear();
    d->filters << filter;

    this->render();
}
