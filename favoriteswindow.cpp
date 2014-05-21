#include "favoriteswindow.h"
#include "ui_favoriteswindow.h"
#include "requestbutton.h"
#include <QHBoxLayout>
#include <QLabel>
#include "api.h"
#include "fellowwindow.h"
#include "users_table.h"
using namespace std;

favoriteswindow::favoriteswindow(vector<string>& usernames, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::favoriteswindow)
{
    ui->setupUi(this);
     QWidget *window = new QWidget();
     ui->favorited_by_table = new UsersTable(usernames);
     //window->setLayout(new UsersLayout(usernames));
     //setCentralWidget(window);
}

void favoriteswindow::add_item(string url, string username)
{
    /*QPixmap * pic = new QPixmap(QString::fromStdString(url));
    QPixmap* mypix = new QPixmap(pic->scaled(QSize(100,100),  Qt::KeepAspectRatio));
    QLabel* photo = new QLabel;
    photo->setPixmap(*mypix);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(photo);

    QLabel* name = new QLabel(QString::fromStdString(username));

    if(username != Api::instance()->get_username())
    {
        RequestButton* button = new RequestButton(username);
        button->setText("View Profile");
        layout->addWidget(button);
        connect(button, SIGNAL(clicked()), this, SLOT(view_friend()));
    }
    layout->addWidget(name);
    ui->favorites_layout->addLayout(layout);*/
}

favoriteswindow::~favoriteswindow()
{
    delete ui;
}

void favoriteswindow::view_friend()
{
    RequestButton* b = dynamic_cast<RequestButton*>(sender());
    string username = b->username;
    fellowwindow* window = new fellowwindow(username);
    window->show();
}
