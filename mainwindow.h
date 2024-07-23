#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMidiIn.h>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QElapsedTimer>
// 增加曲线图 TODO https://zhuangzuoyi.github.io/using-Qt-Charts/02/

static QStringList noteName = {
    "-4","-5","-6","-7",
    "1","2","3","4","5","6","7",
    "+1","+2","+3","+4","+5","+6","+7",
    "++1","++2","++3"
};


static QMap<int,QString>NoteMap = {
    {36,"--1"},{38,"--2"},{40,"--3"},{41,"--4"},{43,"--5"},{45,"--6"},{47,"--7"},
    {48,"-1"},{50,"-2"},{52,"-3"},{53,"-4"},{55,"-5"},{57,"-6"},{59,"-7"},
    {60,"1"},{62,"2"},{64,"3"},{65,"4"},{67,"5"},{69,"6"},{71,"7"},
    {72,"+1"},{74,"+2"},{76,"+3"},{77,"+4"},{79,"+5"},{81,"+6"},{83,"+7"},
    {84,"++1"},{86,"++2"},{88,"++3"},{89,"++4"},{91,"++5"},{93,"++6"},{95,"++7"}
};

static QMap<QString,int>revNoteMap = {
    {"--1",36},{"--2",38},{"--3",40},{"--4",41},{"--5",43},{"--6",45},{"--7",47},
    {"-1",48},{"-2",50},{"-3",52},{"-4",53},{"-5",55},{"-6",57},{"-7",59},
    {"1",60},{"2",62},{"3",64},{"4",65},{"5",67},{"6",69},{"7",71},
    {"+1",72},{"+2",74},{"+3",76},{"+4",77},{"+5",79},{"+6",81},{"+7",83},
    {"++1",84},{"++2",86},{"++3",88},{"++4",89},{"++5",91},{"++6",93},{"++7",95}
};

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

public slots:
    void handleMidiEvent(quint32 message, quint32 timing);
    void onDrawNote(QString noteNumber);
    void onStartPractice(int num);
    void handleContinuePractice();

private:
    void initSlot();

private:
    Ui::MainWindow *ui;

private:
    QMidiIn m_midiIn;
    PracticeStatus pracStatus;
    QMap<QString , QString> m_devices;
    DeviceStatus devStatus;
    RecordRank record;

protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void drawNote(QString noteNumber);
    void startPractice(int count);
    void continuePractice();
};
#endif // MAINWINDOW_H
