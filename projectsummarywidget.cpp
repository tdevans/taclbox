#include "projectsummarywidget.h"
#include <QSpacerItem>

ProjectSummaryWidget::ProjectSummaryWidget(QWidget *parent) : QWidget(parent)
{
    setLayout(new QVBoxLayout);

    mProjectNameLabel = new QLabel("Project: ");
    mProjectVersionLabel = new QLabel("Version: ");

    layout()->addWidget(mProjectNameLabel);
    layout()->addWidget(mProjectVersionLabel);
    layout()->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void ProjectSummaryWidget::setProjectName(QString projectName)
{
    mProjectNameLabel->setText(QString("Project: %1").arg(projectName));
}

void ProjectSummaryWidget::setProjectVersion(SemanticVersion projectVersion)
{
    mProjectVersionLabel->setText(QString("Version: %1.%2.%3").arg(projectVersion.major()).arg(projectVersion.minor()).arg(projectVersion.patch()));
}
