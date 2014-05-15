#include "parser.h"
#include <iostream>
#include <sstream>
using namespace std;

vector <string> get_hashtags(string line)
{
	vector<string> result;
	istringstream str(line);
	string temp;
	int i = 0;
	while(getline(str,temp,'#'))
	{
		if(i != 0) //the first one...
			result.push_back(temp);
		i++;
	}
	return result;
}
