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
#include "requestbutton.h"
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
    cout << "main window freeing db" << endl;
    delete ui;
    DB::instance()->free_db();
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
    ui->username->clear();
    ui->password->clear();
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

    delete ui->home_table;
    vector<int> posts = Api::instance()->get_latest_posts();
    ui->home_table = new ProfileTable(posts.size(), 3, ui->home_tab);
    ui->home_table->show();
    try {
        ProfileTable* p = dynamic_cast<ProfileTable*>(ui->home_table);
        p->add_posts(posts);
    } catch (Exception e) {
        set_status(e.message);
    }
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
    QLayoutItem *child;
    ui->people_table = new UsersTable(users,ui->people_tab);
    ui->people_table->show();
    UsersTable* p = dynamic_cast<UsersTable*>(ui->people_table);
    p->add_users(users);
    refresh["people_tab"] = false;
}

void MainWindow::render_requests()
{
    map<int,string> requests = Api::instance()->get_received_requests();
    ui->requests_table->setRowCount(requests.size());
    ui->requests_table->setColumnCount(3);
    ui->requests_table->resizeColumnsToContents();
    ui->requests_table->resizeRowsToContents();
    ui->requests_table->horizontalHeader()->hide();
    ui->requests_table->verticalHeader()->hide();
    ui->requests_table->resize(800,420);
    ui->requests_table->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->requests_table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->requests_table->setShowGrid(false);
    ui->requests_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->requests_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->requests_table->setSelectionMode(QAbstractItemView::NoSelection);
    ui->requests_table->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    int i = 0;
    for(map<int,string>::iterator it = requests.begin(); it != requests.end(); it++,i++)
    {

        QPixmap * pic = new QPixmap(QString::fromStdString(Api::instance()->get_user_avatar(it->second)));
        QPixmap* mypix = new QPixmap(pic->scaled(QSize(100,100),  Qt::KeepAspectRatio));
        QLabel* avatar = new QLabel;
        avatar->setPixmap(*mypix);

        ui->requests_table->setItem(i,0,new QTableWidgetItem(""));
        ui->requests_table->setCellWidget(i,0,avatar);

        ui->requests_table->setItem(i,1,new QTableWidgetItem(QString::fromStdString(it->second)));

        QPushButton* approve = new RequestButton(it->first);
        approve->setText("Approve");
        connect(approve,SIGNAL(clicked()), this, SLOT(approve_request()));

        QPushButton* disapprove = new RequestButton(it->first);
        disapprove->setText("Disapprove");
        connect(disapprove,SIGNAL(clicked()),this, SLOT(disapprove_request()));

        ui->requests_table->setCellWidget(i,2,approve);
        ui->requests_table->setCellWidget(i,3,disapprove);

        cout << "id:  " << it->first << endl;
        cout << "from:  " << it->second << endl;
    }
}

void MainWindow::approve_request()
{
    try {
        RequestButton* b = dynamic_cast<RequestButton*>(sender());
        Api::instance()->approve_friend_request(b->id);
        int rows = ui->requests_table->currentIndex().row();
        ui->requests_table->removeRow(rows);
    } catch (Exception e) {
        set_status(e.message);
    }
}

void MainWindow::disapprove_request()
{
    try {
        RequestButton* b = dynamic_cast<RequestButton*>(sender());
        Api::instance()->disapprove_friend_request(b->id);
        int rows = ui->requests_table->currentIndex().row();
        ui->requests_table->removeRow(rows);
    } catch (Exception e) {
        set_status(e.message);
    }
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
            refresh["profile_tab"] = false;
        }
    }
    if(index == 3)
    {
        if(refresh["friends_tab"])
        {
            cout << "refreshing friends tab" << endl;
            render_friends();
            refresh["friends_tab"] = false;
        }
    }
    if(index == 5)
    {
        if(refresh["people_tab"])
        {
            cout << "refreshing people tab" << endl;
            render_people();
            refresh["people_tab"] = false;
        }
    }
    if(index == 4)
    {
        if(refresh["requests_tab"])
        {
            cout << "refreshing requests tab" << endl;
            render_requests();
            refresh["requests_tab"] = false;
        }
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
    delete ui->friends_table;
    ui->friends_table = new UsersTable(users,ui->friends_tab);
    ui->friends_table->show();
    UsersTable* p = dynamic_cast<UsersTable*>(ui->friends_table);
    p->add_users(users);
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
    ui->menubar->clear();
}

void MainWindow::on_refresh_button_clicked()
{
    refresh["home_tab"] = true;
    refresh["share_tab"] = true;
    refresh["profile_tab"] = true;
    refresh["friends_tab"] = true;
    refresh["requests_tab"] = true;
    refresh["people_tab"] = true;
    refresh["explore_tab"] = true;
    render_home();
}
