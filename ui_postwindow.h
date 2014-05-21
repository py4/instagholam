/********************************************************************************
** Form generated from reading UI file 'postwindow.ui'
**
** Created: Wed May 21 22:49:55 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSTWINDOW_H
#define UI_POSTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PostWindow
{
public:
    QWidget *centralwidget;
    QLabel *photo;
    QLabel *title;
    QLabel *username;
    QLabel *created_at;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *hashtags;
    QPushButton *show_comment_button;
    QPushButton *show_favorites_button;
    QPushButton *liked_button;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PostWindow)
    {
        if (PostWindow->objectName().isEmpty())
            PostWindow->setObjectName(QString::fromUtf8("PostWindow"));
        PostWindow->resize(800, 600);
        centralwidget = new QWidget(PostWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        photo = new QLabel(centralwidget);
        photo->setObjectName(QString::fromUtf8("photo"));
        photo->setGeometry(QRect(190, 30, 321, 241));
        title = new QLabel(centralwidget);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(330, 10, 67, 17));
        username = new QLabel(centralwidget);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(300, 280, 91, 17));
        created_at = new QLabel(centralwidget);
        created_at->setObjectName(QString::fromUtf8("created_at"));
        created_at->setGeometry(QRect(310, 300, 67, 17));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 340, 751, 31));
        hashtags = new QHBoxLayout(horizontalLayoutWidget);
        hashtags->setObjectName(QString::fromUtf8("hashtags"));
        hashtags->setContentsMargins(0, 0, 0, 0);
        show_comment_button = new QPushButton(centralwidget);
        show_comment_button->setObjectName(QString::fromUtf8("show_comment_button"));
        show_comment_button->setGeometry(QRect(230, 480, 121, 41));
        show_favorites_button = new QPushButton(centralwidget);
        show_favorites_button->setObjectName(QString::fromUtf8("show_favorites_button"));
        show_favorites_button->setGeometry(QRect(380, 480, 121, 41));
        liked_button = new QPushButton(centralwidget);
        liked_button->setObjectName(QString::fromUtf8("liked_button"));
        liked_button->setGeometry(QRect(310, 410, 99, 27));
        PostWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PostWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        PostWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(PostWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        PostWindow->setStatusBar(statusbar);

        retranslateUi(PostWindow);

        QMetaObject::connectSlotsByName(PostWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PostWindow)
    {
        PostWindow->setWindowTitle(QApplication::translate("PostWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        photo->setText(QApplication::translate("PostWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        title->setText(QApplication::translate("PostWindow", "Title", 0, QApplication::UnicodeUTF8));
        username->setText(QApplication::translate("PostWindow", "@username", 0, QApplication::UnicodeUTF8));
        created_at->setText(QApplication::translate("PostWindow", "created_at", 0, QApplication::UnicodeUTF8));
        show_comment_button->setText(QApplication::translate("PostWindow", "Comments", 0, QApplication::UnicodeUTF8));
        show_favorites_button->setText(QApplication::translate("PostWindow", "Favorites", 0, QApplication::UnicodeUTF8));
        liked_button->setText(QApplication::translate("PostWindow", "Like", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PostWindow: public Ui_PostWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSTWINDOW_H
