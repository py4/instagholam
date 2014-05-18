#ifndef EXCEPTION_H_
#define EXCEPTION_H_
#include <string>

class Exception
{
public:
	Exception();
Exception(std::string message) : message(message) {}
	std::string message;
};

class UserNotFound : public Exception
{
public:
UserNotFound() : Exception("User not found") {}
};

class WrongCredentials : public Exception
{
public:
WrongCredentials() : Exception("Wrong username of password") {}
};

class AlreadyLoggedIn : public Exception
{
public:
AlreadyLoggedIn() : Exception("Your are already logged in") {}
};

class NotLoggedIn : public Exception
{
public:
NotLoggedIn() : Exception("Your are not logged in") {}
};

class UserExists : public Exception
{
public:
UserExists() : Exception("Username already exists") {}
};

class AccessDenied : public Exception
{
public:
AccessDenied() : Exception("Access Denied") {}
};

class FriendWithYourself : public Exception
{
public:
FriendWithYourself() : Exception("You can't befriend with yourself!") {}
};

class AlreadyRequested : public Exception
{
public:
AlreadyRequested() : Exception("You've already requested for friendship") {}
};

class HeRequested : public Exception
{
public:
	HeRequested() : Exception("He's already requested for friendship") {}
};

class AlreadyFriends : public Exception
{
public:
AlreadyFriends() : Exception("You are already friends") {}
};

class NotFriends : public Exception
{
public:
NotFriends() : Exception("You are not friends") {}
};

class ReportedBefore : public Exception
{
public:
ReportedBefore() : Exception("You've reported him before") {}
};

class PostNotFound : public Exception
{
public:
PostNotFound() : Exception("Post not found...") {}
};

class LikedBefore : public Exception
{
public:
LikedBefore() : Exception("You've liked this post before") {}
};

class EmptyTitle: public Exception
{
public:
	EmptyTitle() : Exception("Title shouldn't be empty") {}
};

class EmptyPhoto : public Exception
{
public:
	EmptyPhoto() : Exception("There is no photo to upload") {}
};

class EmptyUsername: public Exception
{
public:
	EmptyUsername() : Exception("Username cannot be empty") {}
};

class BadPassword : public Exception
{
public:
	BadPassword() : Exception("Password length should at least be 5 characters") {}
};

class BadInput : public Exception
{
public:
	BadInput() : Exception("Bad input") {}
};

class CommentNotFound : public Exception
{
public:
	CommentNotFound() : Exception("Comment not found") {}
};

#endif
