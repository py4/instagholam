#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "core.h"
#include <QString>
#include <string>
#include <map>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void on_sign_in_clicked();

    void on_select_avatar_clicked();

    void on_register_button_clicked();

    void on_register_2_clicked();

    void on_share_button_clicked();

    void on_share_select_file_clicked();

    void on_tabWidget_currentChanged(int index);

    void show_clicked_post();

    void show_post();

    void on_actionLogout_triggered();

    void approve_request();
    void disapprove_request();
    
    void on_refresh_button_clicked();
    void render_admin_window();

private:
    void set_status(std::string);
    void render_login();
    void render_signup();
    void render_home();
    void render_share();
    void render_profile();
    void render_people();
    void render_friends();
    void render_requests();
    Ui::MainWindow *ui;
    std::map<std::string,bool> refresh;
    void configure_menu();
    //Api api;
};

#endif // MAINWINDOW_H
