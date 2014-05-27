#ifndef JSON_H_
#define JSON_H_

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/reader.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <string>

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
private:
	rapidjson::Document root;
};
#endif