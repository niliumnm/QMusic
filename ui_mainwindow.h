/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QGraphicsView *noteGraphView;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *numEdit;
    QPushButton *startBtn;
    QPushButton *btnHint;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *labFileName;
    QPushButton *btnOpenFile;
    QPushButton *btnStartPlay;
    QPushButton *btnStopPlay;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QComboBox *deviceComb;
    QPushButton *resreshBtn;
    QPushButton *connBtn;
    QTextEdit *infoEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(980, 639);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        noteGraphView = new QGraphicsView(centralwidget);
        noteGraphView->setObjectName(QString::fromUtf8("noteGraphView"));

        gridLayout->addWidget(noteGraphView, 0, 0, 2, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(100, 16777215));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        numEdit = new QLineEdit(groupBox_2);
        numEdit->setObjectName(QString::fromUtf8("numEdit"));

        verticalLayout->addWidget(numEdit);

        startBtn = new QPushButton(groupBox_2);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));

        verticalLayout->addWidget(startBtn);

        btnHint = new QPushButton(groupBox_2);
        btnHint->setObjectName(QString::fromUtf8("btnHint"));

        verticalLayout->addWidget(btnHint);


        gridLayout->addWidget(groupBox_2, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(100, 16777215));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        labFileName = new QLabel(groupBox_3);
        labFileName->setObjectName(QString::fromUtf8("labFileName"));

        verticalLayout_2->addWidget(labFileName);

        btnOpenFile = new QPushButton(groupBox_3);
        btnOpenFile->setObjectName(QString::fromUtf8("btnOpenFile"));

        verticalLayout_2->addWidget(btnOpenFile);

        btnStartPlay = new QPushButton(groupBox_3);
        btnStartPlay->setObjectName(QString::fromUtf8("btnStartPlay"));

        verticalLayout_2->addWidget(btnStartPlay);

        btnStopPlay = new QPushButton(groupBox_3);
        btnStopPlay->setObjectName(QString::fromUtf8("btnStopPlay"));

        verticalLayout_2->addWidget(btnStopPlay);


        gridLayout->addWidget(groupBox_3, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMaximumSize(QSize(16777215, 100));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 100));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        deviceComb = new QComboBox(groupBox);
        deviceComb->setObjectName(QString::fromUtf8("deviceComb"));
        deviceComb->setMinimumSize(QSize(150, 0));

        horizontalLayout->addWidget(deviceComb);

        resreshBtn = new QPushButton(groupBox);
        resreshBtn->setObjectName(QString::fromUtf8("resreshBtn"));

        horizontalLayout->addWidget(resreshBtn);

        connBtn = new QPushButton(groupBox);
        connBtn->setObjectName(QString::fromUtf8("connBtn"));

        horizontalLayout->addWidget(connBtn);


        horizontalLayout_2->addWidget(groupBox);

        infoEdit = new QTextEdit(frame);
        infoEdit->setObjectName(QString::fromUtf8("infoEdit"));
        infoEdit->setMaximumSize(QSize(16777215, 100));

        horizontalLayout_2->addWidget(infoEdit);


        gridLayout_2->addWidget(frame, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 980, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\347\273\203\344\271\240", nullptr));
        numEdit->setText(QCoreApplication::translate("MainWindow", "32", nullptr));
        startBtn->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        btnHint->setText(QCoreApplication::translate("MainWindow", "\346\217\220\347\244\272", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\346\274\224\345\245\217", nullptr));
        labFileName->setText(QCoreApplication::translate("MainWindow", "\346\227\240\346\226\207\344\273\266", nullptr));
        btnOpenFile->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        btnStartPlay->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        btnStopPlay->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207", nullptr));
        resreshBtn->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        connBtn->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
