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
class ReservationNode
{
public:
    Reservation data;
    ReservationNode *next;

    ReservationNode(const Reservation &reservation);
};

class ReservationList
{
private:
    ReservationNode *head;
    ReservationNode *tail;

public:
    ReservationList();
    ~ReservationList();

    // insert and remove to linked list
    bool insertReservation(const Reservation &reservation);
    bool removeReservation(const string &reservationID);

    bool validateReservation(const Reservation &reservation) const;

    // display
    void displayReservations() const;

    // clear linked list
    void clear();
};

#endif