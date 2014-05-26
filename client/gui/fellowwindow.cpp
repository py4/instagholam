#include "fellowwindow.h"
#include "ui_fellowwindow.h"
#include "profile_table.h"
#include "core.h"
#include "users_table.h"
#include "exception.h"
using namespace std;
fellowwindow::fellowwindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::fellowwindow)
{
    ui->setupUi(this);
}

fellowwindow::fellowwindow(string username, QWidget *parent) :
QMainWindow(parent),
ui(new Ui::fellowwindow)
{
    ui->setupUi(this);
    this->username = username;
    //ui->profile_table->show();
    ui->pushButton->hide();
    ui->pushButton2->hide();
    if(Core::instance()->is_friend_with(username))
        ui->label->setText(QString::fromStdString("You are friend with him"));
    else if(Core::instance()->has_requested_to(username))
        ui->label->setText(QString::fromStdString("You've sent a request to him"));
    else if(Core::instance()->has_requested_to_me(username))
    {
        ui->label->setText(QString::fromStdString("He's sent a request to you"));
        connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(approve_request()));
        connect(ui->pushButton2, SIGNAL(clicked()), this, SLOT(disapprove_request()));
        ui->pushButton->setText("Approve");
        ui->pushButton2->setText("Disapprove");
    }
    else
    {
        ui->label->hide();
        ui->pushButton->show();
        ui->pushButton->setText("Request to friend");
        connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(request_to_friend()));
    }
    
    try {
        vector <int> posts;
        if(Core::instance()->is_friend_with(username))
            posts = Core::instance()->get_friend_latest_posts(username);
        else
            posts = Core::instance()->get_user_public_posts(username);
        delete ui->profile_table;
        ui->profile_table = new ProfileTable(posts.size(), 3, ui->profile_tab);
        ProfileTable* p = dynamic_cast<ProfileTable*>(ui->profile_table);
        p->add_posts(posts);

        delete ui->fellow_friends_table;
        vector<string> users = Core::instance()->get_friend_friends(username);
        ui->fellow_friends_table = new UsersTable(users,ui->friends_tab);
        ui->fellow_friends_table->show();
        UsersTable* p2 = dynamic_cast<UsersTable*>(ui->fellow_friends_table);
        p2->add_users(users);
    } catch (Exception e) {
        ui->statusbar->showMessage(QString::fromStdString(e.message));
    }
}

void fellowwindow::approve_request()
{
    Core::instance()->approve_friend_request(username);
    ui->pushButton->hide();
    ui->pushButton2->hide();
}

void fellowwindow::disapprove_request()
{
    Core::instance()->disapprove_friend_request(username);
    ui->pushButton->hide();
    ui->pushButton2->hide();
}

void fellowwindow::request_to_friend()
{
    Core::instance()->request_to_friend(username);
    ui->pushButton->hide();
    ui->pushButton2->hide();
    ui->label->setText(QString::fromStdString("You've sent a request to him"));
    ui->label->show();
}

fellowwindow::~fellowwindow()
{
    delete ui;
}
