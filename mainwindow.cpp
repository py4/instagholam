#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <iostream>
#include <QFileDialog>
#include <qpixmap.h>
#include <QVBoxLayout>
#include "clickableimage.h"
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
        api.login(username,password);
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
    QPixmap * mypix = new QPixmap(QString::fromStdString(api.get_avatar_path()));
    ui->avatar->setPixmap(*mypix);
    ui->stackedWidget->setCurrentWidget(ui->home_page);
    ui->tabWidget->setCurrentWidget(ui->tab);
    //ui->name_under_avatar->setText(QString::fromStdString(api.get_username()));
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
    if ( ui->gridLayout != NULL )
    {
        QLayoutItem* item;
        while ( ( item = ui->gridLayout->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
        delete ui->gridLayout;
    }
    //delete ui->gridLayout;
    ui->gridLayout = new QGridLayout(ui->profile_tab);
    vector <int> posts = api.get_my_latest_posts();
    try {
    cout << "post size:  " << posts.size() << endl;
    /*for(int i = 0; i < posts.size(); i++)
    {
        XML* xml = api.get_post(posts[i]);
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
    vector <string> users = api.get_users();
    for(int i = 0; i < users.size(); i++)
    {
        string avatar = api.get_user_avatar(users[i]);
        QHBoxLayout* layout = new QHBoxLayout;
        QPixmap * pic = new QPixmap(QString::fromStdString(avatar));
        QPixmap* mypix = new QPixmap(pic->scaled(QSize(100,100),  Qt::KeepAspectRatio));
        QLabel* photo = new QLabel;
        photo->setPixmap(*mypix);
        layout->addWidget(photo);
        QLabel* username = new QLabel(QString::fromStdString(users[i]));
        layout->addWidget(username);
        if(!api.is_friend_with(users[i]))
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
        api.sign_up(username, password, full_name, file_path);
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
        api.post_photo(title,file,hashtags,publicity);
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
