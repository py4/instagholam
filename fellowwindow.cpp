#include "fellowwindow.h"
#include "ui_fellowwindow.h"
#include "profile_table.h"
#include "api.h"
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
    if(Api::instance()->is_friend_with(username))
        ui->label->setText(QString::fromStdString("You are friend with him"));
    else if(Api::instance()->has_requested_to(username))
        ui->label->setText(QString::fromStdString("You've sent a request to him"));
    else if(Api::instance()->has_requested_to(username))
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
        if(Api::instance()->is_friend_with(username))
            posts = Api::instance()->get_friend_latest_posts(username);
        else
            posts = Api::instance()->get_user_public_posts(username);
     delete ui->profile_table;
     ui->profile_table = new ProfileTable(posts.size(), 3, ui->profile_tab);
     ProfileTable* p = dynamic_cast<ProfileTable*>(ui->profile_table);
     p->add_posts(posts);
 } catch (Exception e) {
        //set_status(e.message);
 }
    //ui->tabWidget->setCurrentWidget(ui->profile_tab);
}

void fellowwindow::approve_request()
{
    Api::instance()->approve_friend_request(username);
    ui->pushButton->hide();
    ui->pushButton2->hide();
}

void fellowwindow::disapprove_request()
{
    Api::instance()->disapprove_friend_request(username);
    ui->pushButton->hide();
    ui->pushButton2->hide();
}

void fellowwindow::request_to_friend()
{
    Api::instance()->request_to_friend(username);
    ui->pushButton->hide();
    ui->pushButton2->hide();
    ui->label->setText(QString::fromStdString("You've sent a request to him"));
    ui->label->show();
}

fellowwindow::~fellowwindow()
{
    delete ui;
}
