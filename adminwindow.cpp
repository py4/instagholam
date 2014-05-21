#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "api.h"
#include "requestbutton.h"
adminwindow::adminwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminwindow)
{
    ui->setupUi(this);
    vector <string> users = Api::instance()->get_users();

    ui->admin_users_table->setRowCount(users.size());
    ui->admin_users_table->setColumnCount(3);
    ui->admin_users_table->resizeColumnsToContents();
    ui->admin_users_table->resizeRowsToContents();
    ui->admin_users_table->horizontalHeader()->hide();
    ui->admin_users_table->verticalHeader()->hide();
    ui->admin_users_table->resize(800,420);
    ui->admin_users_table->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->admin_users_table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->admin_users_table->setShowGrid(false);
    ui->admin_users_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->admin_users_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->admin_users_table->setSelectionMode(QAbstractItemView::NoSelection);
    ui->admin_users_table->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    for(int i = 0; i < users.size(); i++)
    {

        QPixmap * pic = new QPixmap(QString::fromStdString(Api::instance()->get_user_avatar(users[i])));
        QPixmap* mypix = new QPixmap(pic->scaled(QSize(100,100),  Qt::KeepAspectRatio));
        QLabel* avatar = new QLabel;
        avatar->setPixmap(*mypix);

        ui->admin_users_table->setItem(i,0,new QTableWidgetItem(""));
        ui->admin_users_table->setCellWidget(i,0,avatar);

        ui->admin_users_table->setItem(i,1,new QTableWidgetItem(QString::fromStdString(users[i])));

        QPushButton* remove = new RequestButton(users[i]);
        remove->setText("remove");
        connect(remove,SIGNAL(clicked()), this, SLOT(remove_user()));

        ui->admin_users_table->setCellWidget(i,2,remove);
    }
}

void adminwindow::remove_user()
{
    RequestButton* b = dynamic_cast<RequestButton*>(sender());
    Api::instance()->remove_user(b->username);
    int rows = ui->admin_users_table->currentIndex().row();
    ui->admin_users_table->removeRow(rows);
}

adminwindow::~adminwindow()
{
    delete ui;
}

void adminwindow::on_register_button_clicked()
{
    string full_name = ui->register_full_name->text().toStdString();
        string username = ui->register_username->text().toStdString();
        string password = ui->register_password->text().toStdString();
        string file_path = ui->avatar_file->text().toStdString();
        try {
            Api::instance()->register_user(username, password, full_name, file_path);
            ui->statusbar->showMessage(QString::fromStdString("Successfully registed!"));
        } catch (Exception e)
        {
            ui->statusbar->showMessage(QString::fromStdString(e.message));
        }
}
