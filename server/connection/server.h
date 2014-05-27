#ifndef SERVER_H_
#define SERVER_H_

#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <Poco/Thread.h>
#include "connection_handler.h"
#define SERVER_PORT 3337
#define MAX_CONNECTIONS 5
#include <vector>
class Server
{
public:
	Server();
private:
	int fd;
	std::vector<ConnectionHandler> connections;
	Poco::Thread threads[MAX_CONNECTIONS];
};

#endif