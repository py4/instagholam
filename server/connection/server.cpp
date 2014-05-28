#include "server.h"
#include <iostream>
#include <cstdio>
using namespace std;
using namespace Poco;

Server::Server()
{
	// try {
	// 	init_file_server_com();
	// } catch (string e) {
	// 	cerr << e << endl;
	// 	return;
	// }
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
		ConnectionHandler* h = new ConnectionHandler(this,client_fd);
		Thread* t = new Thread;

		t->start(*h);
		//connections.push_back(ConnectionHandler(this,client_fd));
		//threads[i].start(connections[i]);
	}

	cout << "OOOOOOOOOOOOOOHHHHHHHHH THHHHHHHHATT WAAAAAAAAASSSSSSSS HHHHHHHHEEEEEEEEERRRRRRRREEEEEEE" << endl;
}

void Server::send(int fd_i, string content)
{
	cout << "=============== Server sending to " << fd_i << " ===========================" << endl;
	char* buf = new char[content.size() + 1];
	memcpy(buf,content.c_str(), content.size());
	buf[content.size()] = 0;
	int n = write(fd_i, buf, strlen(buf));
	cout << "[Server] sent:  " << content << endl;
	cout << "==========================================" << endl;
	if(n < 0)
		throw "error in writing!\t";
	delete[] buf;
}

string Server::receive(int fd_i)
{
	cout << "======================= server receiving from " << fd_i << " ==========================" << endl;
	char* buf = new char[BUF_SIZE];
	int n = read(fd_i, buf, BUF_SIZE);
	buf[n < BUF_SIZE - 1 ? n : BUF_SIZE - 1] = '\0';
	cout << "content:  " << buf << endl;
	cout << "=====================================================" << endl;
	if(n < 0) 
		throw "error in reading!\t";
	else
		return string(buf);
	delete[] buf;
}
