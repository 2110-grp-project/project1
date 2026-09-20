// this is main.cpp file 
// entry point for campus reservation system 

#include "Resource.h"
#include "Reservation.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(){

	vector<Resource> Res= loadresources("Resource.txt");
	displayresources(Res);
	ReservationList reservations;

	ifstream inputFile("data/reservations.txt");

	if (!inputFile)
	{
		cout << "Could not open file." << endl;
		return 1;
	}

	string line;

	while (getline(inputFile, line))
	{
		stringstream ss(line);

		string reservationID;
		string studentID;
		string studentName;
		string resourceID;
		string reservationDate;

		getline(ss, reservationID, '|');
		getline(ss, studentID, '|');
		getline(ss, studentName, '|');
		getline(ss, resourceID, '|');
		getline(ss, reservationDate, '|');

		Reservation reservation(
				reservationID,
				studentID,
				studentName,
				resourceID,
				reservationDate);

		reservations.insertReservation(reservation);
	}

	inputFile.close();

	int choice;

	do{

		cout<<"\nCampus Resource Reservation System"<<endl;
		cout<<"1. View Resources"<<endl;
		cout<<"2.Search Resources"<<endl;
		cout<<"3.Sort Resources"<<endl;
		cout << "4. View Reservations" << endl;
		cout << "5. Cancel Reservation" << endl;
		cout << "9. Exit" << endl;

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

		else if (choice == 4)
		{
			reservations.displayReservations();
		}

		else if (choice == 5)
		{
			string reservationID;

			cout << "Enter reservation ID for cancellation: ";
			cin >> reservationID;

			reservations.removeReservation(reservationID);
		}
		
	} while (choice !=9);


	return 0;
}
