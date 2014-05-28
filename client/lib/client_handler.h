#ifndef CLIENT_HANDLER_H_
#define CLIENT_HANDLER_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 3337
#define BUF_SIZE 2000

class ClientHandler
{
public:
	static void init();
	static void send(std::string, int = -1);
	static std::string receive(int = -1);
//private:
	static int client_fd;
	ClientHandler();
	~ClientHandler();
	ClientHandler(ClientHandler const&);
	void operator=(ClientHandler const&);
};
#endif