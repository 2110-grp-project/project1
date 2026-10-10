// this is main.cpp file 
// entry point for campus reservation system

#include "Resource.h"
#include "Reservation.h"
#include "WaitingList.h"
#include "CancellationHistory.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <vector>


using namespace std;

int main(){

    vector<Resource> Res = loadresources("data/resources.txt");
    displayresources(Res);
    ReservationList reservations;

    WaitingList waitingList;
    CancellationHistory cancellationHistory;

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
        cout<<"2. Search Resources"<<endl;
        cout<<"3. Sort Resources"<<endl;
        cout<<"4. View Reservations"<<endl;
        cout<<"5. Cancel Reservation"<<endl;
        cout<<"6. Add Student to Waiting List"<<endl;
        cout<<"7. Remove Student from Waiting List"<<endl;
        cout<<"8. View Waiting List"<<endl;
        cout<<"9. Undo Cancellation"<<endl;
        cout<<"10. View Cancellation History"<<endl;
        cout<< "11. Insert Reservation"<< endl;
        cout << "12. Sort Reservations by Date" << endl;
        cout<<"13. Exit"<<endl;

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

        else if (choice == 6)
        {
            int studentID;
            string resourceID;

            cout << "Enter student ID: ";
            cin >> studentID;

            cout << "Enter resource ID: ";
            cin >> resourceID;

            waitingList.addStudent(studentID, resourceID);

            cout << "Student added to waiting list." << endl;
        }

        else if (choice == 7)
        {
            waitingList.removeStudent();
        }

        else if (choice == 8)
        {
            waitingList.displayWaitingList();
        }

        else if (choice == 9)
        {
            if (!cancellationHistory.isEmpty())
            {
                CancelledReservation reservation =
                    cancellationHistory.undoCancellation();

                cout << "Reservation " << reservation.reservationID
                     << " was restored." << endl;
            }
            else
            {
                cout << "Cancellation history is empty." << endl;
            }
        }

        else if (choice == 10)
        {
            cancellationHistory.displayHistory();
        }

        else if (choice == 11)
        {
            string reservationID, studentID, studentName, resourceID, reservationDate;

            cout << "Enter reservation ID: ";
            cin >> reservationID;

            cout << "Enter Student ID: ";
            cin >> studentID;

            cin.ignore();
            cout << "Enter Student name: ";
            getline(cin, studentName);

            cout << "Enter Resource ID: ";
            cin >> resourceID;

            cout << "Enter Reservation date: ";
            cin >> reservationDate;

            Reservation reservation(reservationID, studentID, studentName,
                                    resourceID, reservationDate);

            // if not added successfully
            if (!reservations.insertReservation(reservation))
                cout << "Reservation could not be added." << endl;

        }

        else if (choice == 12)
        {
            reservations.sortReservationsByDate();
            reservations.displayReservations();
        }

    } while (choice != 13);

    return 0;
}

