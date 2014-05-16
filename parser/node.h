#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <map>
#include <vector>
#include "parser.h"

using namespace std;
class Node
{
	friend class XML;
	friend class DB;
public:
Node() : depth(0) {}
	Node(string, string = "", int = -1);
	Node* add_node(Node*);
	Node* add_node(string, string = "", int = -1);
	string operator[](string);
  vector<Node*>& get_children();
	Node* get_parent();
	void set_attribute(string,string);
	void set_attributes(map<string,string>&);
	void set_value(string);
	string dump();
	
	Node* get_child_node(string);

	string get_value() { return value; }
	void delete_children();
private:
	string name;
	map <string,string> attributes;
	vector <Node*> children;
	Node* parent;
	string value;
	int depth;
};
#endif
