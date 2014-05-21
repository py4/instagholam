/********************************************************************************
** Form generated from reading UI file 'fellowwindow.ui'
**
** Created: Wed May 21 22:21:05 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FELLOWWINDOW_H
#define UI_FELLOWWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fellowwindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *profile_tab;
    QTableWidget *profile_table;
    QPushButton *pushButton;
    QLabel *label;
    QPushButton *pushButton2;
    QWidget *friends_tab;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *fellowwindow)
    {
        if (fellowwindow->objectName().isEmpty())
            fellowwindow->setObjectName(QString::fromUtf8("fellowwindow"));
        fellowwindow->resize(800, 600);
        centralwidget = new QWidget(fellowwindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 801, 551));
        profile_tab = new QWidget();
        profile_tab->setObjectName(QString::fromUtf8("profile_tab"));
        profile_table = new QTableWidget(profile_tab);
        profile_table->setObjectName(QString::fromUtf8("profile_table"));
        profile_table->setGeometry(QRect(0, 0, 791, 431));
        pushButton = new QPushButton(profile_tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 470, 141, 27));
        label = new QLabel(profile_tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 440, 141, 17));
        pushButton2 = new QPushButton(profile_tab);
        pushButton2->setObjectName(QString::fromUtf8("pushButton2"));
        pushButton2->setGeometry(QRect(150, 470, 161, 27));
        tabWidget->addTab(profile_tab, QString());
        friends_tab = new QWidget();
        friends_tab->setObjectName(QString::fromUtf8("friends_tab"));
        tabWidget->addTab(friends_tab, QString());
        fellowwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(fellowwindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        fellowwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(fellowwindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        fellowwindow->setStatusBar(statusbar);

        retranslateUi(fellowwindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(fellowwindow);
    } // setupUi

    void retranslateUi(QMainWindow *fellowwindow)
    {
        fellowwindow->setWindowTitle(QApplication::translate("fellowwindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("fellowwindow", "PushButton", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("fellowwindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        pushButton2->setText(QApplication::translate("fellowwindow", "PushButton", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(profile_tab), QApplication::translate("fellowwindow", "Profile", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(friends_tab), QApplication::translate("fellowwindow", "Friends", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class fellowwindow: public Ui_fellowwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FELLOWWINDOW_H
