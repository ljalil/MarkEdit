#ifndef DOCUMENTNODE_H
#define DOCUMENTNODE_H

#include <QObject>
#include <QFile>
#include <QString>
#include <QVector>

class DocumentNode : public QObject
{
    Q_OBJECT
public:
    explicit DocumentNode(QObject *parent = 0);
    ~DocumentNode();

    void setFileName(const QString &fileName);
    void write(const QString &content);
    void saveFile();
    QByteArray readAll() const;
    void setIndex(short index);
    short index() const;
    bool isSaved() const;
    QFile* document() const;
    QString* temporaryDocument() const;

private:
    short _index;
    bool _saved;
    QFile* _document;
    QString* _temporaryDocument;
signals:

public slots:

};

#endif // DOCUMENTNODE_H
