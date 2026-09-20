#include "Reservation.h"
#include <iostream>
using namespace std;


Reservation::Reservation()
    : reservationID(""),
      studentID(""),
      studentName(""),
      resourceID(""),
      reservationDate("")
{
}


Reservation::Reservation(string reservationID,
                         string studentID,
                         string studentName,
                         string resourceID,
                         string reservationDate)
    : reservationID(reservationID),
      studentID(studentID),
      studentName(studentName),
      resourceID(resourceID),
      reservationDate(reservationDate)
{
}
ReservationNode::ReservationNode(
    const Reservation &reservation)
    : data(reservation), next(nullptr)
{
}

ReservationList::ReservationList()
    : head(nullptr), tail(nullptr)
{
}

//get rservation id
string Reservation::getReservationID() const
{
    return reservationID;
}

//get student id
string Reservation::getStudentID() const
{
    return studentID;
}

//get student names
string Reservation::getStudentName() const
{
    return studentName;
}

//get resource id
string Reservation::getResourceID() const
{
    return resourceID;
}

//get reservation date
string Reservation::getReservationDate() const
{
    return reservationDate;
}

//display information from reservation
void Reservation::display() const
{
    cout << "Reservation ID: " << reservationID << endl;
    cout << "Student ID: " << studentID << endl;
    cout << "Student Name: " << studentName << endl;
    cout << "Resource ID: " << resourceID << endl;
    cout << "Date: " << reservationDate << endl;
}

// validating reservations
bool ReservationList::validateReservation(
    const Reservation &reservation) const
{

    if (reservation.getReservationID().empty())
    {
        cout << "Reservation ID cannot be empty.\n";
        return false;
    }

    if (reservation.getStudentID().empty())
    {
        cout << "Student ID cannot be empty.\n";
        return false;
    }

    if (reservation.getStudentName().empty())
    {
        cout << "Student name cannot be empty.\n";
        return false;
    }

    if (reservation.getResourceID().empty())
    {
        cout << "Resource ID cannot be empty.\n";
        return false;
    }

    if (reservation.getReservationDate().empty())
    {
        cout << "Reservation date cannot be empty.\n";
        return false;
    }

    ReservationNode *current = head;

    while (current != nullptr)
    {

        if (current->data.getReservationID() ==
            reservation.getReservationID())
        {

            cout << "Reservation ID already exists.\n";
            return false;
        }

        current = current->next;
    }

    current = head;

    while (current != nullptr)
    {

        if (current->data.getResourceID() ==
                reservation.getResourceID() &&
            current->data.getReservationDate() ==
                reservation.getReservationDate())
        {

            cout << " Resource "
                 << reservation.getResourceID()
                 << " is already reserved on "
                 << reservation.getReservationDate()
                 << ".\n";

            return false;
        }

        current = current->next;
    }

    return true;
}

// insert reservation

bool ReservationList::insertReservation(
    const Reservation &reservation)
{

    if (!validateReservation(reservation))
    {
        return false;
    }

    ReservationNode *newNode =
        new ReservationNode(reservation);

    if (head == nullptr)
    {

        head = newNode;
        tail = newNode;
    }

    else
    {

        tail->next = newNode;
        tail = newNode;
    }

    cout << "Reservation created successfully.\n";

    return true;
}

// remove/cancel reservation

bool ReservationList::removeReservation(
    const string &reservationID)
{

    if (head == nullptr)
    {

        cout << "No active reservations.\n";

        return false;
    }

    if (head->data.getReservationID() == reservationID)
    {

        ReservationNode *temp = head;

        head = head->next;

        if (head == nullptr)
        {
            tail = nullptr;
        }

        delete temp;

        cout << "Reservation cancelled successfully.\n";

        return true;
    }

    ReservationNode *current = head;
    while (current->next != nullptr)
    {

        if (current->next->data.getReservationID() == reservationID)
        {

            ReservationNode *temp = current->next;
            current->next = temp->next;

            if (temp == tail)
            {
                tail = current;
            }

            delete temp;

            cout << "Reservation cancelled successfully.\n";

            return true;
        }

        current = current->next;
    }

    cout << "Reservation not found.\n";

    return false;
}

// display reservations

void ReservationList::displayReservations() const
{

    if (head == nullptr)
    {

        cout << "\nNo active reservations.\n";

        return;
    }

    cout << "\nReservations: \n";
    ReservationNode *current = head;

    while (current != nullptr)
    {

        current->data.display();

        current = current->next;
    }

    cout << endl;
}