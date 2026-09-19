
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

void merge(vector<Resource>& Res, int left, int mid, int right, bool(*cmp)(Resource, Resource)){
	vector<Resource> leftHalf(Res.begin()+ left, Res.begin()+mid+1);
	vector<Resource> rightHalf(Res.begin()+ mid+1, Res.begin()+right+1);

	int i=0;
	int j=0;
	int k=left;

	while (i<leftHalf.size() && j<rightHalf.size()){
		if (cmp(leftHalf[i], rightHalf[j])){
			Res[k]=leftHalf[i];
			i++;
		}
		else{
			Res[k]=rightHalf[j];
			j++;
		}
		k++;
	}
	
	while(i< leftHalf.size()){
		Res[k]=leftHalf[i];
		i++;
		k++;
	}

	while(j<rightHalf.size()){
		Res[k]=rightHalf[j];
		j++;
		k++;
	}
}

void mergesort(vector<Resource>& Res, int left, int right, bool(*cmp)(Resource, Resource)){
	if (left>=right){
		return;
	}

	int mid=left+(right -left)/2;

	mergesort(Res, left, mid,cmp);
	mergesort(Res, mid+1, right, cmp);
	merge(Res, left, mid, right, cmp);
}


int main(){

	ifstream inFile("Resource.txt");

	if (!inFile){
		cout<<"no file found"<<endl;
		return 0;
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
		
		if (id.empty()){
			cout<<"The id is invalid.So,skipping this entry."<<endl;
			continue;
		}

		bool isduplicate=false;
		for (Resource existing: Res){
			if (existing.id==id){
				cout<<"Duplicate id"<<id<<"found. Skipping this entry."<<endl;
				isduplicate=true;
				break;
			}
		}

		if (isduplicate){
			continue;
		}

			
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
		mergesort(Res, 0, Res.size()-1, comparebyid);
	}
	else if (sortchoice==2){
		mergesort(Res, 0, Res.size()-1, comparebyname);
	}
	else if (sortchoice==3){
		mergesort(Res,0,Res.size()-1, comparebytype);
	}
	else if (sortchoice==4){
		mergesort(Res, 0, Res.size()-1, comparebystatus);
	}
	else{
		cout<<"choice is inavlid. by default; it is sorted by name. "<<endl;
		mergesort(Res,0, Res.size()-1, comparebyname);
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
