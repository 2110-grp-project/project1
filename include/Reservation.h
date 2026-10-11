
#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
using namespace std;

class Reservation {
private:
    string reservationID;
    string studentID;
    string studentName;
    string resourceID;
    string reservationDate;

public:
    Reservation();

    Reservation(string reservationID,
                string studentID,
                string studentName,
                string resourceID,
                string reservationDate);

    string getReservationID() const;
    string getStudentID() const;
    string getStudentName() const;
    string getResourceID() const;
    string getReservationDate() const;

    void display() const;
};

class ReservationNode {
public:
    Reservation data;
    ReservationNode* next;

    ReservationNode(const Reservation& reservation);
};

class ReservationList {
private:
    ReservationNode* head;
    ReservationNode* tail;

public:
    ReservationList();
    ~ReservationList();

    // Insert and remove reservations
    bool insertReservation(const Reservation& reservation);
    bool removeReservation(const string& reservationID);

    bool validateReservation(const Reservation& reservation) const;

    // Display reservations
    void displayReservations() const;

    // Clear linked list
    void clear();

    // Sort reservations by date
    void sortReservationsByDate();

    // Search reservations using Linear Search
    void searchByReservationID(const string& reservationID) const;
    void searchByStudentID(const string& studentID) const;
};

#endif
