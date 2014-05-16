#include "node.h"
#include <iostream>
using namespace std;

Node::Node(string name, string value, int depth)
{
	this->name = name;
	this->value = value;
	this->depth = depth;
}

Node* Node::add_node(Node* node)
{
	children.push_back(node);
	return node;
}

Node* Node::add_node(string name, string value, int depth)
{
	Node* new_node = new Node(name,value,this->depth+1);
	new_node->parent = this;
	children.push_back(new_node);
	return new_node;
}

string Node::operator[](string attribute)
{
	return attributes[attribute];
}

vector<Node*>& Node::get_children()
{
	return children;
}

Node* Node::get_parent()
{
	return parent;
}

void Node::set_attribute(string key,string value)
{
	attributes[key] = value;
}

void Node::set_attributes(map<string,string>& attributes)
{
	map<string,string>::iterator i;
	for(i = attributes.begin(); i != attributes.end(); i++)
		this->attributes[i->first] = i->second;
}

void Node::set_value(string value)
{
	this->value = value;
}

string Node::dump()
{
	string result = "";
	result += get_depth_tabs(depth);

	if(name != "root")
	{
		result += "<" + name;
		map<string,string>::iterator i;
		for(i = attributes.begin(); i != attributes.end(); i++)
			result += " " + i->first + "=" + "\"" + i->second + "\"";
		result += ">";
	}
	
	for(int i = 0; i < children.size(); i++)
	{
		result += "\n";
		result += children[i]->dump();
	}
	result += "\n";
	if(value.length() > 0)
	{
		result += get_depth_tabs(depth+1);
		result += value;
		result += '\n';
	}
	result += get_depth_tabs(depth);
	
	if(name != "root")
		result += "</" + name + ">";
	
	return result;
}

Node* Node::get_child_node(string name)
{
	for(int i = 0; i < children.size(); i++)
	{
		if(children[i]->name == name)
			return children[i];
		else if(Node* found = children[i]->get_child_node(name))
			return found;; 
	}
	
	return NULL;
}

void Node::delete_children()
{
	while(!children.empty())
	{
		children.back()->delete_children();
		delete children.back();
		children.pop_back();
	}
}






