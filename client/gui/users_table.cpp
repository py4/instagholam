#include "users_table.h"
#include "core.h"
#include <QPixmap>
#include "requestbutton.h"
#include <QLabel>
#include "fellowwindow.h"
#include <QHBoxLayout>
#include <iostream>
#include <QHeaderView>
using namespace std;
UsersTable::UsersTable(QWidget *parent) : QTableWidget(parent)
{

}

UsersTable::UsersTable(vector <string> & users, QWidget *parent) : QTableWidget(parent)
{
    setRowCount(users.size());
    setColumnCount(3);
    resizeColumnsToContents();
    resizeRowsToContents();
    horizontalHeader()->hide();
    verticalHeader()->hide();
    resize(800,420);
    verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    setShowGrid(false);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::NoSelection);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

void UsersTable::add_users(vector<string>& users)
{
    for(int i = 0; i < users.size(); i++)
    {
        //QHBoxLayout* layout = new QHBoxLayout;
        QPixmap * pic = new QPixmap(QString::fromStdString(Core::instance()->get_user_avatar(users[i])));
        QPixmap* mypix = new QPixmap(pic->scaled(QSize(100,100),  Qt::KeepAspectRatio));
        QLabel* avatar = new QLabel;
        avatar->setPixmap(*mypix);

        setItem(i,0,new QTableWidgetItem(""));
        setCellWidget(i,0,avatar);

        QLabel* username = new QLabel(QString::fromStdString(users[i]));
        setItem(i,1,new QTableWidgetItem(QString::fromStdString(users[i])));
        cout << "added " << users[i] << endl;
        //layout->addWidget(avatar);
        //layout->addWidget(username);
        if(users[i] != Core::instance()->get_username())
        {
            QPushButton* view = new RequestButton(users[i]);
            view->setText("View Profile");
            //layout->addWidget(view);
            setItem(i,2,new QTableWidgetItem(""));
            setCellWidget(i,2,view);
            connect(view, SIGNAL(clicked()), this, SLOT(view_user()));
        }
        //cout << "adding to layout..." << endl;
        //this->addLayout(layout);
    }
}

void UsersTable::view_user()
{
	RequestButton* b = dynamic_cast<RequestButton*>(sender());
    string username = b->username;
    cout << "username:  " << username << endl;
    fellowwindow* window = new fellowwindow(username);
    window->show();
}
