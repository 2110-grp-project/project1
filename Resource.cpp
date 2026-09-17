
// resource management moudule 
// responsible for handling loading, displaying, searching,, and sorting of campus resources 


#include "Resource.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

string tolower(string s){
	for (int i=0; i<s.length(); i++){
		s[i]=tolower(s[i]);
	}
	return s;
}


bool comparebyname(Resource a, Resource b){
	return tolower(a.name)<tolower(b.name);
}

bool comparebyid(Resource a, Resource b){
	return a.id<b.id;
}

bool comparebytype(Resource a, Resource b){
	return tolower(a.type)<tolower(b.type);
}

bool comparebystatus(Resource a, Resource b){
	return tolower(a.status)<tolower(b.status);
}


int main(){

	ifstream inFile("Resource.txt");

	if (!inFile){
		cout<<"no file found"<<endl;
	}

	string line;
	vector <Resource> Res;

	while(getline(inFile, line)){
		stringstream ss(line);
		string id,name,type,status;

		getline(ss,id,'|');
		getline(ss,name,'|');
		getline(ss,type,'|');
		getline(ss,status,'|');

		Resource r;

		r.id=id;
		r.name=name;
		r.type=type;
		r.status=status;
		Res.push_back(r);

	}

	cout<<"file has "<<Res.size()<<" stored information"<<endl;
	for (Resource r:Res){
		cout<<"id: "<<r.id<<" | name: "<<r.name<<" | type: "<<r.type<<" | status: "<<r.status<<endl;

	}

	cout<<"\nsort by : 1) id 2) name 3) type  4)status "<<endl;
	int sortchoice;
	cin>>sortchoice;
	cin.ignore();

	if (sortchoice == 1){
		sort(Res.begin(), Res.end(), comparebyid);
	}
	else if (sortchoice==2){
		sort(Res.begin(), Res.end(), comparebyname);
	}
	else if (sortchoice==3){
		sort(Res.begin(), Res.end(), comparebytype);
	}
	else if (sortchoice==4){
		sort(Res.begin(), Res.end(), comparebystatus);
	}
	else{
		cout<<"choice is inavlid. by default, it is sorted by name. "<<endl;
		sort(Res.begin(), Res.end(), comparebyname);
	}


	cout<<"sorted result: "<<endl;
	for (Resource r: Res){
		cout<<"id: "<<r.id<<" |name: "<<r.name<<" |type: "<<r.type<<" |status: "<<r.status<<endl;
	}

	string searchterm;
	cout<<"\nenter a name or type to search for : ";
	getline(cin,searchterm);

	cout<<"you searched for: "<<searchterm<<endl;

	cout<<"\nsearch results: "<<endl;

	for (Resource r: Res){
		if (tolower(r.name)==tolower(searchterm) ||tolower( r.type)==tolower(searchterm)){
			cout<<"id: "<<r.id<<" |name: "<<r.name<<" |type: "<<r.type<<" |status: "<<r.status<<endl;
		}
	}


return 0;
}
