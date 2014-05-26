#include <QTableWidget>
#include "core.h"
#include <vector>
class ProfileTable : public QTableWidget
{
    Q_OBJECT

public:
	ProfileTable(QWidget *parent = 0);
	ProfileTable(int,int, QWidget *parent = 0);
    void add_posts(std::vector<int>&);
private slots:
    void show_post();
};
