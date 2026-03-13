/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindow
{
public:
    QWidget *centralwidget;
    QLabel *titleLabel;
    QSpinBox *processSpin;
    QLabel *processLabel;
    QTableWidget *processTable;
    QPushButton *fcfsButton;
    QPushButton *sjfButton;
    QPushButton *priorityButton;
    QPushButton *rrButton;
    QLabel *tqLabel;
    QSpinBox *timeQuantumSpin;
    QTextEdit *resultText;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mainwindow)
    {
        if (mainwindow->objectName().isEmpty())
            mainwindow->setObjectName(QString::fromUtf8("mainwindow"));
        mainwindow->resize(1115, 861);
        mainwindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: #e6f2ff;  /* light blue */\n"
"}"));
        centralwidget = new QWidget(mainwindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(80, 90, 700, 50));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setStyleSheet(QString::fromUtf8("color: #003366;       /* dark blue text */\n"
"font-weight: bold;    /* bold text */\n"
"font-size: 16pt;      /* bigger font */"));
        titleLabel->setAlignment(Qt::AlignCenter);
        processSpin = new QSpinBox(centralwidget);
        processSpin->setObjectName(QString::fromUtf8("processSpin"));
        processSpin->setGeometry(QRect(430, 150, 80, 25));
        processSpin->setMinimum(1);
        processSpin->setMaximum(10);
        processSpin->setValue(3);
        processLabel = new QLabel(centralwidget);
        processLabel->setObjectName(QString::fromUtf8("processLabel"));
        processLabel->setGeometry(QRect(250, 150, 151, 21));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(false);
        processLabel->setFont(font1);
        processLabel->setStyleSheet(QString::fromUtf8("color: #000000;\n"
"font-size: 12pt;\n"
""));
        processTable = new QTableWidget(centralwidget);
        if (processTable->columnCount() < 4)
            processTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        processTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        processTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        processTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        processTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (processTable->rowCount() < 10)
            processTable->setRowCount(10);
        processTable->setObjectName(QString::fromUtf8("processTable"));
        processTable->setGeometry(QRect(260, 190, 441, 301));
        processTable->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: #ffffff;   /* white table cells */\n"
"    gridline-color: #cccccc;     /* gray grid lines */\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #3399ff;   /* header blue */\n"
"    color: white;\n"
"    font-weight: bold;\n"
"}"));
        processTable->setRowCount(10);
        processTable->setColumnCount(4);
        fcfsButton = new QPushButton(centralwidget);
        fcfsButton->setObjectName(QString::fromUtf8("fcfsButton"));
        fcfsButton->setGeometry(QRect(220, 500, 120, 35));
        fcfsButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #3399ff;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #66b3ff;\n"
"}"));
        sjfButton = new QPushButton(centralwidget);
        sjfButton->setObjectName(QString::fromUtf8("sjfButton"));
        sjfButton->setGeometry(QRect(350, 500, 120, 35));
        sjfButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #3399ff;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #66b3ff;\n"
"}\n"
""));
        priorityButton = new QPushButton(centralwidget);
        priorityButton->setObjectName(QString::fromUtf8("priorityButton"));
        priorityButton->setGeometry(QRect(480, 500, 120, 35));
        priorityButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #3399ff;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #66b3ff;\n"
"}"));
        rrButton = new QPushButton(centralwidget);
        rrButton->setObjectName(QString::fromUtf8("rrButton"));
        rrButton->setGeometry(QRect(610, 500, 120, 35));
        rrButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #3399ff;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #66b3ff;\n"
"}"));
        tqLabel = new QLabel(centralwidget);
        tqLabel->setObjectName(QString::fromUtf8("tqLabel"));
        tqLabel->setGeometry(QRect(240, 560, 121, 21));
        tqLabel->setStyleSheet(QString::fromUtf8("color: #000000;\n"
"font-size: 12pt;"));
        timeQuantumSpin = new QSpinBox(centralwidget);
        timeQuantumSpin->setObjectName(QString::fromUtf8("timeQuantumSpin"));
        timeQuantumSpin->setGeometry(QRect(380, 560, 80, 25));
        timeQuantumSpin->setMinimum(1);
        timeQuantumSpin->setMaximum(20);
        timeQuantumSpin->setValue(2);
        resultText = new QTextEdit(centralwidget);
        resultText->setObjectName(QString::fromUtf8("resultText"));
        resultText->setGeometry(QRect(190, 600, 700, 200));
        resultText->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    background-color: #fefefe;\n"
"    color: #003366;\n"
"    font-family: Consolas;  \n"
"    font-size: 10pt;\n"
"}"));
        resultText->setReadOnly(true);
        mainwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainwindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1115, 19));
        mainwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(mainwindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        mainwindow->setStatusBar(statusbar);

        retranslateUi(mainwindow);

        QMetaObject::connectSlotsByName(mainwindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainwindow)
    {
        mainwindow->setWindowTitle(QCoreApplication::translate("mainwindow", "CpuSchedulingSimulator", nullptr));
        titleLabel->setText(QCoreApplication::translate("mainwindow", "CPU Scheduling Simulator", nullptr));
        processLabel->setText(QCoreApplication::translate("mainwindow", "Number of Processes", nullptr));
        QTableWidgetItem *___qtablewidgetitem = processTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("mainwindow", "PID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = processTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("mainwindow", "Arrival Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = processTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("mainwindow", "Burst Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = processTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("mainwindow", "Priority", nullptr));
        fcfsButton->setText(QCoreApplication::translate("mainwindow", "FCFS", nullptr));
        sjfButton->setText(QCoreApplication::translate("mainwindow", "SJF", nullptr));
        priorityButton->setText(QCoreApplication::translate("mainwindow", "PRIORITY", nullptr));
        rrButton->setText(QCoreApplication::translate("mainwindow", "ROUND ROBBINS", nullptr));
        tqLabel->setText(QCoreApplication::translate("mainwindow", "Time Quantum", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainwindow: public Ui_mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
