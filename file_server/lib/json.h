#ifndef JSON_H_
#define JSON_H_

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/reader.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <string>
#include "rapidjson/internal/pow10.h"
#include "rapidjson/internal/stack.h"
#include "rapidjson/internal/strfunc.h"
#include <map>

std::map<std::string,std::string> get_params(rapidjson::Document& root);

class Json
{
public:
	Json();
	template<typename T>
	void AddMember(const char* key, T value)
	{
		root.AddMember(key, value, root.GetAllocator());
	}
	std::string dump();
	rapidjson::Document parse(std::string);
	rapidjson::Document root;
	void set_params(std::map<std::string, std::string>);
	//std::map<std::string,std::string> get_params();
};
#endif