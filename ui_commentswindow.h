/********************************************************************************
** Form generated from reading UI file 'commentswindow.ui'
**
** Created: Wed May 21 02:16:23 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMENTSWINDOW_H
#define UI_COMMENTSWINDOW_H

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
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_commentswindow
{
public:
    QWidget *centralwidget;
    QLabel *photo;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *comments_layout;
    QLabel *title;
    QLabel *label;
    QTextEdit *new_comment_content;
    QPushButton *submit_comment;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *commentswindow)
    {
        if (commentswindow->objectName().isEmpty())
            commentswindow->setObjectName(QString::fromUtf8("commentswindow"));
        commentswindow->resize(740, 457);
        centralwidget = new QWidget(commentswindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        photo = new QLabel(centralwidget);
        photo->setObjectName(QString::fromUtf8("photo"));
        photo->setGeometry(QRect(0, 0, 171, 181));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(280, 10, 451, 391));
        comments_layout = new QVBoxLayout(verticalLayoutWidget);
        comments_layout->setObjectName(QString::fromUtf8("comments_layout"));
        comments_layout->setContentsMargins(0, 0, 0, 0);
        title = new QLabel(centralwidget);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(40, 180, 67, 17));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 250, 131, 17));
        new_comment_content = new QTextEdit(centralwidget);
        new_comment_content->setObjectName(QString::fromUtf8("new_comment_content"));
        new_comment_content->setGeometry(QRect(10, 270, 201, 78));
        submit_comment = new QPushButton(centralwidget);
        submit_comment->setObjectName(QString::fromUtf8("submit_comment"));
        submit_comment->setGeometry(QRect(40, 350, 99, 27));
        commentswindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(commentswindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 740, 25));
        commentswindow->setMenuBar(menubar);
        statusbar = new QStatusBar(commentswindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        commentswindow->setStatusBar(statusbar);

        retranslateUi(commentswindow);

        QMetaObject::connectSlotsByName(commentswindow);
    } // setupUi

    void retranslateUi(QMainWindow *commentswindow)
    {
        commentswindow->setWindowTitle(QApplication::translate("commentswindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        photo->setText(QApplication::translate("commentswindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        title->setText(QApplication::translate("commentswindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("commentswindow", "Leave a comment:", 0, QApplication::UnicodeUTF8));
        submit_comment->setText(QApplication::translate("commentswindow", "Submit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class commentswindow: public Ui_commentswindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMENTSWINDOW_H
