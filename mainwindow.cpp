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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!timer){
        timer=new QTimer;
    }
    initSlot();
    initUI();
    on_resreshBtn_clicked();
    on_connBtn_clicked();
}

MainWindow::~MainWindow()
{
    if (!timer) {
        delete timer;
    }
    if (!progBar) {
        delete progBar;
    }

    delete ui;
}

void MainWindow::on_resreshBtn_clicked()
{
    this->m_devices=m_midiIn.devices();
    ui->deviceComb->clear();
    for(const QString& name : m_devices){
        ui->deviceComb->addItem(name);
    }
}

void MainWindow::on_deviceComb_currentIndexChanged(int index)
{
    QString deviceId;
    for (auto it = m_devices.begin(); it != m_devices.end(); it++) {
        if(it.value()==ui->deviceComb->itemText(index)){
            deviceId=it.key();
        }
    }

    devStatus.curDevId=deviceId;
}


void MainWindow::on_connBtn_clicked()
{
    if(m_midiIn.isConnected()){
        //断开连接
        m_midiIn.stop();
        m_midiIn.disconnect();
        qDebug()<<"disconnect to "<<m_devices[m_midiIn.deviceId()];
    }

    // 连接设备
    if(!devStatus.curDevId.isEmpty()){
        bool conn=m_midiIn.connect(devStatus.curDevId);
        if(conn){
            qDebug()<<"Connection established to "<<m_devices[m_midiIn.deviceId()];
            m_midiIn.start();
            qDebug()<<"start listening";
            ui->infoEdit->append("connected, start listening");
        }else{
            qDebug()<<"Connection FAILED";
        }
    }else{
        qDebug()<<"curDevId is EMPTY";
        return;
    }
}

void MainWindow::handleMidiEvent(quint32 message, quint32 timing)
{
    // https://www.masanao.site/staff/iz/formats/midi-event.html
    QMidiEvent event;
    event.setMessage(message);
    if(event.type()==0&&event.velocity()>0){
        record.m_tryCount++;
        qDebug() << "received event" << event.type()
                 << "note:" << event.note()
                 << "velocity:" << event.velocity()
                 <<"amount: "<<event.amount()
                 <<"number: "<<event.number()
                 <<"value: "<<event.value()
                 << " " << message;
        if(pracStatus.isStart&&!(pracStatus.curNote.isEmpty())){
            QString wantNote=pracStatus.curNote; //+1 -1
            QString receivedNoteStr=NoteMap[event.note()];
            QString staffNoteSrt=revStaffNoteMap[event.note()];
            qDebug()<<"等待Note: "<<wantNote<<" 收到"<<event.note()<<"-"<<receivedNoteStr;
            //qDebug()<<"尝试第"<<record.m_tryCount<<"次 用时"<< record.m_time.elapsed()/1000.0 <<"秒";
            emit playNoteSound(staffNoteSrt);
            if(event.type()==0&&wantNote==receivedNoteStr&&event.velocity()!=0){ //吹对
                if (pracStatus.perfact) {
                    pracStatus.perfectCount++;
                    ui->infoEdit->append("perfect!! ");
                    QTextCharFormat fmt;//文本字符格式
                    fmt.setForeground(QColor(250,235,215));// 前景色(即字体色)设为color色
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
    QGraphicsScene *scene=new QGraphicsScene();
    scene->setSceneRect(0, 0, 300, 300);
    QPixmap notePic=QPixmap(":/note/res/NotePic/"+noteNumber+".jpg");
    QGraphicsPixmapItem* pictureItem = new QGraphicsPixmapItem(notePic);
    //pictureItem->setPos(100, 100);
    scene->addItem(pictureItem);
    qDebug()<<ui->noteGraphView->scene();
    ui->noteGraphView->setScene(scene);
    qDebug()<<ui->noteGraphView->scene();
    ui->noteGraphView->show();
}

void MainWindow::onStartPractice(int num)
{
    //没开始时
    if(!pracStatus.isStart){
        pracStatus.isStart=true;
        pracStatus.totalCount=num;
        pracStatus.curCount=1;
    }

    //随机生成序号
    // 随机选择一个图片路径
    int randomIndex = QRandomGenerator::global()->bounded(9999) % noteName.size();
    QString noteIndexStr = noteName[randomIndex]; // +1 ++1
    //显示
    emit drawNote(noteIndexStr);
    emit startTimer(perfectTimeDuration);
    pracStatus.curNote=noteIndexStr;
    //等待midi信号 如果midi信号能够映射为++几个 则自动emit HandlePractice

    //放一个waiting for 初始化为-int min 如果在handleMidievent里找到wating for 就成功，继续发送handlePractice

}

void MainWindow::handleContinuePractice()
{
    pracStatus.curCount++;
    if(pracStatus.curCount>pracStatus.totalCount){
        double sec=record.m_time.elapsed()/1000.0;
        double rate=pracStatus.totalCount/record.m_tryCount;
        QString infoStr="您本次用时 "+QString::number(sec)+" 正确率: "+QString::number(rate)+
            " 完美次数" + QString::number(pracStatus.perfectCount) + 
            " 完美率" + QString::number((1.0*(pracStatus.perfectCount))/ pracStatus.totalCount)
            ;
        pracStatus.isStart=false;
        QMessageBox::information(this,"练习结束",infoStr);
        return;
    }

    //随机生成序号
    // 随机选择一个图片路径
    int randomIndex = QRandomGenerator::global()->bounded(9999) % noteName.size();
    QString noteIndexStr = noteName[randomIndex]; // +1 ++1
    //显示
    emit drawNote(noteIndexStr);
    pracStatus.curNote=noteIndexStr;
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
    connect(timer, &QTimer::timeout, this, [=]() {
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
    QString wavName = ":/voice/res/voice/"+ noteStr + ".wav";
    QSound::play(wavName);
}

void MainWindow::initSlot()
{
    connect(&m_midiIn, &QMidiIn::midiEvent, this, &MainWindow::handleMidiEvent);
    connect(this,&MainWindow::drawNote,this,&MainWindow::onDrawNote);
    connect(this,&MainWindow::startPractice,this,&MainWindow::onStartPractice);
    connect(this,&MainWindow::continuePractice,this,&MainWindow::handleContinuePractice);
    connect(this, &MainWindow::startTimer, this, &MainWindow::handleStartTimer);
    connect(this, &MainWindow::playNoteSound, this, &MainWindow::handlePlayNote);
}

void MainWindow::initUI()
{
    progBar = new QProgressBar;
    progLab = new QLabel;
    ui->statusbar->addWidget(progBar);
    ui->statusbar->addWidget(progLab);
    progBar->hide();
    progLab->hide();
    progBar->setRange(0, 50);
    progBar->setValue(50);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_midiIn.isConnected()){
        m_midiIn.stop();
        qDebug()<<"stop listening";
        m_midiIn.disconnect();
        qDebug()<<"disconnect to "<<m_devices[m_midiIn.deviceId()];
    }
}


void MainWindow::on_startBtn_clicked()
{
    emit startPractice(ui->numEdit->text().toInt());
    record.m_tryCount=0;
    record.m_time.start();
}


void MainWindow::on_btnHint_clicked()
{
    QString simpNoteStr=pracStatus.curNote;
    int noteValue = revNoteMap[simpNoteStr];
    QString staffNote=revStaffNoteMap[noteValue];

    ui->infoEdit->append("当前音符 "+staffNote);
}

