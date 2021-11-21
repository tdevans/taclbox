#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QObject>

class ProjectManager : public QObject
{
    Q_OBJECT
public:
    explicit ProjectManager(QObject *parent = nullptr);

signals:

};

#endif // PROJECTMANAGER_H
