#ifndef RESOURCE_H
#define RESOURCE_H
#include <vector>
#include <string>
using namespace std;

struct Resource{
	string id;
	string name;
	string type;
	string status;
};

vector<Resource> loadresources(string filename);
void displayresources(const vector<Resource>&Res);
void sortresources(vector<Resource>& Res);
void searchresources(const vector<Resource>& Res);

#endif

