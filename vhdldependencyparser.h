#ifndef VHDLDEPENDENCYPARSER_H
#define VHDLDEPENDENCYPARSER_H

#include <QObject>
#include <QString>

class VhdlDependencyParser : public QObject
{
    Q_OBJECT
public:
    explicit VhdlDependencyParser(QObject *parent = nullptr);



signals:

};

#endif // VHDLDEPENDENCYPARSER_H
