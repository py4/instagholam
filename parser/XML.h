#ifndef XML_H_
#define XML_H_

#include <fstream>
#include <string>
#include "parser.h"
#include "node.h"
#include <sstream>

class XML
{
public:
	XML();
	~XML();
	//bool load(std::string);
	void load(std::string);
	void parse();
	string dump();

	Node* operator[](string);
	Node* get_node(string);

	void save_to_disk(string);

	Node* root_node;
	Node* current_node;
private:
	//std::ifstream raw_data;
	std::stringstream raw_data;

	void delete_node(Node*);

	void dump_node(Node*,string&);
};
#endif
