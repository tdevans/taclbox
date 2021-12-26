#ifndef TEXTEDITORWIDGET_H
#define TEXTEDITORWIDGET_H

#include <QWidget>
#include <QFileInfo>
#include <QPlainTextEdit>

class TextEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextEditorWidget(const QFileInfo& file, QWidget *parent = nullptr);

    const QFileInfo& fileInfo() const;

private:
    const QFileInfo& mFile;
    QPlainTextEdit* mPlainTextEditor;

signals:

};

#endif // TEXTEDITORWIDGET_H
