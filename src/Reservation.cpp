
#include "../include/Reservation.h"
#include <iostream>
#include <cstdio>
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

ReservationNode::ReservationNode(const Reservation &reservation)
    : data(reservation), next(nullptr)
{
}

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

// Validate reservations
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
    const Reservation &reservation)
{
    if (!validateReservation(reservation))
    {
        return false;
    }

    ReservationNode *newNode = new ReservationNode(reservation);

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

// Display reservations
void ReservationList::displayReservations() const
{
    if (head == nullptr)
    {
        cout << "\nNo active reservations.\n";
        return;
    }

    cout << "\nReservations:\n";

    ReservationNode *current = head;

    while (current != nullptr)
    {
        current->data.display();
        current = current->next;
    }

    cout << endl;
}

// Destructor
ReservationList::~ReservationList()
{
    clear();
}

// Clear linked list
void ReservationList::clear()
{
    ReservationNode *current = head;

    while (current != nullptr)
    {
        ReservationNode *temp = current;
        current = current->next;
        delete temp;
    }

    head = nullptr;
    tail = nullptr;
}

// Split list for merge sort
void ReservationList::splitList(
    ReservationNode *source,
    ReservationNode **front,
    ReservationNode **back)
{
    ReservationNode *slow = source;
    ReservationNode *fast = source->next;

    while (fast != nullptr)
    {
        fast = fast->next;

        if (fast != nullptr)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}

// Merge two sorted lists by reservation date
ReservationNode *ReservationList::merge(
    ReservationNode *left,
    ReservationNode *right)
{
    if (left == nullptr)
        return right;

    if (right == nullptr)
        return left;

    int leftMonth, leftDay, leftYear;
    int rightMonth, rightDay, rightYear;

    string leftDate = left->data.getReservationDate();
    string rightDate = right->data.getReservationDate();

    if (sscanf(leftDate.c_str(), "%d/%d/%d",
               &leftMonth, &leftDay, &leftYear) != 3 ||
        sscanf(rightDate.c_str(), "%d/%d/%d",
               &rightMonth, &rightDay, &rightYear) != 3)
    {
        return left;
    }

    bool leftComesFirst =
        (leftYear < rightYear) ||
        (leftYear == rightYear && leftMonth < rightMonth) ||
        (leftYear == rightYear && leftMonth == rightMonth &&
         leftDay <= rightDay);

    if (leftComesFirst)
    {
        left->next = merge(left->next, right);
        return left;
    }
    else
    {
        right->next = merge(left, right->next);
        return right;
    }
}

// Merge sort
ReservationNode *ReservationList::mergeSort(ReservationNode *node)
{
    if (node == nullptr || node->next == nullptr)
        return node;

    ReservationNode *front;
    ReservationNode *back;

    splitList(node, &front, &back);

    front = mergeSort(front);
    back = mergeSort(back);

    return merge(front, back);
}

// Sort reservations by date
void ReservationList::sortReservationsByDate()
{
    if (head == nullptr || head->next == nullptr)
    {
        cout << "Not enough reservations to sort.\n";
        return;
    }

    head = mergeSort(head);
    tail = head;

    while (tail->next != nullptr)
    {
        tail = tail->next;
    }

    cout << "Reservations sorted by date.\n";
}

// Search by reservation ID
void ReservationList::searchByReservationID(
    const string &reservationID) const
{
    ReservationNode *current = head;

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

    cout << "Reservation not found.\n";
}

// Search by student ID
void ReservationList::searchByStudentID(
    const string &studentID) const
{
    ReservationNode *current = head;
    bool found = false;

    while (current != nullptr)
    {
        if (current->data.getStudentID() == studentID)
        {
            cout << "\nReservation found:\n";
            current->data.display();
            found = true;
        }

        current = current->next;
    }

    if (!found)
    {
        cout << "No reservations found for this student.\n";
    }
}
