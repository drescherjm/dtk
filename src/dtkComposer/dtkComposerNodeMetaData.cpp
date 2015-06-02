// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkComposerNodeMetaData.h"

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMetaDataPrivate
{
public:
    QString color;
    QString title;
    dtkComposerNode::Kind kind;
    QString type;
    QStringList tags;
    QString description;
    QStringList input_labels;
    QStringList output_labels;
};

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

dtkComposerNodeMetaData::dtkComposerNodeMetaData(void) : d(new dtkComposerNodeMetaDataPrivate)
{
    d->color = "darkGray";
    d->kind = dtkComposerNode::Unknown;
}

dtkComposerNodeMetaData::~dtkComposerNodeMetaData(void)
{

}

bool dtkComposerNodeMetaData::setFromFile(const QString& file_path)
{
    QFile file(file_path);

    if(!file.open(QFile::ReadOnly)) {
        qDebug() << Q_FUNC_INFO << "Unable to read file" << file_path;
        return false;
    }

    QJsonDocument json_doc = QJsonDocument::fromJson(file.readAll());
    if (json_doc.isEmpty()) {
        qDebug() << Q_FUNC_INFO << "Json document" << file_path << "is empty. Unable to create json object.";
        return false;
    }

    QJsonObject json = json_doc.object();

    qDebug() << json.keys();

    d->title = json.value(QString("title")).toString();
    this->setKind(json.value(QString("kind")).toString());
    d->type = json.value(QString("type")).toString();

    QVariantList tag_list = json.value(QString("tags")).toArray().toVariantList();
    for(const QVariant& v : tag_list)
        d->tags << v.toString();

    d->description = json.value(QString("description")).toString();

    QVariantList input_list = json.value(QString("inputs")).toArray().toVariantList();
    for(const QVariant& v : input_list)
        d->input_labels << v.toString();

    QVariantList output_list = json.value(QString("outputs")).toArray().toVariantList();
    for(const QVariant& v : output_list)
        d->output_labels << v.toString();

    if(json.keys().contains("color"))
        this->setColor(json.value("color").toString());

    file.close();

    return true;
}

void dtkComposerNodeMetaData::setColor(const QString& color)
{
    d->color = color;
}

void dtkComposerNodeMetaData::setTitle(const QString& title)
{
    d->title = title;
}

void dtkComposerNodeMetaData::setKind(const QString& kind)
{
    QString kind_lower = kind.toLower();

    if (kind_lower == QString("atomic")) {
        d->kind = dtkComposerNode::Atomic;

    } else if(kind_lower == QString("composite")) {
        d->kind = dtkComposerNode::Composite;

    } else if(kind_lower == QString("control")) {
        d->kind = dtkComposerNode::Control;

    } else if(kind_lower == QString("proxy")) {
        d->kind = dtkComposerNode::Proxy;

    } else if(kind_lower == QString("data")) {
        d->kind = dtkComposerNode::Data;

    } else if(kind_lower == QString("process")) {
        d->kind = dtkComposerNode::Process;

    } else if(kind_lower == QString("view")) {
        d->kind = dtkComposerNode::View;

    } else if(kind_lower == QString("actor")) {
        d->kind = dtkComposerNode::Actor;

    } else {
        d->kind = dtkComposerNode::Unknown;
    }
}

void dtkComposerNodeMetaData::setType(const QString& type)
{
    d->type = type;
}

void dtkComposerNodeMetaData::setTags(const QStringList& tags)
{
    d->tags = tags;
}

void dtkComposerNodeMetaData::setDescription(const QString& description)
{
    d->description = description;
}

void dtkComposerNodeMetaData::appendInputLabel(const QString& label)
{
    d->input_labels << label;
}

void dtkComposerNodeMetaData::appendOutputLabel(const QString& label)
{
    d->output_labels << label;
}

void dtkComposerNodeMetaData::setInputLabel(int i, const QString& label)
{
    d->input_labels.replace(i, label);
}

void dtkComposerNodeMetaData::setOutputLabel(int i, const QString& label)
{
    d->output_labels.replace(i, label);
}

const QString& dtkComposerNodeMetaData::title(void) const
{
    return d->title;
}

const QString& dtkComposerNodeMetaData::color(void) const
{
    return d->color;
}

dtkComposerNode::Kind dtkComposerNodeMetaData::kind(void) const
{
    return d->kind;
}

const QString& dtkComposerNodeMetaData::type(void) const
{
    return d->type;
}

const QStringList& dtkComposerNodeMetaData::tags(void) const
{
    return d->tags;
}

const QString& dtkComposerNodeMetaData::description(void) const
{
    return d->description;
}

const QStringList& dtkComposerNodeMetaData::inputLabels(void) const
{
    return d->input_labels;
}

const QStringList& dtkComposerNodeMetaData::outputLabels(void) const
{
    return d->output_labels;
}

//
// dtkComposerNodeMetaData.cpp ends here
