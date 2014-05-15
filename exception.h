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
#endif
