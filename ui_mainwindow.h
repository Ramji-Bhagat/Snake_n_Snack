/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *workArea;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_22;
    QLCDNumber *score;
    QPushButton *start;
    QPushButton *pandr;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(574, 760);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        workArea = new QLabel(centralwidget);
        workArea->setObjectName("workArea");
        workArea->setGeometry(QRect(10, 90, 541, 501));
        workArea->setStyleSheet(QString::fromUtf8(""));
        workArea->setFrameShape(QFrame::Shape::Box);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 40, 161, 33));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_22 = new QLabel(layoutWidget);
        label_22->setObjectName("label_22");
        label_22->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);\n"
"\n"
"\n"
"color: rgb(255, 255, 255);\n"
"font: 700 italic 18pt \"Rockwell\";\n"
""));

        horizontalLayout->addWidget(label_22);

        score = new QLCDNumber(layoutWidget);
        score->setObjectName("score");
        score->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));

        horizontalLayout->addWidget(score);

        start = new QPushButton(centralwidget);
        start->setObjectName("start");
        start->setGeometry(QRect(230, 40, 80, 31));
        start->setMinimumSize(QSize(80, 0));
        start->setMaximumSize(QSize(80, 16777215));
        start->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 127);\n"
"color: rgb(0, 0, 0);\n"
"font: 700 11pt \"Rockwell\";"));
        pandr = new QPushButton(centralwidget);
        pandr->setObjectName("pandr");
        pandr->setGeometry(QRect(390, 40, 150, 30));
        pandr->setMinimumSize(QSize(150, 30));
        pandr->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 127);\n"
"background-color: rgb(255, 29, 63);\n"
"color: rgb(0, 0, 0);\n"
"font: 700 12pt \"Rockwell\";"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(120, 610, 311, 31));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 255);\n"
"font: 700 12pt \"Script MT Bold\";\n"
"color: rgb(0, 0, 0);"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 10, 271, 21));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 19pt \"Ravie\";\n"
"\n"
"\n"
"\n"
""));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        workArea->setText(QString());
        label_22->setText(QCoreApplication::translate("MainWindow", " Score", nullptr));
        start->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        pandr->setText(QCoreApplication::translate("MainWindow", "Pause/Resume", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "  Press space bar to pause and resume the game", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Snake  'n'  Snack", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
