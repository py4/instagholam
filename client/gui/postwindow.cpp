#include "postwindow.h"
#include "ui_postwindow.h"
#include <iostream>
#include "commentswindow.h"
#include "core.h"
#include "favoriteswindow.h"
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
    vector<int> comment_ids = Core::instance()->get_post_comments(id);
    commentswindow* comments_window = new commentswindow(id, title, url);
    for(int i = 0; i < comment_ids.size(); i++)
    {
        map<string,string> comment_info = Core::instance()->get_comment(id, comment_ids[i]);
        comments_window->add_comment(comment_info["username"], comment_info["content"]);
    }
    comments_window->show();
}

void PostWindow::show_favorites()
{
    vector<string> usernames = Core::instance()->get_post_liked_by(id);
    favoriteswindow* favorites_window = new favoriteswindow(usernames);
    /*for(int i = 0; i < usernames.size(); i++)
    {
        string url = Core::instance()->get_user_avatar(usernames[i]);
        favorites_window->add_item(url,usernames[i]);
    }*/
    favorites_window->show();
}

void PostWindow::on_show_comment_button_clicked()
{
    show_comments();
}

void PostWindow::on_show_favorites_button_clicked()
{
    show_favorites();
}

void PostWindow::on_liked_button_clicked()
{
    if(Core::instance()->is_likable(id))
    {
        cout << ">>>>>> calling like <<<<<<<" << endl;
        Core::instance()->like(id);
        cout << ">>>>>> call finished <<<<<<<" << endl;
        ui->liked_button->setText("Unlike");
    }
    else
    {
        Core::instance()->unlike(id);
        ui->liked_button->setText("Like");
    }
}
