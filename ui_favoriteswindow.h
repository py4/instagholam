/********************************************************************************
** Form generated from reading UI file 'favoriteswindow.ui'
**
** Created: Wed May 21 16:37:51 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAVORITESWINDOW_H
#define UI_FAVORITESWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_favoriteswindow
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *favorites_layout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *favoriteswindow)
    {
        if (favoriteswindow->objectName().isEmpty())
            favoriteswindow->setObjectName(QString::fromUtf8("favoriteswindow"));
        favoriteswindow->resize(300, 500);
        centralwidget = new QWidget(favoriteswindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 301, 451));
        favorites_layout = new QHBoxLayout(horizontalLayoutWidget);
        favorites_layout->setObjectName(QString::fromUtf8("favorites_layout"));
        favorites_layout->setContentsMargins(0, 0, 0, 0);
        favoriteswindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(favoriteswindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 300, 25));
        favoriteswindow->setMenuBar(menubar);
        statusbar = new QStatusBar(favoriteswindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        favoriteswindow->setStatusBar(statusbar);

        retranslateUi(favoriteswindow);

        QMetaObject::connectSlotsByName(favoriteswindow);
    } // setupUi

    void retranslateUi(QMainWindow *favoriteswindow)
    {
        favoriteswindow->setWindowTitle(QApplication::translate("favoriteswindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class favoriteswindow: public Ui_favoriteswindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAVORITESWINDOW_H
