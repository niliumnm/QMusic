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
#include <QDebug>
#include <qvector.h>
#include <QGraphicsScene>

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
//音符的定义
struct Node {
    int value = -1;
    int duration = -1;
    Node* next=nullptr;
    Node() {

    };
    Node(QString strNote) {
        if (staffNoteMap.contains(strNote)) {
            //是五线谱的内容
            value = staffNoteMap[strNote];
        }
        else if (revNoteMap.contains(strNote)) {
            value = revNoteMap[strNote];
        }
        else {
            qDebug() << "Wrong Note!!!";
        }
    }
    void setDuration(QString time) {
        duration = time.toInt();
    }
};

struct Sheet {
    QString name;
    QString author;
    QString title;
    int count = 0;
    Node* dummyHead=new Node;
    Node* tail = nullptr;
    void insert(Node* node) {
        if (count==0) {
            dummyHead->next = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = tail->next;
        }
        count++;
    }
    void deleteHead() {
        if (count == 0) return;
        Node* tobeDel = dummyHead->next;
        dummyHead = dummyHead->next;
        delete tobeDel;
    };
    bool isValid() {
        if (dummyHead != nullptr && dummyHead->next != nullptr && count > 0) {
            return true;
        }
        return false;
    }
    bool isEmpty() {
        return count == 0;
    }
    void outputValue() {
        Node* cur = dummyHead;
        int cnt = 0;
        while (cur->next)
        {
            cur = cur->next;
            qDebug() << "note: " << cur->value << "("+ revStaffNoteMap[cur->value] + ") " << cur->duration << "\n";
            cnt++;
        }
        assert(cnt == count);
    }
    ~Sheet()
    {
        // 遍历链表,逐个释放节点内存
        while (dummyHead != nullptr) {
            Node* temp = dummyHead;
            dummyHead = dummyHead->next;
            delete temp;
        }

        // 将链表头指针设置为 nullptr
        dummyHead = nullptr;
    }
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
    void on_btnOpenFile_clicked();
    void on_btnStartPlay_clicked();
    void on_tuneComb_currentIndexChanged(int index);

public slots:
    void handleMidiEvent(quint32 message, quint32 timing);
    void onDrawNote(QString noteNumber);
    void onDrawTune(QString tuneStr);
    void onStartPractice(int num);
    void handleContinuePractice();
    void handleStartTimer(double sec);
    void handlePlayNote(QString noteStr);
    void handleStartPlaySheetPractice();

private:
    void initSlot();
    void initUI();
    inline bool isSame(QString strA, QString strB);

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
    Sheet sheet;
    QVector<int>noteShift={0,0,-1,0,0,0,-1};
    QGraphicsScene *scene;
    QGraphicsItem* notePicItem = nullptr;
    QGraphicsItem* tunePicItem = nullptr;

protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void drawNote(QString noteNumber);
    void drawTune(QString tuneStr);
    void startPractice(int count);
    void continuePractice();
    void startTimer(double sec);
    void playNoteSound(QString note);
    void startPlaySheetPractice();
};
#endif // MAINWINDOW_H
