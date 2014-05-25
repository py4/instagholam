#include "requestbutton.h"
using namespace std;
RequestButton::RequestButton(QWidget *parent) : QPushButton(parent)
{

}

RequestButton::RequestButton(string username, QWidget *parent) : QPushButton(parent)
{
	this->username = username;
}

RequestButton::RequestButton(int id, QWidget *parent) : QPushButton(parent)
{
	this->id = id;
}
