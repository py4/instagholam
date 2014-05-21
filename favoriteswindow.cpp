#include "favoriteswindow.h"
#include "ui_favoriteswindow.h"
#include "requestbutton.h"
#include <QHBoxLayout>
#include <QLabel>
using namespace std;

favoriteswindow::favoriteswindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::favoriteswindow)
{
    ui->setupUi(this);
}

void favoriteswindow::add_item(string url, string username)
{
    QPixmap * pic = new QPixmap(QString::fromStdString(url));
    QPixmap* mypix = new QPixmap(pic->scaled(QSize(100,100),  Qt::KeepAspectRatio));
    QLabel* photo = new QLabel;
    photo->setPixmap(*mypix);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(photo);

    QLabel* name = new QLabel(QString::fromStdString(username));
    RequestButton* button = new RequestButton(username);

    layout->addWidget(name);
    layout->addWidget(button);

    ui->favorites_layout->addLayout(layout);
}

favoriteswindow::~favoriteswindow()
{
    delete ui;
}
