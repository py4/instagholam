#include "json.h"
using namespace std;
using namespace rapidjson;
Json::Json()
{
	root.SetObject();
}


string Json::dump()
{
	StringBuffer buffer;
	PrettyWriter<StringBuffer> writer(buffer);
	root.Accept(writer);
	return buffer.GetString();
}

rapidjson::Document Json::parse(string json)
{
	rapidjson::Document d;
	d.Parse<0>(json.c_str());
}