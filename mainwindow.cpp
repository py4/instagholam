#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <iostream>
#include <QFileDialog>
#include <qpixmap.h>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegExp rx("[a-zA-Z0-9_]+");
    ui->username->setValidator(new QRegExpValidator(rx, this ));
    ui->password->setEchoMode(QLineEdit::Password);
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
