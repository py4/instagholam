#include <QVBoxLayout>
#include <string>
#include <vector>
#include <QTableWidget>
class UsersTable : public QTableWidget
{
	Q_OBJECT

private slots:
	void view_user();

	public:
	UsersTable(QWidget *parent = 0);
	UsersTable(std::vector <std::string> &, QWidget *parent = 0);
	void add_users(std::vector<std::string>&);
};