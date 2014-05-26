#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>

namespace Ui {
class adminwindow;
}

class adminwindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit adminwindow(QWidget *parent = 0);
    ~adminwindow();
    
private:
    Ui::adminwindow *ui;

    private slots:
    void remove_user();

    private slots:
    void on_register_button_clicked();
};

#endif // ADMINWINDOW_H
