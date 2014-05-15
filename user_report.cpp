#include "user_report.h"
#include "user.h"

int UserReport::count = 0;

UserReport::UserReport()
{
	set_id();
}

UserReport::UserReport(User* from,User* to)
{
	set_id();
	this->from = from;
	this->to = to;
}

void UserReport::set_id()
{
	count++;
	id = count;
}

User* UserReport::get_from()
{
	return from;
}

User* UserReport::get_to()
{
	return to;
}
