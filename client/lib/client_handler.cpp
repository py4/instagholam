#include "client_handler.h"
using namespace std;

static int client_fd = 0;

void ClientHandler::init()
{
	client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	int iSetOption = 1;
	setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&iSetOption, sizeof(iSetOption));
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	serv_addr.sin_port = htons(SERVER_PORT);

	if(connect(client_fd, (struct sockaddr*)& serv_addr, sizeof(serv_addr)) == -1)
		throw "Could not connect to the server";
	else
		cout << "connected with fd " << client_fd << endl;
}

ClientHandler::ClientHandler()
{
	init();
}

ClientHandler::~ClientHandler()
{
	close(client_fd);
}

void ClientHandler::send(string content)
{
	char* buf = new char[content.size() + 1];
	memcpy(buf,content.c_str(), content.size());
	buf[content.size()] = 0;
	int n = write(client_fd, buf, strlen(buf));
	if(n < 0)
		throw "error in writing!\t";
	delete[] buf;
}

std::string ClientHandler::receive()
{
	char* buf = new char[BUF_SIZE];
	int n = read(client_fd, buf, sizeof(buf));
	buf[n < BUF_SIZE - 1 ? n : BUF_SIZE - 1] = '\0';

	if(n < 0)
		throw "error in reading!\t";
	else
		return string(buf);
	delete[] buf;
}