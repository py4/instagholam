#include "postwindow.h"
#include "ui_postwindow.h"
#include <iostream>
#include "commentswindow.h"
#include "api.h"
using namespace std;
PostWindow::PostWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PostWindow)
{
    ui->setupUi(this);
}

PostWindow::PostWindow(int id, string title, string url, string username, string created_at,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PostWindow)
{
    ui->setupUi(this);
    this->id = id;
    this->title = title;
    ui->title->setText(QString::fromStdString(title));
    this->url = url;
    QPixmap * mypix = new QPixmap(QString::fromStdString(url));
    ui->photo->setPixmap(*mypix);
    this->username = username;
    QString user = "<font color='red'>@</font>";
    user.append(QString::fromStdString(username));
    ui->username->setText(user);
    this->created_at = created_at;
    ui->created_at->setText(QString::fromStdString(created_at));
}

PostWindow::~PostWindow()
{
    delete ui;
}

void PostWindow::set_hashtags(vector<string>& hashtags)
{
    for(int i = 0; i < hashtags.size(); i++)
    {
        QLabel* tag = new QLabel(QString::fromStdString('#'+hashtags[i]));
        ui->hashtags->addWidget(tag);
    }
}

void PostWindow::show_comments()
{
    vector<int> comment_ids = Api::instance()->get_post_comments(id);
    commentswindow* comments_window = new commentswindow(id, title, url);
    for(int i = 0; i < comment_ids.size(); i++)
    {
        map<string,string> comment_info = Api::instance()->get_comment(id, comment_ids[i]);
        comments_window->add_comment(comment_info["username"], comment_info["content"]);
    }
    comments_window->show();
}

void PostWindow::on_show_comment_button_clicked()
{
    show_comments();
}
