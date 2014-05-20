#ifndef COMMENTSWINDOW_H
#define COMMENTSWINDOW_H

#include <QMainWindow>
#include <string>
namespace Ui {
class commentswindow;
}

class commentswindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit commentswindow(QWidget *parent = 0);
    explicit commentswindow(int, std::string, std::string, QWidget* parent = 0);
    void add_comment(std::string, std::string);
    ~commentswindow();
    
private slots:
    void on_submit_comment_clicked();

private:
    Ui::commentswindow *ui;
    int id;
};

#endif // COMMENTSWINDOW_H
