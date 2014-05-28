#include "query_handler.h"
#include <QFileInfo>
#include <QUuid>
#include "FileServer.h"
#define BUF_SIZE 4000000

using namespace std;

QueryHandler::QueryHandler()
{
	query_fd = 0;
}

QueryHandler::QueryHandler(FileServer* server, int query_fd)
{
	this->query_fd = query_fd;
	this->server = server;
}

string QueryHandler::download_from_client(string _file_name)
{
	cout << "========== downling from client ==========" << endl; 
	QFileInfo fi(_file_name.c_str());
	string suffix = fi.suffix().toStdString();
	string file_name = QUuid::createUuid().toString().toStdString() + "." + suffix;
	char buf[100];
	int numbytes = 0;
	while((numbytes = read(query_fd, buf, 100)) > 0)
	{
		buf[numbytes < 100 ? numbytes : 100] = '\0';
		FILE* fp = fopen(("CDN/" + file_name).c_str(),"ab");
		printf("read %d bytes from user socket\n",numbytes);
		int written_bytes = fwrite(buf,1,numbytes,fp);
		printf("wrote %d bytes to disk\n",written_bytes);
		fclose(fp);
		if(string(buf) == "quit")
			throw "Client quitted upload";
		if(numbytes < 100)
		{
			cout << "wrote less than 100 bytes, I think it's done" << endl;
			break;
		}
	}
	cout << "===================================" << endl;
	return file_name;
}

void QueryHandler::send(string content)
{
	char* buf = new char[content.size() + 1];
	memcpy(buf,content.c_str(), content.size());
	buf[content.size()] = 0;
	cout << "=======================" << endl;
	cout << "[QueryHandler] sending to " << query_fd << endl;
	int n = write(query_fd, buf, content.size()+1);
	cout << "it was " << n << " bytes " << endl;
	cout << "the content was:  " << endl;
	cout << buf << endl;
	cout << "=========================" << endl;
	if(n < 0)
	{
		int err=errno;
		fprintf(stderr,"%s",strerror(err));
		throw "error in writing!\t";
	}
	delete[] buf;
}

string QueryHandler::receive()
{
	cout << "receiving" << endl;
	char* buf = new char[BUF_SIZE];
	int n = read(query_fd, buf, BUF_SIZE);
	buf[n < BUF_SIZE - 1 ? n : BUF_SIZE - 1] = '\0';
	cout << "=================================" << endl;
	cout << "n:  " << n << endl;
	cout << "QueryHandler received from " << query_fd << " " << buf << endl;
	cout << "=================================" << endl;
	if(n < 0)
	{
		cout << "[QueryHandler] error in reading" << endl;
		throw "error in reading!\t";
	}
	else
		return string(buf);
	delete[] buf;
}

void QueryHandler::set_params(rapidjson::Document& document)
{
	params = get_params(document);
}

void QueryHandler::handle_generate_temp_token(rapidjson::Document& document)
{
	set_params(document);
	string auth_token = params["auth_token"];
	
	try { 
		string token = server->generate_temp_token(auth_token);
		send(token);
	} catch (string e) {
		send(e);
		close(query_fd);
	}
}

void QueryHandler::handle_upload(rapidjson::Document& document)
{
	set_params(document);
	string user_token = params["user_token"];
	try {
		if(server->authenticate_user(user_token))
		{
			string file_name = params["file_name"];
			send_with_key("message","accepted");
			string CDN_path = download_from_client(file_name);
			cout << "final CDN_path:  " << CDN_path << endl;
			send(CDN_path);
			cout << "[QueryHandler] done with sending CDN_path to client with fd " << query_fd << endl;
		}
		else
		{
			send_with_key("message","access denied");
			cout << "[QueryHandler] user token was wrong" << endl;
		} 
	} catch (const char* e) {
		cout << e << endl;
		return;
	}

}

void QueryHandler::send_with_key(string key, string data)
{
	Json json;
	json.AddMember(key.c_str(), data.c_str());
	send(json.dump());
}
