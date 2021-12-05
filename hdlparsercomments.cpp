#include "hdlparsercomments.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

QString removeComments(QString text)
{
    QRegularExpression vhdlOneLineRegex("--.*?\\n");
    QRegularExpression vhdlMultiLineRegex("\\/\\*(?:.|\n)*\\*\\/");

    // Replace one line comments with just a newline to preserve line numbering
    text.replace(vhdlOneLineRegex, "\n");

    // For multi-line comments, replace with the same number of new-lines that were
    // in the comment to preserve line numbering.
    QRegularExpressionMatchIterator multiLineMatches = vhdlMultiLineRegex.globalMatch(text);
    while (multiLineMatches.hasNext())
    {
        QRegularExpressionMatch m = multiLineMatches.next();
        text.replace(m.capturedStart(), m.capturedLength(), QString("\n").repeated(m.captured().count('\n')));
    }

    return text;
}
