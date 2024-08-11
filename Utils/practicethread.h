#ifndef PRACTICETHREAD_H
#define PRACTICETHREAD_H

#include <QObject>
#include <Utils/practicethread.h>
#include <define/NoteDef.h>

class PracticeThread : public QObject
{
    Q_OBJECT
public:
    explicit PracticeThread(QObject *parent = nullptr);
    void test();

public slots:
    void handleStartPlaySheetPractice(const Sheet& sheet);

signals:
    void prevNote(QString noteNumber);
    void drawNote(QString noteNumber);
};

#endif // PRACTICETHREAD_H
