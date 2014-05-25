#ifndef FAVORITESWINDOW_H
#define FAVORITESWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
namespace Ui {
class favoriteswindow;
}

class favoriteswindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit favoriteswindow(std::vector <std::string>&, QWidget *parent = 0);
    ~favoriteswindow();
    void add_item(std::string url, std::string username);
private:
    Ui::favoriteswindow *ui;
private slots:
    void view_friend();
};

#endif // FAVORITESWINDOW_H
