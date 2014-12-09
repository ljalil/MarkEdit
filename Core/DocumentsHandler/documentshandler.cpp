#include "documentshandler.h"
#include <QDebug>
DocumentsHandler::DocumentsHandler(QObject *parent) :
    QObject(parent)
{
    _DocumentsList = new QVector<DocumentNode*>;
}

DocumentsHandler::~DocumentsHandler()
{
    delete this->_DocumentsList;
}

DocumentNode* DocumentsHandler::at(int index)
{
    return this->_DocumentsList->at(index);
}

bool DocumentsHandler::contains(QString filePath)
{
    QVectorIterator<DocumentNode*> iterator(*this->_DocumentsList);
    while(iterator.hasNext()) {
        if(iterator.next()->document()->fileName() == filePath)
            return true;
    }
    return false;
}

QByteArray DocumentsHandler::readFile(int index)
{
    return this->_DocumentsList->at(index)->readAll();
}

void DocumentsHandler::addFile(const QString &fileName)
{
    DocumentNode* newNode = new DocumentNode;
    newNode->setFileName(fileName);
    this->_DocumentsList->append(newNode);
}

void DocumentsHandler::removeFile(int index)
{
    this->_DocumentsList->removeAt(index);
}

void DocumentsHandler::stageFile(int index, const QString &content)
{
    this->_DocumentsList->at(index)->write(content);
}

void DocumentsHandler::commitFile(int index)
{
    this->_DocumentsList->at(index)->saveFile();
}



