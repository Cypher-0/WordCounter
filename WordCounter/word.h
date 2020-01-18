#ifndef WORD_H
#define WORD_H

#include <QString>
#include <QStringList>
#include <QDebug>

class Word
{
private :
    QString value;
    int count = 0;

public:
    Word(QString iValue);

    QString getValue() const;//return word string
    int getCount() const;

    bool compare(QString input);//compare value to input and count++ if equals

};

struct countMoreThan //used to create predicate to sort list
{
    bool operator() (const Word &in0,const Word &in1) const //return true if in0.count > in1.count
    {
        return in0.getCount() > in1.getCount();
    }
};

struct alphabInferior //used to create predicate to sort list
{
    bool operator() (const Word &in0,const Word &in1) const //return true if in0.count > in1.count
    {
        QString in0Str = in0.getValue(),in1Str = in1.getValue();
        QStringList temp({in0Str,in1Str});
        temp.sort(Qt::CaseSensitivity::CaseInsensitive);
        return in0Str == temp[0];
    }
};

QDebug operator<<(QDebug debug, const Word &w);


#endif // WORD_H
