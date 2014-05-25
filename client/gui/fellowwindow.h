#ifndef FELLOWWINDOW_H
#define FELLOWWINDOW_H

#include <QMainWindow>
#include <string>
namespace Ui {
class fellowwindow;
}

class fellowwindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit fellowwindow(QWidget *parent = 0);
    explicit fellowwindow(std::string, QWidget *parent = 0);
    ~fellowwindow();
private slots:
	void approve_request();
	void disapprove_request();
	void request_to_friend();
private:
    Ui::fellowwindow *ui;
    std::string username;
};

#endif // FELLOWWINDOW_H
