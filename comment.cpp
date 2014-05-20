#include "comment.h"
#include "post.h"
#include <string>
#include "user.h"
#include <iostream>
using namespace std;
int Comment::count = 0;

Comment::Comment()
{
	id = count + 1;
	count++;
}

Comment::Comment(string content)
{
	id = count + 1;
	count++;
	this->content = content;
}

Comment::Comment(User* user,Post* post,string content)
{
	this->user = user;
	this->post = post;
	this->content = content;
	id = count + 1;
	count++;
}

string Comment::get_user()
{
	return user->get_username();
}

string Comment::get_content()
{
	return content;
}

int Comment::get_post_id()
{
	return post->get_id();
}

string Comment::get_created_at()
{
	struct tm * ptr;
    char buf [20];
    ptr = localtime(&created_at);
    strftime (buf,20,"%x",ptr);
    return buf;
}

