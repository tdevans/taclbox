#ifndef INVALIDPROJECTFILEEXCEPTION_H
#define INVALIDPROJECTFILEEXCEPTION_H

#include <QException>

class InvalidProjectFileException : public QException
{
public:
    InvalidProjectFileException(QString msg = "") throw() : mMsg(msg) {}
    QString message() const throw() { return mMsg; }
    void raise() const override { throw *this; }
    InvalidProjectFileException* clone() const override { return new InvalidProjectFileException(*this); }
private:
    QString mMsg;
};

#endif // INVALIDPROJECTFILEEXCEPTION_H
