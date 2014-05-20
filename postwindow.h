#ifndef POSTWINDOW_H
#define POSTWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include <QLabel>
namespace Ui {
class PostWindow;
}

class PostWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PostWindow(QWidget *parent = 0);
    explicit PostWindow(int,std::string,std::string,std::string,std::string,QWidget *parent = 0);
    ~PostWindow();
    void set_hashtags(std::vector<std::string>&);
    
private:
    Ui::PostWindow *ui;
    int id;
    std::string title;
    std::string username;
    std::string created_at;
    std::string url;

private slots:
    void show_comments();
    void on_show_comment_button_clicked();
};

#endif // POSTWINDOW_H
