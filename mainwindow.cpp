#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QElapsedTimer>
#include <QCoreApplication>
#include "qMidi/QMidiOut.h"
#include "qMidi/QMidiFile.h"
#include "qMidi/QMidiIn.h"
#include <QMap>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QTimer>
#include <QProgressBar>
#include <QSound>
#include <qfile.h>
#include <qtextstream.h>
#include <qfiledialog.h>
#include <QDateTime>
#include <define/NoteDef.h>
#include <Utils/practicethread.h>
#include <QMetaType>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      timer(std::make_unique<QTimer>(this)),
      m_pThread(std::make_unique<PracticeThread>()),
      pracThread(std::make_unique<QThread>()),
      progLab(std::make_unique<QLabel>()) ,
      progBar(std::make_unique<QProgressBar>()),
      scene(std::make_unique<QGraphicsScene>()) {
    qRegisterMetaType<Sheet>("Sheet");
    ui->setupUi(this);

    m_pThread->moveToThread(pracThread.get());
    pracThread->start();
    initSlot();
    initUI();
    on_resreshBtn_clicked();
    on_connBtn_clicked();
    on_tuneComb_currentIndexChanged(7);
    shift["Bb"] = { 0,0,-1,0,0,0,-1 };
}

MainWindow::~MainWindow() {
  if (pracThread->isRunning()) {
    pracThread->quit(); // 发送退出信号
    pracThread->wait(); // 等待线程结束
  }
}

void MainWindow::on_resreshBtn_clicked()
{
    this->m_devices = m_midiIn.devices();
    ui->deviceComb->clear();
    for (const QString& name : m_devices) {
        ui->deviceComb->addItem(name);
    }
}

void MainWindow::on_deviceComb_currentIndexChanged(int index)
{
    QString deviceId;
    for (auto it = m_devices.begin(); it != m_devices.end(); it++) {
        if (it.value() == ui->deviceComb->itemText(index)) {
            deviceId = it.key();
        }
    }

    devStatus.curDevId = deviceId;
}


void MainWindow::on_connBtn_clicked()
{
    if (m_midiIn.isConnected()) {
        //断开连接
        m_midiIn.stop();
        m_midiIn.disconnect();
        qDebug() << "disconnect to " << m_devices[m_midiIn.deviceId()];
    }

    // 连接设备
    if (!devStatus.curDevId.isEmpty()) {
        bool conn = m_midiIn.connect(devStatus.curDevId);
        if (conn) {
            qDebug() << "Connection established to " << m_devices[m_midiIn.deviceId()];
            m_midiIn.start();
            qDebug() << "start listening";
            ui->infoEdit->append("connected, start listening");
        }
        else {
            qDebug() << "Connection FAILED";
        }
    }
    else {
        qDebug() << "curDevId is EMPTY";
        return;
    }
}

void MainWindow::handleMidiEvent(quint32 message, quint32 timing)
{
    // https://www.masanao.site/staff/iz/formats/midi-event.html
    QMidiEvent event;
    event.setMessage(message);
    qDebug() << "received event" << event.type()
        << "note:" << event.note()
        << "velocity:" << event.velocity()
        << "amount: " << event.amount()
        << "number: " << event.number()
        << "value: " << event.value()
        << " " << message;
    if (event.type() == 0 && event.velocity() > 0) {
        record.m_tryCount++;

        if (pracStatus.isStart && !(pracStatus.curNote.isEmpty())) {
            QString wantNote = pracStatus.curNote; //+1 -1
            // 偏移
            auto strIter = std::find_if(wantNote.begin(), wantNote.end(), [&](const QChar& c)->bool {
                if (c >= '1' && c <= '7')
                    return true;
                return false;
                });
            QChar lastDigit = *strIter;
            int idx = lastDigit.digitValue();
            assert(idx >= 1 && idx <= 7);
            int midiValue = revNoteMap[wantNote];
            midiValue += noteShift[idx - 1];
            wantNote = NoteMap[midiValue];
            //偏移
            QString receivedNoteStr = NoteMap[event.note()];
            QString staffNoteSrt = revStaffNoteMap[event.note()];
            qDebug() << "wating Note: " << wantNote << " receive: " << event.note() << "-" << receivedNoteStr;
            //qDebug()<<"尝试第"<<record.m_tryCount<<"次 用时"<< record.m_time.elapsed()/1000.0 <<"秒";
            emit playNoteSound(staffNoteSrt);
            if (event.type() == 0 && wantNote == receivedNoteStr && event.velocity() != 0) { //吹对
                if (pracStatus.perfact) {
                    pracStatus.perfectCount++;
                    ui->infoEdit->append("perfect!! ");
                    QTextCharFormat fmt;//文本字符格式
                    fmt.setForeground(QColor(250, 235, 215));// 前景色(即字体色)设为color色
                    QTextCursor cursor = ui->infoEdit->textCursor();//获取文本光标
                    cursor.mergeCharFormat(fmt);//光标后的文字就用该格式显示
                    ui->infoEdit->mergeCurrentCharFormat(fmt);//textEdit使用当前的字符格式
                }

                emit handleContinuePractice();
            }
        }
    }
}

void MainWindow::onDrawNote(QString noteNumber)
{
    // 创建 QGraphicsScene
    //scene->setSceneRect(0, 0, 300, 300);
    if (notePicItem) {
        scene->removeItem(notePicItem.get());
    }

    QPixmap notePic = QPixmap(":/note/res/NotePic/" + noteNumber + ".jpg");
    notePicItem.reset(new QGraphicsPixmapItem(notePic));
    notePicItem->setScale(2);
    notePicItem->setPos(450, 200);
    scene->addItem(notePicItem.get());
    ui->noteGraphView->setScene(scene.get());
    ui->noteGraphView->show();
}

void MainWindow::onDrawTune(QString tuneStr)
{
    //:/note/res/TunePic/tune_Eb.jpg
    QString path = ":/note/res/TunePic/tune_" + tuneStr + ".jpg";
    //scene->setSceneRect(0, 0, 300, 300);
    if (tunePicItem) {
        scene->removeItem(tunePicItem.get());
    }

    QPixmap notePic = QPixmap(path);
    tunePicItem.reset(new QGraphicsPixmapItem(notePic));
    tunePicItem->setScale(1.5);
    tunePicItem->setPos(20, 20);
    scene->addItem(tunePicItem.get());
    qDebug() << ui->noteGraphView->scene();
    ui->noteGraphView->setScene(scene.get());
    qDebug() << ui->noteGraphView->scene();
    ui->noteGraphView->show();
}

void MainWindow::onStartPractice(int num)
{
    //没开始时
    if (!pracStatus.isStart) {
        pracStatus.isStart = true;
        pracStatus.totalCount = num;
        pracStatus.curCount = 1;
    }

    //随机生成序号
    // 随机选择一个图片路径
    int randomIndex = QRandomGenerator::global()->bounded(9999) % noteName.size();
    QString noteIndexStr = noteName[randomIndex]; // +1 ++1
    //显示
    emit drawNote(noteIndexStr);
    emit startTimer(perfectTimeDuration);
    pracStatus.curNote = noteIndexStr;
    //等待midi信号 如果midi信号能够映射为++几个 则自动emit HandlePractice

    //放一个waiting for 初始化为-int min 如果在handleMidievent里找到wating for 就成功，继续发送handlePractice

}

void MainWindow::handleContinuePractice()
{
    pracStatus.curCount++;
    if (pracStatus.curCount > pracStatus.totalCount) {
        double sec = record.m_time.elapsed() / 1000.0;
        double rate = pracStatus.totalCount / record.m_tryCount;
        QString infoStr = "您本次用时 " + QString::number(sec) + " 正确率: " + QString::number(rate) +
            " 完美次数" + QString::number(pracStatus.perfectCount) +
            " 完美率" + QString::number((1.0 * (pracStatus.perfectCount)) / pracStatus.totalCount)
            ;
        pracStatus.isStart = false;
        QMessageBox::information(this, "练习结束", infoStr);
        return;
    }

    //随机生成序号
    // 随机选择一个图片路径
    int randomIndex = QRandomGenerator::global()->bounded(9999) % noteName.size();
    QString noteIndexStr = noteName[randomIndex]; // +1 ++1
    //显示
    emit drawNote(noteIndexStr);
    pracStatus.curNote = noteIndexStr;
    //等待midi信号 如果midi信号能够映射为++几个 则自动emit HandlePractice
    emit startTimer(perfectTimeDuration);
}

void MainWindow::handleStartTimer(double sec)
{
    //如果开启5s
    pracStatus.perfact = true;
    progBar->show();
    progLab->setText("perfect time!!");
    progLab->show();
    int rangeMax = sec * 10;
    progBar->setRange(0, rangeMax);
    progBar->setValue(rangeMax);
    //0 50 
    connect(timer.get(), &QTimer::timeout, this, [=]() {
        progBar->setValue(progBar->value() - 1);
        if (progBar->value() == 0) {
            timer->stop();
            pracStatus.perfact = false;
            progBar->hide();
            progLab->hide();
        }
        });
    timer->start(100);
}

void MainWindow::handlePlayNote(QString noteStr)
{
    //:/voice/res/voice/B5.wav
    QString wavName = ":/voice/res/voice/" + noteStr + ".wav";
    QSound::play(wavName);
}

void MainWindow::initSlot()
{
    connect(&m_midiIn, &QMidiIn::midiEvent, this, &MainWindow::handleMidiEvent);
    connect(this, &MainWindow::drawNote, this, &MainWindow::onDrawNote);
    connect(this, &MainWindow::startPractice, this, &MainWindow::onStartPractice);
    connect(this, &MainWindow::continuePractice, this, &MainWindow::handleContinuePractice);
    connect(this, &MainWindow::startTimer, this, &MainWindow::handleStartTimer);
    connect(this, &MainWindow::playNoteSound, this, &MainWindow::handlePlayNote);
    connect(this, &MainWindow::drawTune, this, &MainWindow::onDrawTune);
    // 连接练习信号 和练习线程的prevNext drawNote
    assert(m_pThread);
    connect(this, &MainWindow::startPlaySheetPractice, m_pThread.get(), &PracticeThread::handleStartPlaySheetPractice);
    connect(m_pThread.get(), &PracticeThread::drawNote, this, &MainWindow::onDrawNote);
    connect(m_pThread.get(), &PracticeThread::prevNote, this, &MainWindow::onDrawNote);
}

void MainWindow::initUI()
{
    scene->setSceneRect(0, 0, 1500, 800);
    ui->statusbar->addWidget(progBar.get());
    ui->statusbar->addWidget(progLab.get());
    progBar->hide();
    progLab->hide();
    progBar->setRange(0, 50);
    progBar->setValue(50);
}

void MainWindow::onPrevNote(Node* note)
{
    // tune: Bb note: C
    //Node

}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (m_midiIn.isConnected()) {
        m_midiIn.stop();
        qDebug() << "stop listening";
        m_midiIn.disconnect();
        qDebug() << "disconnect to " << m_devices[m_midiIn.deviceId()];
    }
}


void MainWindow::on_startBtn_clicked()
{
    emit startPractice(ui->numEdit->text().toInt());
    record.m_tryCount = 0;
    record.m_time.start();
}


void MainWindow::on_btnHint_clicked()
{
    QString simpNoteStr = pracStatus.curNote;
    int noteValue = revNoteMap[simpNoteStr];
    QString staffNote = revStaffNoteMap[noteValue];

    ui->infoEdit->append("当前音符 " + staffNote);
}


void MainWindow::on_btnOpenFile_clicked()
{
    sheet.notes.clear();
    // 弹出文件选择对话框,要求选择后缀名为 .txt 的文件
    QString fileName = QFileDialog::getOpenFileName(
        nullptr,
        "打开乐谱文件",
        QDir::homePath(),
        "Text Files (*.txt)"
    );

    if (fileName.isEmpty()) {
        ui->infoEdit->append("未选择文件");
        return;
    }

    // 打开选定的文件
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->infoEdit->append("打开文件失败");
        return;
    }

    if (!sheet.notes.empty()) {
        // 释放之前的节点
        for (Node *note : sheet.notes) {
            delete note;
        }
    }
    sheet.notes.clear(); // 清空节点列表

    // 读取文件内容
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) {
            continue;
        }

        if (line.startsWith("@")) {
            QStringList param = line.split(":");
            if (param[0] == "@Author") {
                sheet.author = param[1];
            } 
            else if (param[0] == "@Title") {
                assert(param.size() == 2);
                sheet.title = param[1];
            } 
            else if (param[0] == "@Name") {
                assert(param.size() == 2);
                sheet.name = param[1];
            }
            else if (param[0] == "@Tune") {
                assert(param.size() == 2);
                sheet.tune = param[1];
            }
            else if (param[0] == "@Body") {
                // 读取音符 C4:D4:E4:F4:G4:A4:B4:--
                QString bodyLine = in.readLine().trimmed();
                QStringList notes = bodyLine.split(":");
                // 读取时值 16:32:4:1:2:4:8
                QString timeLine = in.readLine().trimmed();
                QStringList times = timeLine.split(":");
                if (bodyLine.isEmpty() || timeLine.isEmpty() || notes.size() != times.size()) {
                    ui->infoEdit->append("音符和时值不匹配");
                    assert(false);
                }
                
                Node *newNode;
                for (int i = 0; i < notes.size(); i++) {
                    if (notes[i].isEmpty() || times[i].isEmpty()) {
                        continue;
                    }

                    newNode = new Node(notes[i]);
                    newNode->setDuration(times[i]);
                    sheet.notes.push_back(newNode);
                }
            }
        } else if (line.startsWith("#")) {
            // 注释
            continue;
        } else {
            continue;
        }
    }
    file.close();
}


void MainWindow::on_btnStartPlay_clicked()
{
    emit startPlaySheetPractice(sheet);
}

void MainWindow::on_tuneComb_currentIndexChanged(int index)
{
    QString tune = ui->tuneComb->currentText();
    if (tuneMap.contains(tune)) {
        // 设置偏移量
        noteShift = tuneMap[tune];
        auto it = std::find_if_not(tune.begin(), tune.end(), [](QChar c)->bool {
            return (c >= 'A' && c <= 'G') || (c >= 'a' && c <= 'g') || c == '#';
        });
        QVector<QChar> tuneName(tune.begin(), it);
        assert(!tuneName.isEmpty());
        QString noteStr(tuneName.begin(), tuneName.size());
        emit drawTune(noteStr);
    }
};

