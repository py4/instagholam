#include "clickableimage.h"
#include <iostream>
#include <QObject>
#include <QVariant>
using namespace std;

ClickableImage::ClickableImage(int id, QWidget *parent) : QLabel(parent)
{
	this->id = id;
}

void ClickableImage::mousePressEvent(QMouseEvent *eve )
{
	// if ( eve->button() == Qt::LeftButton )
 //    	emit leftButtonPressed(this);
	// else if ( eve->button() == Qt::RightButton )
	// 	emit rightButtonPressed(this);
	// else if ( eve->button() == Qt::MidButton )
	// 	emit middleButtonPressed(this);	
	// /cout << "photo id:  " << id << endl;
}

void ClickableImage::mouseReleaseEvent(QMouseEvent *eve )
{
	if ( eve->button() == Qt::LeftButton )
    	emit leftButtonReleased(this);
	else if ( eve->button() == Qt::RightButton )
		emit rightButtonReleased(this);
	else if ( eve->button() == Qt::MidButton )
		emit middleButtonReleased(this);	
}

void ClickableImage::enterEvent(QEvent* eve)
{
	emit mouseEntered(this);
}

void ClickableImage::leaveEvent(QEvent* eve)
{
	emit mouseLeft(this);
}