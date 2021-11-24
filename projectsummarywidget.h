#ifndef PROJECTSUMMARYWIDGET_H
#define PROJECTSUMMARYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "semanticversion.h"

class ProjectSummaryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectSummaryWidget(QWidget *parent = nullptr);

    void setProjectName(QString projectName);
    void setProjectVersion(SemanticVersion projectVersion);

signals:

private:
    QLabel* mProjectNameLabel;
    QLabel* mProjectVersionLabel;
};

#endif // PROJECTSUMMARYWIDGET_H
