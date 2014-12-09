#include "documentnode.h"
#include <QDebug>
DocumentNode::DocumentNode(QObject *parent) :
    QObject(parent)
{
    _document = new QFile();
    _temporaryDocument = new QString;
    _saved = true;
}

DocumentNode::~DocumentNode()
{
    this->_document->close();
    delete this->_document;
    delete this->_temporaryDocument;
}

void DocumentNode::setFileName(const QString &fileName)
{
    this->_document->setFileName(fileName);
    this->_document->open(QIODevice::ReadWrite | QIODevice::Text);
}

void DocumentNode::write(const QString &content)
{
    this->_temporaryDocument->append(content);
}

void DocumentNode::saveFile()
{
    this->_document->write(this->_temporaryDocument->toUtf8());
}

QByteArray DocumentNode::readAll() const
{
    return this->_document->readAll();
}

void DocumentNode::setIndex(short index)
{
    this->_index = index;
}

short DocumentNode::index() const
{
    return this->_index;
}

bool DocumentNode::isSaved() const
{
    return this->_saved;
}

QFile* DocumentNode::document() const
{
    return this->_document;
}
QString *DocumentNode::temporaryDocument() const
{
    return this->_temporaryDocument;
}
