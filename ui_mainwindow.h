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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
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
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QGraphicsView *noteGraphView;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *numEdit;
    QPushButton *startBtn;
    QPushButton *btnHint;
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
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        noteGraphView = new QGraphicsView(centralwidget);
        noteGraphView->setObjectName(QString::fromUtf8("noteGraphView"));

        horizontalLayout_3->addWidget(noteGraphView);

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


        horizontalLayout_3->addWidget(groupBox_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

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


        verticalLayout_2->addWidget(frame);

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
