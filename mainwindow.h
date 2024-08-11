#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qnamespace.h"
#include <QMainWindow>
#include <QMidiIn.h>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QElapsedTimer>
#include <QProgressBar>
#include <qlabel.h>
#include <define/NoteDef.h>
#include <QDebug>
#include <QThread>
#include <qvector.h>
#include <QGraphicsScene>
#include <Utils/practicethread.h>
#include <QGraphicsPixmapItem>
#include <QTimer>

// 增加曲线图 TODO https://zhuangzuoyi.github.io/using-Qt-Charts/02/

struct RecordRank {
    int m_tryCount;
    QElapsedTimer m_time;
};

struct PracticeStatus
{
    bool isStart = false;
    int totalCount;
    int curCount;
    QString curNote;
    int perfectCount = 0;
    bool perfact = true;
    PracticeStatus() {}
};

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

struct DeviceStatus {
    QString curDevId;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_resreshBtn_clicked();
    void on_deviceComb_currentIndexChanged(int index);
    void on_connBtn_clicked();
    void on_startBtn_clicked();
    void on_btnHint_clicked();
    void on_btnOpenFile_clicked();
    void on_btnStartPlay_clicked(); // 开始练习乐谱被点击
    void on_tuneComb_currentIndexChanged(int index);

public slots:
    void handleMidiEvent(quint32 message, quint32 timing);
    void onDrawNote(QString noteNumber);
    void onDrawTune(QString tuneStr);
    void onPrevNote(Node* note);
    void onStartPractice(int num);
    void handleContinuePractice();
    void handleStartTimer(double sec);
    void handlePlayNote(QString noteStr);

private:
    void initSlot();
    void initUI();

private:
    Ui::MainWindow* ui;

private:
    std::unique_ptr<QTimer> timer;
    std::unique_ptr<QProgressBar> progBar;
    std::unique_ptr<QGraphicsScene> scene;
    std::unique_ptr<QGraphicsPixmapItem> notePicItem;
    std::unique_ptr<QGraphicsPixmapItem> tunePicItem;
    std::unique_ptr<PracticeThread> m_pThread;
    std::unique_ptr<QThread> pracThread;
    std::unique_ptr<QLabel> progLab;
    QMidiIn m_midiIn;
    PracticeStatus pracStatus;
    QMap<QString, QString> m_devices;
    DeviceStatus devStatus;
    RecordRank record;
    Sheet sheet;
    QMap<QString, QVector<int>>shift;
    QVector<int>noteShift = { 0,0,-1,0,0,0,-1 };

protected:
    void closeEvent(QCloseEvent* event) override;

signals:
    void drawNote(QString noteNumber);
    void startPractice(int count);
    void continuePractice();
    void startTimer(double sec);
    void playNoteSound(QString note);
    void startPlaySheetPractice(const Sheet& sheet);
    void prevNote(Node* note);
    void drawTune(QString tuneStr);
};
#endif // MAINWINDOW_H
