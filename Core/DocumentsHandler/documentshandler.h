#ifndef DOCUMENTSHANDLER_H
#define DOCUMENTSHANDLER_H

#include <QObject>
#include <QVector>
#include <QByteArray>
#include "../DocumentNode/documentnode.h"

class DocumentsHandler : public QObject
{
    Q_OBJECT
public:
    explicit DocumentsHandler(QObject *parent = 0);
    ~DocumentsHandler();
    DocumentNode* at(int index);
    bool contains(QString filePath);

private:
    QVector<DocumentNode*> *_DocumentsList;

signals:
public:
    QByteArray readFile(int index);
public slots:
    void addFile(const QString &fileName);
    void stageFile(int index, const QString &content);
    void commitFile(int index);
    void removeFile(int index);
};

#endif // DOCUMENTSHANDLER_H
