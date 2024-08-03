#ifndef NOTESHIFTER_H
#define NOTESHIFTER_H

#include <QString>
#include <QMap>
#include <QVector>

class NoteShifter
{
public:
    NoteShifter();
private:
    QMap<QString,QMap<QString,int>> m_noteMap;
};

#endif // NOTESHIFTER_H
