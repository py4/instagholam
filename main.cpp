#include <iostream>
#include "db.h"
#include "parser.h"
using namespace std;
int main()
{
	vector <string> result = get_hashtags("#salam  #tag2      #tag3");
	for(int i = 0;i < result.size(); i++)
	{
		cout << "tag:  " << result[i] << endl;
	}
	return 0;
}
