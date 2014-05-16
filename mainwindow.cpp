#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <iostream>
#include <QFileDialog>
#include <qpixmap.h>
#include <QVBoxLayout>
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
    vector <int> posts = api.get_my_latest_posts();
    try {
    int j = 0;
    ui->profile_post_layout->setContentsMargins(0,0,0,0);
    for(int i = 0; i < posts.size(); i++)
    {
        XML* xml = api.get_post(posts[i]);
        xml->dump();
        string url = (*xml)["photo_path"]->get_value();
        string title = (*xml)["title"]->get_value();

        QPixmap * pic = new QPixmap(QString::fromStdString(url));
        QPixmap* mypix = new QPixmap(pic->scaled(QSize(50,50),  Qt::KeepAspectRatio));
        QLabel* photo = new QLabel;
        photo->setPixmap(*mypix);
        QLabel* label = new QLabel(QString::fromStdString(title));
        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(photo);
        layout->addWidget(label);
        layout->setContentsMargins(0,0,0,0);
        ui->profile_post_layout->addLayout(layout,j,i);
        if(i % 4 == 0)
            j++;
        delete xml;
        cout << url;
    }
    } catch (Exception e) {
        set_status(e.message);
    }

    ui->tabWidget->setCurrentWidget(ui->profile_tab);
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
}
