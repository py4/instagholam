#ifndef FAVORITESWINDOW_H
#define FAVORITESWINDOW_H

#include <QMainWindow>
#include <string>

namespace Ui {
class favoriteswindow;
}

class favoriteswindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit favoriteswindow(QWidget *parent = 0);
    ~favoriteswindow();
    void add_item(std::string url, std::string username);
private:
    Ui::favoriteswindow *ui;
};

#endif // FAVORITESWINDOW_H
