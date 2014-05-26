#include "commentswindow.h"
#include "ui_commentswindow.h"
#include <string>
#include <QHBoxLayout>
#include <QTextEdit>
#include "core.h"
#include <iostream>
using namespace std;
commentswindow::commentswindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::commentswindow)
{
    ui->setupUi(this);
}

commentswindow::commentswindow(int id, string title, string url, QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::commentswindow)
{
    ui->setupUi(this);
    ui->title->setText(QString::fromStdString(title));
    QPixmap * mypix = new QPixmap(QString::fromStdString(url));
    ui->photo->setPixmap(*mypix);
    this->id = id;
}

void commentswindow::add_comment(string by, string content)
{
    QHBoxLayout* layout = new QHBoxLayout;
    QLabel* username = new QLabel(QString::fromStdString(by));
    QTextEdit* comment = new QTextEdit;
    comment->setText(QString::fromStdString(content));
    comment->setEnabled(false);
    layout->addWidget(username);
    layout->addWidget(comment);
    ui->comments_layout->addLayout(layout);
}

commentswindow::~commentswindow()
{
    delete ui;
}

void commentswindow::on_submit_comment_clicked()
{
    string comment = ui->new_comment_content->toPlainText().toStdString();
    Core::instance()->add_comment(id,comment);
    add_comment(Core::instance()->get_username(), comment);
    cout << "added!" << endl;
}
