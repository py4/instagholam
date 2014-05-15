/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri May 16 00:04:40 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *login_form;
    QLineEdit *username;
    QLineEdit *password;
    QLabel *label;
    QLabel *label_2;
    QPushButton *sign_in;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QPushButton *register_2;
    QWidget *register_form;
    QLineEdit *register_full_name;
    QLineEdit *register_username;
    QLineEdit *register_password;
    QPushButton *select_avatar;
    QLineEdit *avatar_file;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *register_button;
    QWidget *home_page;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QLabel *avatar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 791, 471));
        login_form = new QWidget();
        login_form->setObjectName(QString::fromUtf8("login_form"));
        username = new QLineEdit(login_form);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(260, 130, 311, 27));
        password = new QLineEdit(login_form);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(260, 160, 311, 27));
        label = new QLabel(login_form);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(166, 130, 81, 20));
        label_2 = new QLabel(login_form);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(166, 160, 81, 20));
        sign_in = new QPushButton(login_form);
        sign_in->setObjectName(QString::fromUtf8("sign_in"));
        sign_in->setGeometry(QRect(350, 200, 99, 27));
        widget = new QWidget(login_form);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(300, 250, 182, 29));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        register_2 = new QPushButton(widget);
        register_2->setObjectName(QString::fromUtf8("register_2"));

        horizontalLayout->addWidget(register_2);

        stackedWidget->addWidget(login_form);
        register_form = new QWidget();
        register_form->setObjectName(QString::fromUtf8("register_form"));
        register_full_name = new QLineEdit(register_form);
        register_full_name->setObjectName(QString::fromUtf8("register_full_name"));
        register_full_name->setGeometry(QRect(270, 90, 251, 31));
        register_username = new QLineEdit(register_form);
        register_username->setObjectName(QString::fromUtf8("register_username"));
        register_username->setGeometry(QRect(270, 130, 251, 31));
        register_password = new QLineEdit(register_form);
        register_password->setObjectName(QString::fromUtf8("register_password"));
        register_password->setGeometry(QRect(270, 170, 251, 31));
        select_avatar = new QPushButton(register_form);
        select_avatar->setObjectName(QString::fromUtf8("select_avatar"));
        select_avatar->setGeometry(QRect(170, 210, 71, 27));
        avatar_file = new QLineEdit(register_form);
        avatar_file->setObjectName(QString::fromUtf8("avatar_file"));
        avatar_file->setGeometry(QRect(270, 210, 251, 27));
        label_4 = new QLabel(register_form);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(170, 90, 71, 21));
        label_5 = new QLabel(register_form);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(170, 140, 71, 17));
        label_6 = new QLabel(register_form);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(170, 180, 67, 17));
        register_button = new QPushButton(register_form);
        register_button->setObjectName(QString::fromUtf8("register_button"));
        register_button->setGeometry(QRect(340, 270, 111, 27));
        stackedWidget->addWidget(register_form);
        home_page = new QWidget();
        home_page->setObjectName(QString::fromUtf8("home_page"));
        tabWidget = new QTabWidget(home_page);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 721, 451));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        avatar = new QLabel(home_page);
        avatar->setObjectName(QString::fromUtf8("avatar"));
        avatar->setGeometry(QRect(720, 0, 71, 71));
        stackedWidget->addWidget(home_page);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);
        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Username", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Password", 0, QApplication::UnicodeUTF8));
        sign_in->setText(QApplication::translate("MainWindow", "Sign in", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Not a user?", 0, QApplication::UnicodeUTF8));
        register_2->setText(QApplication::translate("MainWindow", "Register!", 0, QApplication::UnicodeUTF8));
        select_avatar->setText(QApplication::translate("MainWindow", "Avatar", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Full name", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Username", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Password", 0, QApplication::UnicodeUTF8));
        register_button->setText(QApplication::translate("MainWindow", "Register me!", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Home", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Profile", 0, QApplication::UnicodeUTF8));
        avatar->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
