#include "query_handler.h"
#include <QFileInfo>
#include <QUuid>
using namespace std;

QueryHandler::QueryHandler()
{
	query_fd = 0;
}

QueryHandler::QueryHandler(int query_fd, string query)
{
	this->query_fd = query_fd;
	this->query = query;
}

string QueryHandler::download_from_client(string file_name)
{
	char buf[100];
	int numbytes = 0;
	while((numbytes = read(query_fd, buf, 100)) > 0)
	{
		QFileInfo fi(file_name.c_str());
		string suffix = fi.suffix().toStdString();
		string file_name = "CDN/" + QUuid::createUuid().toString().toStdString() + "." + suffix;
		FILE* fp = fopen(file_name.c_str(),"ab");
		int written_bytes = fwrite(buf,1,numbytes,fp);
		printf("written %d bytes\n",written_bytes);
		fclose(fp);
	}
	close(query_fd);
}