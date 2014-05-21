#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <iostream>
#include <QFileDialog>
#include <qpixmap.h>
#include <QVBoxLayout>
#include <QTableWidget>
#include "clickableimage.h"
#include "postwindow.h"
#include "profile_table.h"
#include "users_table.h"
#include <QLayoutItem>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegExp rx("[a-zA-Z0-9_]+");
    ui->username->setValidator(new QRegExpValidator(rx, this ));
    ui->password->setEchoMode(QLineEdit::Password);
    ui->share_file_name->setReadOnly(true);
    ui->avatar_file->setReadOnly(true);
    render_login();

    refresh["home_tab"] = true;
    refresh["share_tab"] = true;
    refresh["profile_tab"] = true;
    refresh["friends_tab"] = true;
    refresh["requests_tab"] = true;
    refresh["people_tab"] = true;
    refresh["explore_tab"] = true;


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sign_in_clicked()
{
    string username = ui->username->text().toStdString();
    string password = ui->password->text().toStdString();
    try {
        Api::instance()->login(username,password);
        render_home();
        QMenu* menu = new QMenu("Actions");
        QAction* logout_action = new QAction("logout",menu);
        menu->addAction(logout_action);
        connect(logout_action,SIGNAL(triggered()),this,SLOT(on_actionLogout_triggered()));
        ui->menubar->addMenu(menu);
    } catch (Exception e)
    {
        set_status(e.message);
    }
}

void MainWindow::set_status(string status)
{
    statusBar()->showMessage(QString::fromStdString(status));
}

void MainWindow::render_login()
{
    ui->stackedWidget->setCurrentWidget(ui->login_form);
}

void MainWindow::render_signup()
{
    QRegExp rx("[a-zA-Z0-9_]+");
    ui->register_username->setValidator(new QRegExpValidator(rx, this ));
    ui->register_password->setEchoMode(QLineEdit::Password);
    ui->stackedWidget->setCurrentWidget(ui->register_form);
    ui->register_full_name->clear();
    ui->register_username->clear();
    ui->register_password->clear();
    ui->avatar_file->clear();
}

void MainWindow::render_home()
{
    QPixmap * mypix = new QPixmap(QString::fromStdString(Api::instance()->get_avatar_path()));
    ui->avatar->setPixmap(*mypix);
    ui->stackedWidget->setCurrentWidget(ui->home_page);
    ui->tabWidget->setCurrentWidget(ui->home_tab);
    refresh["home_tab"] = false;
    //ui->name_under_avatar->setText(QString::fromStdString(Api::instance()->get_username()));
}

void MainWindow::render_share()
{
    ui->share_file_name->clear();
    ui->share_title->clear();
    ui->share_hashtags->clear();
    ui->tabWidget->setCurrentWidget(ui->share_tab);
}

void MainWindow::render_profile()
{
    delete ui->profile_table;
    vector <int> posts = Api::instance()->get_my_latest_posts();
    ui->profile_table = new ProfileTable(posts.size(), 3, ui->profile_tab);
    ui->profile_table->show();
    try {
        ProfileTable* p = dynamic_cast<ProfileTable*>(ui->profile_table);
        p->add_posts(posts);
    } catch (Exception e) {
        set_status(e.message);
    }
    ui->tabWidget->setCurrentWidget(ui->profile_tab);
    refresh["profile_tab"] = false;
}

void clearLayout(QLayout* layout)
{
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        //delete item;
    }
}

void MainWindow::render_people()
{
    vector <string> users = Api::instance()->get_users();
    //clearLayout(ui->people_tab->layout());
    QLayoutItem *child;
    //while ( (child = ui->people_tab->layout()->takeAt(0)) != 0) {
      //         delete child;
        //}
    //delete ui->people_tab->layout();
    //ui->people_tab->setLayout(new UsersLayout(users));
    //delete ui->people_table;

    ui->people_table = new UsersTable(users,ui->people_tab);
    ui->people_table->show();
    UsersTable* p = dynamic_cast<UsersTable*>(ui->people_table);
    cout << "p:  " << p << endl;
    p->add_users(users);
    //ui->people_table = new QTableWidget()
    /*for(int i = 0; i < users.size(); i++)
    {
        string avatar = Api::instance()->get_user_avatar(users[i]);
        QHBoxLayout* layout = new QHBoxLayout;
        QPixmap * pic = new QPixmap(QString::fromStdString(avatar));
        QPixmap* mypix = new QPixmap(pic->scaled(QSize(100,100),  Qt::KeepAspectRatio));
        QLabel* photo = new QLabel;
        photo->setPixmap(*mypix);
        layout->addWidget(photo);
        QLabel* username = new QLabel(QString::fromStdString(users[i]));
        layout->addWidget(username);
        if(!Api::instance()->is_friend_with(users[i]))
        {
            QPushButton* request = new QPushButton(QString::fromStdString("Request"));
            layout->addWidget(request);
        }
        ui->people_layout->addLayout(layout);
    }*/
    refresh["people_tab"] = false;
}

void MainWindow::on_select_avatar_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this);
    ui->avatar_file->setText(file_name);
}

void MainWindow::on_register_button_clicked()
{
    string full_name = ui->register_full_name->text().toStdString();
    string username = ui->register_username->text().toStdString();
    string password = ui->register_password->text().toStdString();
    string file_path = ui->avatar_file->text().toStdString();
    try {
        Api::instance()->sign_up(username, password, full_name, file_path);
        set_status("Successfully registed!");
        QMenu* menu = new QMenu("Actions");
        QAction* logout_action = new QAction("logout",menu);
        menu->addAction(logout_action);
        connect(logout_action,SIGNAL(triggered()),this,SLOT(on_actionLogout_triggered()));
        ui->menubar->addMenu(menu);
        render_home();
    } catch (Exception e)
    {
        set_status(e.message);
    }
}


void MainWindow::on_register_2_clicked()
{
    render_signup();
}

void MainWindow::on_share_button_clicked()
{
    string title = ui->share_title->text().toStdString();
    string file = ui->share_file_name->text().toStdString();
    bool publicity = ui->share_pub_checkbox->isChecked();
    string hashtags = ui->share_hashtags->text().toStdString();
    try {
        Api::instance()->post_photo(title,file,hashtags,publicity);
        set_status("Successfully posted!");
        render_share();
    } catch (Exception e) {
        set_status(e.message);
    }
}

void MainWindow::on_share_select_file_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this);
    ui->share_file_name->setText(file_name);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 2)
    {
        if(refresh["profile_tab"])
        {
            cout << "refreshing profile tab" << endl;
            render_profile();
        }
        refresh["profile_tab"] = true;
    }
    if(index == 3)
    {
        if(refresh["friends_tab"])
        {
            cout << "refreshing friends tab" << endl;
            render_friends();
        }
        refresh["friends_tab"] = true;
    }
    if(index == 5)
    {
        if(refresh["people_tab"])
        {
            cout << "refreshing people tab" << endl;
            render_people();
        }
        refresh["people_tab"] = true;
    }
}

void MainWindow::show_clicked_post()
{
    cout << "fuck that!!!" << endl;
}

void MainWindow::show_post()
{
    cout << "show_post" << endl;
    ClickableImage* p = dynamic_cast<ClickableImage*>(sender());
    int post_id = p->id;
    map<string,string> info = Api::instance()->get_post_info(post_id);
    PostWindow* post_window = new PostWindow(post_id,info["title"],info["photo_path"],info["username"],info["created_at"]);
    vector<string> hashtags = Api::instance()->get_post_hashtags(post_id);
    post_window->set_hashtags(hashtags);

    post_window->show();
}

void MainWindow::render_friends()
{
    vector<string> users = Api::instance()->get_friends();
    //delete ui->friends_tab->layout();
    //ui->friends_tab->setLayout(new UsersLayout(users));
    delete ui->friends_table;
    ui->friends_table = new UsersTable(users);
    refresh["friends_tab"] = false;
}

void MainWindow::on_actionLogout_triggered()
{
    refresh["home_tab"] = true;
    refresh["share_tab"] = true;
    refresh["profile_tab"] = true;
    refresh["friends_tab"] = true;
    refresh["requests_tab"] = true;
    refresh["people_tab"] = true;
    refresh["explore_tab"] = true;
    Api::instance()->logout();
    render_login();
}
