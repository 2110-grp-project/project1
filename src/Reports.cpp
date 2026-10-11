#include "Reports.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <limits>
#include <sstream>

using namespace std;


static int reservationcount (const ReservationList& list, const string& resourceID){
	stringstream buffer;
	streambuf* old= cout.rdbuf(buffer.rdbuf());
	list.displayReservations();
	cout.rdbuf(old);
	int count=0;
	string line;
	string tag="Resource id: ";
	while (getline(buffer, line)){
		if(line.compare(0, tag.size(), tag)==0){
			if (resourceID==""|| line.substr(tag.size())==resourceID){
				count++;
			}
		}
	}

	return count;
}

static int waitingcount (const WaitingList& waiting, const string& resourceID){
	stringstream buffer;
	streambuf* old=cout.rdbuf(buffer.rdbuf());
	const_cast<WaitingList&>(waiting).displayWaitingList();
	cout.rdbuf(old);
	int count=0;
	string line;
	string tag="resource id: ";
	while (getline(buffer, line)){
		size_t pos=line.find(tag);
		if (pos!=string::npos){
			if(resourceID==""||line.substr(pos+tag.size())==resourceID){
				count++;
			}
		}
	}

	return count;
}


void activereservation (const ReservationList& list){
	cout<<"\n--- Reports of active reservatios ---\n";
	int total=reservationcount(list, "");
	if (total==0){
		cout<<"there are no active reservation at the moment.\n";
		return;
	}
	cout<<"total active reservations: "<<total<<"\n\n";
	list.displayReservations();
}


void utilization(const vector<Resource>& resources, const ReservationList& list){
	cout<<"\n-- Report of resource utilization --\n";
	if (resources.empty()){
		cout<<"there are no resources.\n";
		return;
	}

	cout<<left<< setw(10) << "Id" <<setw(25) <<"name" << setw(12) <<"status"<< "reservations\n";
	for (const Resource& r: resources){
		cout<<left<< setw(10)<<r.id <<setw(25)<<r.name<<setw(12)<<r.status<<reservationcount(list,r.id)<<"\n";
	}
}




void waitingliststats(const vector<Resource>& resources, const WaitingList& waiting){
	cout<<"\n--- waiting list for each resources ---\n";
	if (resources.empty()){
		cout<<"no resources to display.\n";
		return;
	}

	cout<<left<<setw(10)<<"Id" <<setw(25)<<"name" <<"student waiting\n";
	for (const Resource& r:resources){
		cout<< left <<setw(10) <<r.id<<setw(25)<<r.name << waitingcount(waiting, r.id)<< "\n";
	}
	cout<<" total students waiting for each resources " << waitingcount(waiting, "")<< "\n";
}


struct ResourceDemand {
	string id;
	string name;
	int reservations;
	int waiting;
	int total;
};


void mostrequested(const vector<Resource>& resources, const ReservationList& list, const WaitingList& waiting){

	cout<< "\n--- most requested resources ---\n";
	if ( resources.empty()){
		cout<<"no resources to diplay.\n";
		return;
	}

	vector<ResourceDemand> demand;
	for (const Resource& r: resources){
		ResourceDemand d;
		d.id=r.id;
		d.name=r.name;
		d.reservations= reservationcount(list, r.id);
		d.waiting=waitingcount(waiting, r.id);
		d.total = d.reservations + d.waiting;
		demand.push_back(d);
	}
	for (size_t i=1; i<demand.size(); i++){
		ResourceDemand key= demand[i];
		int j=(int)i -1;
		while (j>=0 && demand[j].total <key.total){
			demand[j+1]=demand[j];
			j--;
		}
		demand[j+1]=key;
	}
	cout<< left <<setw(6)<<"rank"<<setw(10)<<"ID"<<setw(25)<<"name"<<setw(14)<< "reservations" <<setw(10)<< "waiting" <<"total\n";
	for (size_t i=0; i<demand.size(); i++){
		cout<< left << setw(6) <<(i+1) <<setw(10)<< demand[i].id<<setw(25) << demand[i].name << setw(14)<< demand[i].reservations<< setw(10) <<demand[i].waiting <<demand[i].total <<"\n";
	}
}



void menu(const vector<Resource>& resources, const ReservationList& list, const WaitingList& waiting){

	while (true){
		cout<<"\n reports  \n"
			<<"1. Active reservations\n"
			<<"2. Resource utilization\n"
			<<"3. Most requested resources\n"
			<<"4. Waiting list statistic\n"
			<<"0. Back to main menu\n"
			<<" Choose an option: ";

		int choice;
		if (!(cin>>choice)){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout<< "the input is invalid. please try again by entering a number.\n";
			continue;
		}

		switch(choice){
			case 1: activereservation(list); break;
			case 2: utilization(resources, list); break;
			case 3: mostrequested(resources, list, waiting); break;
			case 4: waitingliststats(resources, waiting); break;
			case 0: return;
			default: cout<<"the option is invalid. please enter number between 0-4.\n";
		}
	}
}

