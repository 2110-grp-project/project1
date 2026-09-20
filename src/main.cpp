// this is main.cpp file 
// entry point for campus reservation system 

#include "../include/Resource.h"
#include <iostream> 

using namespace std;

int main(){

	vector<Resource> Res= loadresources("data/resources.txt");
	displayresources(Res);

	int choice;

	do{

		cout<<"\n===== Campus Resource Reservation System ====="<<endl;
		cout<<"1. View Resources"<<endl;
		cout<<"2.Search Resources"<<endl;
		cout<<"3.Sort Resources"<<endl;
		cout<<"Exit"<<endl;

		cin>>choice;
		cin.ignore();

		if (choice==1){
			displayresources(Res);
		}
		
		else if (choice==2){
			searchresources(Res);
		}

		else if(choice==3){
			sortresources(Res);
		}
	}while (choice !=9);
return 0;
}
