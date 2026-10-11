
#include "../include/Reservation.h"
#include <iostream>
using namespace std;

// Default constructor
Reservation::Reservation()
    : reservationID(""),
      studentID(""),
      studentName(""),
      resourceID(""),
      reservationDate("")
{
}

// Constructor
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

// Reservation node constructor
ReservationNode::ReservationNode(const Reservation& reservation)
    : data(reservation), next(nullptr)
{
}

// Reservation list constructor
ReservationList::ReservationList()
    : head(nullptr), tail(nullptr)
{
}

// Get reservation ID
string Reservation::getReservationID() const
{
    return reservationID;
}

// Get student ID
string Reservation::getStudentID() const
{
    return studentID;
}

// Get student name
string Reservation::getStudentName() const
{
    return studentName;
}

// Get resource ID
string Reservation::getResourceID() const
{
    return resourceID;
}

// Get reservation date
string Reservation::getReservationDate() const
{
    return reservationDate;
}

// Display reservation information
void Reservation::display() const
{
    cout << "Reservation ID: " << reservationID << endl;
    cout << "Student ID: " << studentID << endl;
    cout << "Student Name: " << studentName << endl;
    cout << "Resource ID: " << resourceID << endl;
    cout << "Date: " << reservationDate << endl;
}

// Validate reservation
bool ReservationList::validateReservation(
    const Reservation& reservation) const
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

    ReservationNode* current = head;

    // Check for duplicate reservation ID
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

    // Check whether the resource is already reserved on that date
    while (current != nullptr)
    {
        if (current->data.getResourceID() ==
                reservation.getResourceID() &&
            current->data.getReservationDate() ==
                reservation.getReservationDate())
        {
            cout << "Resource "
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

// Insert reservation
bool ReservationList::insertReservation(
    const Reservation& reservation)
{
    if (!validateReservation(reservation))
    {
        return false;
    }

    ReservationNode* newNode = new ReservationNode(reservation);

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

// Remove or cancel reservation
bool ReservationList::removeReservation(const string& reservationID)
{
    if (head == nullptr)
    {
        cout << "No active reservations.\n";
        return false;
    }

    if (head->data.getReservationID() == reservationID)
    {
        ReservationNode* temp = head;
        head = head->next;

        if (head == nullptr)
        {
            tail = nullptr;
        }

        delete temp;
        cout << "Reservation cancelled successfully.\n";
        return true;
    }

    ReservationNode* current = head;

    while (current->next != nullptr)
    {
        if (current->next->data.getReservationID() == reservationID)
        {
            ReservationNode* temp = current->next;
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

// Display all reservations
void ReservationList::displayReservations() const
{
    if (head == nullptr)
    {
        cout << "\nNo active reservations.\n";
        return;
    }

    cout << "\nReservations:\n";

    ReservationNode* current = head;

    while (current != nullptr)
    {
        current->data.display();
        cout << endl;
        current = current->next;
    }
}

// Search by reservation ID using Linear Search
void ReservationList::searchByReservationID(
    const string& reservationID) const
{
    ReservationNode* current = head;

    while (current != nullptr)
    {
        if (current->data.getReservationID() == reservationID)
        {
            cout << "\nReservation found:\n";
            current->data.display();
            return;
        }

        current = current->next;
    }

    cout << "No reservation found with ID "
         << reservationID << ".\n";
}

// Search by student ID using Linear Search
void ReservationList::searchByStudentID(
    const string& studentID) const
{
    ReservationNode* current = head;
    bool found = false;

    while (current != nullptr)
    {
        if (current->data.getStudentID() == studentID)
        {
            cout << "\nReservation found:\n";
            current->data.display();
            cout << endl;
            found = true;
        }

        current = current->next;
    }

    if (!found)
    {
        cout << "No reservations found for student "
             << studentID << ".\n";
    }
}

// Sort reservations by date
// Uses insertion into a new linked-list order
void ReservationList::sortReservationsByDate()
{
    if (head == nullptr || head->next == nullptr)
    {
        cout << "Not enough reservations to sort.\n";
        return;
    }

    ReservationNode* sorted = nullptr;
    ReservationNode* current = head;

    while (current != nullptr)
    {
        ReservationNode* nextNode = current->next;

        if (sorted == nullptr ||
            current->data.getReservationDate() <
                sorted->data.getReservationDate())
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            ReservationNode* position = sorted;

            while (position->next != nullptr &&
                   position->next->data.getReservationDate() <=
                       current->data.getReservationDate())
            {
                position = position->next;
            }

            current->next = position->next;
            position->next = current;
        }

        current = nextNode;
    }

    head = sorted;

    tail = head;
    while (tail != nullptr && tail->next != nullptr)
    {
        tail = tail->next;
    }

    cout << "Reservations sorted by date.\n";
}

// Clear linked list
void ReservationList::clear()
{
    ReservationNode* current = head;

    while (current != nullptr)
    {
        ReservationNode* temp = current;
        current = current->next;
        delete temp;
    }

    head = nullptr;
    tail = nullptr;
}

// Destructor
ReservationList::~ReservationList()
{
    clear();
}
