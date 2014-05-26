#include "profile_table.h"
#include <QHeaderView>
#include <QPixmap>
#include <QString>
#include <QTableWidgetItem>
#include "postwindow.h"
#include "clickableimage.h"
#include <iostream>
#include <vector>
using namespace std;

ProfileTable::ProfileTable(QWidget *parent) : QTableWidget(parent)
{
}

ProfileTable::ProfileTable(int row,int column, QWidget *parent ) : QTableWidget(parent)
{
	setRowCount(row);
    setColumnCount(column);
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

void ProfileTable::add_posts(vector<int>& posts)
{
    for(int i = 0; i < posts.size(); i++)
    {
            if(i >= posts.size())
                break;
            map<string,string> post_info = Core::instance()->get_post_info(posts[i]);
    string title = post_info["title"];
    string url = post_info["photo_path"];
    string created_at = post_info["created_at"];

    QPixmap * pic = new QPixmap(QString::fromStdString(url));
    QPixmap* mypix = new QPixmap(pic->scaled(QSize(200,200),  Qt::KeepAspectRatio));
    ClickableImage* photo = new ClickableImage(posts[i]);
    photo->setPixmap(*mypix);

    connect(photo,SIGNAL(leftButtonPressed(ClickableImage*)), this, SLOT(show_post()));

    setItem(i / 3,i % 3,new QTableWidgetItem(""));
    setCellWidget(i / 3,i % 3,photo);
    }
}

void ProfileTable::show_post()
{
    cout << "show_post" << endl;
    ClickableImage* p = dynamic_cast<ClickableImage*>(sender());
    int post_id = p->id;
    map<string,string> info = Core::instance()->get_post_info(post_id);
    PostWindow* post_window = new PostWindow(post_id,info["title"],info["photo_path"],info["username"],info["created_at"]);
    vector<string> hashtags = Core::instance()->get_post_hashtags(post_id);
    post_window->set_hashtags(hashtags);

    post_window->show();
}
