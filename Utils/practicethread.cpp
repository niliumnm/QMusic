#include "practicethread.h"
#include <qmessagebox.h>
#include <QElapsedTimer>

PracticeThread::PracticeThread(QObject *parent)
    : QObject{parent}
{}

void PracticeThread::test()
{

}

void PracticeThread::handleStartPlaySheetPractice(const Sheet& sheet)
{
    if (sheet.notes.isEmpty()) {
        assert(false);
    }

    qint64  totalTime = 0; //应该播放的时间
    QElapsedTimer timeElapsed;
    timeElapsed.start();
    //for (const Node* curNote : sheet.notes) {
    for (auto it = sheet.notes.begin(); it != sheet.notes.end(); it++) {
        Node* curNote = *it;
        switch (curNote->duration)
        {
        case(1): {
            totalTime += static_cast<int>(Time1D1NoteMs);
            break;
        }
        case(2): {
            totalTime += static_cast<int>(Tim1D2NoteeMs);
            break;
        }
        case(4): {
            totalTime += static_cast<int>(Time1D4NoteMs);
            break;
        }
        case(8): {
            totalTime += static_cast<int>(Tim1D8NoteeMs);
            break;
        }
        case(16): {
            totalTime += static_cast<int>(Time1D16NoteMs);
            break;
        }
        case(32): {
            totalTime += static_cast<int>(Time1D32NoteMs);
            break;
        }
        case(64): {
            totalTime += static_cast<int>(Time1D64NoteMs);
            break;
        }
        default: {
            qDebug() << "Unkonw Note";
            Q_ASSERT(false);
        };
        }

        while (1) {
            if (timeElapsed.elapsed() >= totalTime) { // 
                //dispNote();
                emit drawNote(curNote->toSimpForm());
                if (std::next(it) != sheet.notes.end()) {
                    emit prevNote((*(std::next(it)))->toSimpForm());
                }
                break;
            }
        }
    }
    qDebug() << "Practice finished";
}
