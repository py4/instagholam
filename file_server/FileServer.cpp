#include "FileServer.h"
#include <iostream>
#include <cstdio>
#include <QUuid>
#include <QFileInfo>
using namespace std;
using namespace Poco;

FileServer::FileServer()
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
	printf("File server started on port %d\n",SERVER_PORT);

	auth_token = "abcdef";
}

string FileServer::receive()
{
	char* buf = new char[BUF_SIZE];
	int n = read(fd, buf, BUF_SIZE);
	buf[n < BUF_SIZE - 1 ? n : BUF_SIZE - 1] = '\0';

	if(n < 0)
		throw "error in reading!\t";
	else
		return string(buf);
	delete[] buf;
}


void FileServer::init()
{
	while(true)
	{
		struct sockaddr_in client_addr;
		socklen_t client_addr_size = sizeof(client_addr);
		int query_fd = accept(fd, (struct sockaddr *) &client_addr, &client_addr_size);

		QueryHandler* handler = new QueryHandler(this,query_fd);
		Thread* t = new Thread;
		t->start(*handler);
		//handlers.push_back(QueryHandler(this,query_fd));
		//cerr << "starting query handler thread " << threads.size() << " with fd of " << query_fd << endl;
		//threads.push_back(new Thread);
		//cout << "i'm runnig handler with fd " << handlers.back().query_fd << endl;
		//threads.back()->start(handlers.back());
		cerr << "after start" << endl;
	}

	/*for(int i = 0; i < threads.size(); i++)
	{
		threads[i]->join();
		cout << "deleting thread " << i << endl;
		delete threads[i];
	} */
}

bool FileServer::authenticate(string auth_hash)
{
	return auth_hash == auth_token;
}

string FileServer::generate_temp_token(string auth_hash)
{
	if(!authenticate(auth_hash))
		throw string("Access Denied");

	string token = QUuid::createUuid().toString().toStdString();
	temp_tokens.push_back(token);
	return token;
}

bool FileServer::authenticate_user(string auth_hash)
{
	for(int i = 0; i < temp_tokens.size(); i++)
		if(temp_tokens[i] == auth_hash)
			return true;
	return false;
}
