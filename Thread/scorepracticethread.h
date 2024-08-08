#ifndef SCOREPRACTICETHREAD_H
#define SCOREPRACTICETHREAD_H

#include <QObject>

class ScorePracticeThread : public QObject
{
    Q_OBJECT
public:
    explicit ScorePracticeThread(QObject *parent = nullptr);

public slots:
    void run();
    void init();

signals:
};

#endif // SCOREPRACTICETHREAD_H
