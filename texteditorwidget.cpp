#include "texteditorwidget.h"
#include <QHBoxLayout>
#include <QFile>

TextEditorWidget::TextEditorWidget(const QFileInfo &file, QWidget *parent)
    : QWidget(parent), mFile(file)
{
    QHBoxLayout* l = new QHBoxLayout();
    if (l)
    {
        setLayout(new QHBoxLayout);

        mPlainTextEditor = new QPlainTextEdit;
        if (mPlainTextEditor)
        {
            layout()->addWidget(mPlainTextEditor);

            if (!mFile.exists())
            {
                mPlainTextEditor->setReadOnly(true);
                mPlainTextEditor->document()->setPlainText(QString("Could not find file %1").arg(mFile.path()));
            }
            else if (!mFile.isFile())
            {
                mPlainTextEditor->setReadOnly(true);
                mPlainTextEditor->document()->setPlainText(QString("The specified path was not a file: %1").arg(mFile.path()));
            }
            else if (!mFile.isReadable())
            {
                mPlainTextEditor->setReadOnly(true);
                mPlainTextEditor->document()->setPlainText(QString("The specified file was not readable: %1").arg(mFile.path()));
            }
            else
            {
                QFile f(file.filePath());
                bool openedSuccessfully = f.open(QIODevice::ReadOnly);
                if (!openedSuccessfully)
                {
                    mPlainTextEditor->setReadOnly(true);
                    mPlainTextEditor->document()->setPlainText(QString("Unable to open the specified file: %1").arg(mFile.path()));
                }
                else
                {
                    mPlainTextEditor->document()->setPlainText(f.readAll());
                    f.close();
                }
            }
        }
    }
}

const QFileInfo &TextEditorWidget::fileInfo() const
{
    return mFile;
}
