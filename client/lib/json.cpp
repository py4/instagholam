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
	d.SetObject();
	d.Parse<0>(json.c_str());
	return d;
}

void Json::set_params(map<string,string> params)
{
	rapidjson::Value param(rapidjson::kArrayType);
	for(map<string,string>::iterator it = params.begin(); it != params.end(); it++)
	{
		rapidjson::Value _key(rapidjson::kObjectType);
		_key.AddMember(it->first.c_str(), it->second.c_str(),root.GetAllocator());	
		param.PushBack(_key, root.GetAllocator());
	}

	root.AddMember("params",param,root.GetAllocator());
}

map<string,string> get_params(rapidjson::Document& root)
{
	map<string,string> params;
	if(root["params"].GetType() == 0)
		return params;

	for (Value::ConstValueIterator itr = root["params"].Begin(); itr != root["params"].End(); ++itr)
	{
		for(Value::ConstMemberIterator m = itr->MemberBegin(); m != itr->MemberEnd(); ++m)
			params[m->name.GetString()] = m->value.GetString();
	}

	return params;
}

/*map<string,string> Json::get_params()
{
	return get_params(root);
}*/