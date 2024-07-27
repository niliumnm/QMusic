#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMidiIn.h>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QElapsedTimer>
#include <QProgressBar>
#include <qlabel.h>
#include <define/NoteDef.h>
// 增加曲线图 TODO https://zhuangzuoyi.github.io/using-Qt-Charts/02/

struct RecordRank{
    int m_tryCount;
    QElapsedTimer m_time;
};

struct PracticeStatus
{
    bool isStart=false;
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

struct DeviceStatus{
    QString curDevId;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_resreshBtn_clicked();
    void on_deviceComb_currentIndexChanged(int index);
    void on_connBtn_clicked();
    void on_startBtn_clicked();
    void on_btnHint_clicked();

public slots:
    void handleMidiEvent(quint32 message, quint32 timing);
    void onDrawNote(QString noteNumber);
    void onStartPractice(int num);
    void handleContinuePractice();
    void handleStartTimer(double sec);
    void handlePlayNote(QString noteStr);

private:
    void initSlot();
    void initUI();

private:
    Ui::MainWindow *ui;

private:
    QMidiIn m_midiIn;
    PracticeStatus pracStatus;
    QMap<QString , QString> m_devices;
    DeviceStatus devStatus;
    RecordRank record;
    QTimer * timer = nullptr;
    QProgressBar* progBar = nullptr;
    QLabel* progLab = nullptr;    

protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void drawNote(QString noteNumber);
    void startPractice(int count);
    void continuePractice();
    void startTimer(double sec);
    void playNoteSound(QString note);
};
#endif // MAINWINDOW_H
