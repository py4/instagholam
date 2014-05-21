#include "requestbutton.h"
using namespace std;
RequestButton::RequestButton(QWidget *parent) : QPushButton(parent)
{

}

RequestButton::RequestButton(string username, QWidget *parent) : QPushButton(parent)
{
	this->username = username;
}

