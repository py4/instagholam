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
}

void MainWindow::render_home()
{
    QPixmap * mypix = new QPixmap(QString::fromStdString(Api::instance()->get_avatar_path()));
    ui->avatar->setPixmap(*mypix);
    ui->stackedWidget->setCurrentWidget(ui->home_page);
    ui->tabWidget->setCurrentWidget(ui->tab);
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
    //ui->profile_table->clearContents();
    //ui->profile_table->clear();

    /*if ( ui->gridLayout != NULL )
    {
        QLayoutItem* item;
        while ( ( item = ui->gridLayout->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
        delete ui->gridLayout;
    }*/
    /*if (ui->profile_layout != NULL )
        {
            QLayoutItem* item;
            while ( ( item = ui->profile_layout->takeAt( 0 ) ) != NULL )
            {
                delete item->widget();
                delete item;
            }
            delete ui->profile_layout;
        }*/
    //delete ui->gridLayout;
    //ui->profile_layout = new QVBoxLayout(ui->profile_tab);
    delete ui->profile_table;
    ui->profile_table = new QTableWidget(ui->profile_tab);
    ui->profile_table->show();
    vector <int> posts = Api::instance()->get_my_latest_posts();
    try {
    cout << "post size:  " << posts.size() << endl;
    ui->profile_table->setRowCount(posts.size());
    ui->profile_table->setColumnCount(3);
    QStringList m_TableHeader;
    //m_TableHeader<<"Pic"<<"Title"<<"Created_at" << "Action";
    //ui->profile_table->setHorizontalHeaderLabels(m_TableHeader);
    ui->profile_table->resizeColumnsToContents();
    ui->profile_table->resizeRowsToContents();
    //ui->profile_table->horizontalHeader()->setStretchLastSection(true);
    ui->profile_table->horizontalHeader()->hide();
    ui->profile_table->verticalHeader()->hide();
    ui->profile_table->resize(800,420);
    //ui->profile_table->resizeRowsToContents();
    //ui->profile_table->verticalHeader()->hide();
    cout << "setting header resize mode..." << endl;
    ui->profile_table->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    //ui->profile_table->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->profile_table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->profile_table->setShowGrid(false);
    ui->profile_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->profile_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->profile_table->setSelectionBehavior(QAbstractItemView::NoSelection);
    ui->profile_table->setSelectionMode(QAbstractItemView::NoSelection);
    ui->profile_table->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    for(int i = 0; i < posts.size(); i++)
    {
        //for(int j = 0; j < 3; i++ and j++)
        //{
            if(i >= posts.size())
                break;

        map<string,string> post_info = Api::instance()->get_post_info(posts[i]);
        string title = post_info["title"];
        string url = post_info["photo_path"];
        string created_at = post_info["created_at"];

        QPixmap * pic = new QPixmap(QString::fromStdString(url));
        QPixmap* mypix = new QPixmap(pic->scaled(QSize(200,200),  Qt::KeepAspectRatio));
        //QLabel* photo = new QLabel;
        //photo->setPixmap(*mypix);
        ClickableImage* photo = new ClickableImage(posts[i]);
        photo->setPixmap(*mypix);

        connect(photo,SIGNAL(leftButtonPressed(ClickableImage*)), this, SLOT(show_post()));


        QPushButton* view = new QPushButton(QString::fromStdString("View"));
        view->setFixedSize(50,50);

        ui->profile_table->setItem(i / 3,i % 3,new QTableWidgetItem(""));
        //ui->profile_table->setItem(i,1,new QTableWidgetItem(QString::fromStdString(title)));
        //ui->profile_table->setItem(i,2,new QTableWidgetItem(QString::fromStdString(created_at)));
        //ui->profile_table->setItem(i,3,new QTableWidgetItem(""));

        ui->profile_table->setCellWidget(i / 3,i % 3,photo);
        //}
        //ui->profile_table->setCellWidget(i,3,view);
    }
    /*for(int i = 0 ; i < posts.size(); i++)
    {
        map<string,string> post_info = Api::instance()->get_post_info(posts[i]);
        string title = post_info["title"];
        string url = post_info["photo_path"];
        string created_at = post_info["created_at"];

        QHBoxLayout* layout = new QHBoxLayout;

        QPixmap * pic = new QPixmap(QString::fromStdString(url));
        QPixmap* mypix = new QPixmap(pic->scaled(QSize(100,100),  Qt::KeepAspectRatio));
        QLabel* photo = new QLabel;
        photo->setPixmap(*mypix);

        layout->addWidget(photo);
        QLabel* l_title = new QLabel(QString::fromStdString(title));
        layout->addWidget(l_title);
        QLabel* l_created_at = new QLabel(QString::fromStdString(created_at));
        layout->addWidget(l_created_at);

        QPushButton* show = new QPushButton(QString::fromStdString("Show"));
        layout->addWidget(show);

        ui->profile_layout->addLayout(layout);
        //ui->profile_layout->addWidget(layout);
    }*/
    /*for(int i = 0; i < posts.size(); i++)
    {
        XML* xml = Api::instance()->get_post(posts[i]);
        xml->dump();
        string url = (*xml)["photo_path"]->get_value();
        string title = (*xml)["title"]->get_value();

        QPixmap * pic = new QPixmap(QString::fromStdString(url));
        QPixmap* mypix = new QPixmap(pic->scaled(QSize(100,100),  Qt::KeepAspectRatio));
        ClickableImage* photo = new ClickableImage(posts[i]);
        photo->setPixmap(*mypix);
        //connect(photo,SIGNAL(mousePressEvent()),this,SLOT(show_clicked_post()));
        //photo->property("id").va
        //photo->property("id").valu
        ui->gridLayout->addWidget(photo,i / 4, i % 4);
        delete xml;
    }*/
    } catch (Exception e) {
        set_status(e.message);
    }
    ui->tabWidget->setCurrentWidget(ui->profile_tab);
}

void MainWindow::render_people()
{
    vector <string> users = Api::instance()->get_users();
    for(int i = 0; i < users.size(); i++)
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
        render_profile();
    if(index == 5)
        render_people();
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
