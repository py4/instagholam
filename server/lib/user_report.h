#ifndef USER_REPORT_H_
#define USER_REPORT_H_

class User;

class UserReport
{
	friend class Api;
public:
	UserReport();
	UserReport(User*,User*);
	User* get_from();
	User* get_to();
private:
	void set_id();
	int id;
	static int count;
	User* from;
	User* to;
};
#endif
