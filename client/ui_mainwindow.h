/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue May 27 01:28:39 2014
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
#include <QtGui/QCheckBox>
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
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLogout;
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *login_form;
    QLineEdit *username;
    QLineEdit *password;
    QLabel *label;
    QLabel *label_2;
    QPushButton *sign_in;
    QWidget *layoutWidget;
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
    QLineEdit *register_password_2;
    QLabel *label_9;
    QLabel *label_11;
    QLineEdit *avatar_file_2;
    QPushButton *select_avatar_2;
    QLabel *label_12;
    QPushButton *register_button_2;
    QLineEdit *register_full_name_2;
    QLineEdit *register_username_2;
    QWidget *home_page;
    QTabWidget *tabWidget;
    QWidget *home_tab;
    QTableWidget *home_table;
    QPushButton *refresh_button;
    QWidget *share_tab;
    QLabel *label_7;
    QCheckBox *share_pub_checkbox;
    QPushButton *share_button;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QLineEdit *share_title;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_10;
    QLineEdit *share_hashtags;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *share_select_file;
    QLineEdit *share_file_name;
    QWidget *profile_tab;
    QTableWidget *profile_table;
    QWidget *friends_tab;
    QTableWidget *friends_table;
    QWidget *requests_tab;
    QTableWidget *requests_table;
    QWidget *people_tab;
    QTableWidget *people_table;
    QWidget *explore_tab;
    QLabel *avatar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionLogout = new QAction(MainWindow);
        actionLogout->setObjectName(QString::fromUtf8("actionLogout"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 0, 791, 531));
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
        layoutWidget = new QWidget(login_form);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(300, 250, 182, 29));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        register_2 = new QPushButton(layoutWidget);
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
        register_password_2 = new QLineEdit(register_form);
        register_password_2->setObjectName(QString::fromUtf8("register_password_2"));
        register_password_2->setGeometry(QRect(200, 210, 251, 31));
        label_9 = new QLabel(register_form);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(100, 130, 71, 21));
        label_11 = new QLabel(register_form);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(100, 220, 67, 17));
        avatar_file_2 = new QLineEdit(register_form);
        avatar_file_2->setObjectName(QString::fromUtf8("avatar_file_2"));
        avatar_file_2->setGeometry(QRect(200, 250, 251, 27));
        select_avatar_2 = new QPushButton(register_form);
        select_avatar_2->setObjectName(QString::fromUtf8("select_avatar_2"));
        select_avatar_2->setGeometry(QRect(100, 250, 71, 27));
        label_12 = new QLabel(register_form);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(100, 180, 71, 17));
        register_button_2 = new QPushButton(register_form);
        register_button_2->setObjectName(QString::fromUtf8("register_button_2"));
        register_button_2->setGeometry(QRect(270, 310, 111, 27));
        register_full_name_2 = new QLineEdit(register_form);
        register_full_name_2->setObjectName(QString::fromUtf8("register_full_name_2"));
        register_full_name_2->setGeometry(QRect(200, 130, 251, 31));
        register_username_2 = new QLineEdit(register_form);
        register_username_2->setObjectName(QString::fromUtf8("register_username_2"));
        register_username_2->setGeometry(QRect(200, 170, 251, 31));
        stackedWidget->addWidget(register_form);
        home_page = new QWidget();
        home_page->setObjectName(QString::fromUtf8("home_page"));
        tabWidget = new QTabWidget(home_page);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 801, 551));
        home_tab = new QWidget();
        home_tab->setObjectName(QString::fromUtf8("home_tab"));
        home_table = new QTableWidget(home_tab);
        home_table->setObjectName(QString::fromUtf8("home_table"));
        home_table->setGeometry(QRect(0, 0, 791, 441));
        refresh_button = new QPushButton(home_tab);
        refresh_button->setObjectName(QString::fromUtf8("refresh_button"));
        refresh_button->setGeometry(QRect(340, 450, 99, 27));
        tabWidget->addTab(home_tab, QString());
        share_tab = new QWidget();
        share_tab->setObjectName(QString::fromUtf8("share_tab"));
        label_7 = new QLabel(share_tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(230, 10, 341, 71));
        share_pub_checkbox = new QCheckBox(share_tab);
        share_pub_checkbox->setObjectName(QString::fromUtf8("share_pub_checkbox"));
        share_pub_checkbox->setGeometry(QRect(410, 220, 98, 22));
        share_button = new QPushButton(share_tab);
        share_button->setObjectName(QString::fromUtf8("share_button"));
        share_button->setGeometry(QRect(310, 220, 99, 27));
        layoutWidget1 = new QWidget(share_tab);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(190, 90, 381, 29));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_2->addWidget(label_8);

        share_title = new QLineEdit(layoutWidget1);
        share_title->setObjectName(QString::fromUtf8("share_title"));

        horizontalLayout_2->addWidget(share_title);

        layoutWidget2 = new QWidget(share_tab);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(190, 170, 301, 29));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_4->addWidget(label_10);

        share_hashtags = new QLineEdit(layoutWidget2);
        share_hashtags->setObjectName(QString::fromUtf8("share_hashtags"));

        horizontalLayout_4->addWidget(share_hashtags);

        layoutWidget3 = new QWidget(share_tab);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(180, 130, 331, 29));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        share_select_file = new QPushButton(layoutWidget3);
        share_select_file->setObjectName(QString::fromUtf8("share_select_file"));

        horizontalLayout_3->addWidget(share_select_file);

        share_file_name = new QLineEdit(layoutWidget3);
        share_file_name->setObjectName(QString::fromUtf8("share_file_name"));

        horizontalLayout_3->addWidget(share_file_name);

        tabWidget->addTab(share_tab, QString());
        profile_tab = new QWidget();
        profile_tab->setObjectName(QString::fromUtf8("profile_tab"));
        profile_table = new QTableWidget(profile_tab);
        profile_table->setObjectName(QString::fromUtf8("profile_table"));
        profile_table->setGeometry(QRect(0, 0, 801, 421));
        tabWidget->addTab(profile_tab, QString());
        friends_tab = new QWidget();
        friends_tab->setObjectName(QString::fromUtf8("friends_tab"));
        friends_table = new QTableWidget(friends_tab);
        friends_table->setObjectName(QString::fromUtf8("friends_table"));
        friends_table->setGeometry(QRect(0, -1, 801, 461));
        tabWidget->addTab(friends_tab, QString());
        requests_tab = new QWidget();
        requests_tab->setObjectName(QString::fromUtf8("requests_tab"));
        requests_table = new QTableWidget(requests_tab);
        requests_table->setObjectName(QString::fromUtf8("requests_table"));
        requests_table->setGeometry(QRect(0, 0, 801, 441));
        tabWidget->addTab(requests_tab, QString());
        people_tab = new QWidget();
        people_tab->setObjectName(QString::fromUtf8("people_tab"));
        people_table = new QTableWidget(people_tab);
        people_table->setObjectName(QString::fromUtf8("people_table"));
        people_table->setGeometry(QRect(0, 0, 791, 451));
        tabWidget->addTab(people_tab, QString());
        explore_tab = new QWidget();
        explore_tab->setObjectName(QString::fromUtf8("explore_tab"));
        tabWidget->addTab(explore_tab, QString());
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

        stackedWidget->setCurrentIndex(1);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionLogout->setText(QApplication::translate("MainWindow", "Logout", 0, QApplication::UnicodeUTF8));
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
        label_9->setText(QApplication::translate("MainWindow", "Full name", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Password", 0, QApplication::UnicodeUTF8));
        select_avatar_2->setText(QApplication::translate("MainWindow", "Avatar", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "Username", 0, QApplication::UnicodeUTF8));
        register_button_2->setText(QApplication::translate("MainWindow", "Register me!", 0, QApplication::UnicodeUTF8));
        refresh_button->setText(QApplication::translate("MainWindow", "Refresh", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(home_tab), QApplication::translate("MainWindow", "Home", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Share your moments with your friends! :)", 0, QApplication::UnicodeUTF8));
        share_pub_checkbox->setText(QApplication::translate("MainWindow", "Public?", 0, QApplication::UnicodeUTF8));
        share_button->setText(QApplication::translate("MainWindow", "Share!", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Title", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "HashTags", 0, QApplication::UnicodeUTF8));
        share_select_file->setText(QApplication::translate("MainWindow", "Select file", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(share_tab), QApplication::translate("MainWindow", "Share", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(profile_tab), QApplication::translate("MainWindow", "Profile", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(friends_tab), QApplication::translate("MainWindow", "Friends", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(requests_tab), QApplication::translate("MainWindow", "Requests", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(people_tab), QApplication::translate("MainWindow", "People", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(explore_tab), QApplication::translate("MainWindow", "Explore", 0, QApplication::UnicodeUTF8));
        avatar->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
