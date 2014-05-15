#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "api.h"
#include <QString>
#include <string>
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

private:
    void set_status(std::string);
    void render_login();
    void render_signup();
    void render_home();
    Ui::MainWindow *ui;
    Api api;
};

#endif // MAINWINDOW_H
