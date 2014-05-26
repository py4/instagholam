/********************************************************************************
** Form generated from reading UI file 'adminwindow.ui'
**
** Created: Tue May 27 01:28:39 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINWINDOW_H
#define UI_ADMINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_adminwindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *users_tab;
    QTableWidget *admin_users_table;
    QWidget *new_user_tab;
    QLineEdit *register_password;
    QLabel *label_4;
    QLabel *label_6;
    QLineEdit *avatar_file;
    QPushButton *select_avatar;
    QLabel *label_5;
    QPushButton *register_button;
    QLineEdit *register_full_name;
    QLineEdit *register_username;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *adminwindow)
    {
        if (adminwindow->objectName().isEmpty())
            adminwindow->setObjectName(QString::fromUtf8("adminwindow"));
        adminwindow->resize(800, 600);
        centralwidget = new QWidget(adminwindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 801, 461));
        users_tab = new QWidget();
        users_tab->setObjectName(QString::fromUtf8("users_tab"));
        admin_users_table = new QTableWidget(users_tab);
        admin_users_table->setObjectName(QString::fromUtf8("admin_users_table"));
        admin_users_table->setGeometry(QRect(0, 0, 801, 461));
        tabWidget->addTab(users_tab, QString());
        new_user_tab = new QWidget();
        new_user_tab->setObjectName(QString::fromUtf8("new_user_tab"));
        register_password = new QLineEdit(new_user_tab);
        register_password->setObjectName(QString::fromUtf8("register_password"));
        register_password->setGeometry(QRect(290, 170, 251, 31));
        label_4 = new QLabel(new_user_tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(210, 80, 71, 21));
        label_6 = new QLabel(new_user_tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(200, 170, 67, 17));
        avatar_file = new QLineEdit(new_user_tab);
        avatar_file->setObjectName(QString::fromUtf8("avatar_file"));
        avatar_file->setGeometry(QRect(290, 220, 251, 27));
        select_avatar = new QPushButton(new_user_tab);
        select_avatar->setObjectName(QString::fromUtf8("select_avatar"));
        select_avatar->setGeometry(QRect(190, 220, 71, 27));
        label_5 = new QLabel(new_user_tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(200, 130, 71, 17));
        register_button = new QPushButton(new_user_tab);
        register_button->setObjectName(QString::fromUtf8("register_button"));
        register_button->setGeometry(QRect(310, 270, 111, 27));
        register_full_name = new QLineEdit(new_user_tab);
        register_full_name->setObjectName(QString::fromUtf8("register_full_name"));
        register_full_name->setGeometry(QRect(290, 80, 251, 31));
        register_username = new QLineEdit(new_user_tab);
        register_username->setObjectName(QString::fromUtf8("register_username"));
        register_username->setGeometry(QRect(290, 120, 251, 31));
        tabWidget->addTab(new_user_tab, QString());
        adminwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(adminwindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        adminwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(adminwindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        adminwindow->setStatusBar(statusbar);

        retranslateUi(adminwindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(adminwindow);
    } // setupUi

    void retranslateUi(QMainWindow *adminwindow)
    {
        adminwindow->setWindowTitle(QApplication::translate("adminwindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(users_tab), QApplication::translate("adminwindow", "Users", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("adminwindow", "Full name", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("adminwindow", "Password", 0, QApplication::UnicodeUTF8));
        select_avatar->setText(QApplication::translate("adminwindow", "Avatar", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("adminwindow", "Username", 0, QApplication::UnicodeUTF8));
        register_button->setText(QApplication::translate("adminwindow", "register", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(new_user_tab), QApplication::translate("adminwindow", "New User", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class adminwindow: public Ui_adminwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINWINDOW_H
