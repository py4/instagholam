#include "server.h"
#include <iostream>
#include <cstdio>
using namespace std;
using namespace Poco;

Server::Server()
{
	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd==-1) {
    	perror("Create socket");
	}
	int iSetOption = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char*)&iSetOption, sizeof(iSetOption));
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;     
	serv_addr.sin_port = htons(SERVER_PORT);
	bind(fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	if (listen(fd, MAX_CONNECTIONS) == -1)
		printf("Listening Error!\n"); 
	cout << "Server started!\n";

	for (int i = 0; i < MAX_CONNECTIONS; i++)
	{
		struct sockaddr_in client_addr;
		socklen_t client_addr_size = sizeof(client_addr);
		int client_fd = accept(fd, (struct sockaddr *) &client_addr, &client_addr_size);
		cout << "New client accepted with id " << client_fd << endl;
		connections.push_back(ConnectionHandler(client_fd));
		threads[i].start(connections[i]);
	}
}