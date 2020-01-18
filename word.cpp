#include "word.h"

Word::Word(QString iValue)
{
    value = iValue.toLower();
    count++;
}

QString Word::getValue() const//return word string
{
    return value;
}

int Word::getCount() const
{
    return count;
}

bool Word::compare(QString input)//compare value to input and count++ if equals
{
    if(input.toLower() == value)
    {
        count++;
        return true;
    }

    return false;
}


//--------------------------------------------------------------------------------

QDebug operator<<(QDebug debug, const Word &w)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "Mot : " << w.getValue() << " | Compté : " << w.getCount();

    return debug;
}
